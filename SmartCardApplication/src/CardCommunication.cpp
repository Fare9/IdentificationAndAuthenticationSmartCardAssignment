#include "CardCommunication.h"

CardCommunication::CardCommunication(SCARDCONTEXT m_hContext, SCARDHANDLE m_hCard, DWORD m_dwActiveProtocol)
{
	this->m_hContext = m_hContext;
	this->m_hCard = m_hCard;

	switch (m_dwActiveProtocol)
	{
	case SCARD_PROTOCOL_T0:
		this->ioRequest = SCARD_PCI_T0;
		break;
	case SCARD_PROTOCOL_T1:
		this->ioRequest = SCARD_PCI_T1;
		break;
	default:
		this->ioRequest = SCARD_PCI_RAW;
		break;
	}

	srand((unsigned) time(0));
}

CardCommunication::~CardCommunication() = default;

void CardCommunication::SetCommandTextBox(gcroot<System::Windows::Forms::RichTextBox^> CommandTextBox)
{
	this->CommandTextBox = CommandTextBox;
}

void CardCommunication::SetCrypto(Crypto* crypto)
{
	this->crypto = crypto;
}

uint64_t CardCommunication::SendAnswerToReset()
{
	uint64_t lRetValue;
	BYTE answerToResetCommand[] = { 0x3B,0x68,0x00,0x00,0x80,0x66,0x57,0x59,0x01,0x00,0x08,0x03 };

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nSending Answer To Reset\n");
	_tprintf(_T("Sending Answer To Reset...\n"));

	RtlZeroMemory(baResponseApdu, 300);

	lRetValue = this->Exchange((LPCBYTE)answerToResetCommand, (uint32_t)sizeof(answerToResetCommand), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

uint64_t CardCommunication::SelectDF(CONST CHAR* dfName)
{
	std::vector<BYTE> selectDF = { 
		0x00,	// CLA
		0xA4,	// INS 
		0x04,	// P1 (DF or MF by name)
		0x00	// P2 (Return FCI)
	};
	uint64_t lRetValue = 0;
	size_t   nameLen = 0;
	System::String^ stringP;
	char text_buffer[300];

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	if (dfName == nullptr)
		return -1;

	nameLen = strlen(dfName);

	snprintf(text_buffer, 300, "\nSELECT DF=%s...\n", dfName);
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("SELECT DF=%s...\n", dfName);

	if ((nameLen == 0) || (nameLen > 16))
	{
		CommandTextBox->AppendText("Name cannot be 0, or exceeds the limit of 16 bytes\n");
		MessageBoxA(NULL, "Name cannot be 0, or exceeds the limit of 16 bytes", "Name Error", MB_OK);
		_tprintf(_T("Name cannot be 0, or exceeds the limit of 16 bytes\n"));
		return -1;
	}

	selectDF.push_back((BYTE)(nameLen & 0xFF));

	for (size_t i = 0; i < nameLen; i++)
	{
		selectDF.push_back((BYTE)(dfName[i]));
	}

	RtlZeroMemory(baResponseApdu, 300);

	lRetValue = this->Exchange((LPCBYTE)selectDF.data(), (uint32_t)selectDF.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

uint64_t CardCommunication::SelectEF(CONST uint16_t efID)
{
	std::vector<BYTE> selectEF = { 
		0x00,		// CLA
		0xA4,		// INS
		0x02,		// P1 (Select EF by ID)
		0x00,		// P2 
		0x02		// Length of ID
	};
	System::String^ stringP;
	char text_buffer[300];

	uint64_t lRetValue = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	if (efID == 0)
		return -1;


	selectEF.push_back((BYTE)((efID >> 8) & 0xFF));
	selectEF.push_back((BYTE)(efID & 0xFF));
	
	snprintf(text_buffer, 300, "\nSELECT EF=0x%04X...\n", efID);
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("SELECT EF=0x%04X...\n", efID);

	RtlZeroMemory(baResponseApdu, 300);

	lRetValue = this->Exchange((LPCBYTE)selectEF.data(), (uint32_t)selectEF.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}


// Transparent files
uint64_t CardCommunication::UpdateBinary(CONST uint16_t efID, CONST CHAR* buffer, BYTE size, uint16_t offset)
{
	std::vector<BYTE> writeCommand = { 
		0x00,		// CLA
		0xD6,		// INS (WriteBinary)
	};
	uint64_t lRetValue = 0;
	size_t   bufLen = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled UpdateBinary\n");

	lRetValue = this->SelectEF(efID);

	// Check if it was possible to access the EF
	if (((lRetValue & 0xFF00) != 0x9000) && ((lRetValue & 0xFF00) != 0x6100))
		return lRetValue;

	bufLen = size;

	if ((bufLen > 30) || (bufLen > (efSize - offset)))
	{
		CommandTextBox->AppendText("Sorry error trying to write because of size limit\n");
		MessageBoxA(NULL, "Sorry error trying to write because of size limit", "Error writing", MB_OK);
		printf("Sorry is not possible to write %s in offset %d because of size %d of EF\n", buffer, offset, efSize);
		return -1;
	}

	if (offset & 0x8000)
	{
		CommandTextBox->AppendText("Offset cannot be greater than 32767\n");
		MessageBoxA(NULL, "Offset cannot be greater than 32767", "Offset Error", MB_OK);
		printf("Offset cannot be greater than %d\n", 0x7fff);
		return -1;
	}

	// P1 with b8 = 0 (P1-P2 = offset)
	writeCommand.push_back((BYTE)((offset >> 8) & 0xFF));	// P1
	// second part of the offset in P2
	writeCommand.push_back((BYTE)(offset & 0xFF));			// P2

	// Now write the size
	writeCommand.push_back((BYTE)bufLen);					// Le

	// Now write the data
	for (size_t i = 0; i < bufLen; i++)
		writeCommand.push_back((BYTE)buffer[i]);

	lRetValue = this->Exchange((LPCBYTE)writeCommand.data(), (uint32_t)writeCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);
	
	return lRetValue;
}

uint64_t CardCommunication::ReadBinary(CONST uint16_t efID, CHAR* buffer, BYTE size, uint16_t offset)
{
	std::vector<BYTE> readCommand = { 
		0x00,		// CLA
		0xB0,		// INS (ReadBinary)
	};
	uint64_t lRetValue = 0;
	size_t   bufLen = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled to ReadBinary\n");

	lRetValue = this->SelectEF(efID);

	// Check if it was possible to access the EF
	if (((lRetValue & 0xFF00) != 0x9000) && ((lRetValue & 0xFF00) != 0x6100))
		return lRetValue;

	if ((size > efSize) || (size > (efSize - offset)))
	{
		CommandTextBox->AppendText("Sorry error trying to read because of size limit\n");
		MessageBoxA(NULL, "Sorry error trying to read because of size limit", "Error writing", MB_OK);
		printf("Sorry is not possible to read size %d from offset %d because of size %d of EF\n", size, offset, efSize);
		return -1;
	}

	if (offset & 0x8000)
	{
		CommandTextBox->AppendText("Offset cannot be greater than 32767\n");
		MessageBoxA(NULL, "Offset cannot be greater than 32767", "Offset Error", MB_OK);
		printf("Offset cannot be greater than %d\n", 0x7fff);
		return -1;
	}

	// P1 with b8 = 0 (P1-P2 = offset)
	readCommand.push_back((BYTE)((offset >> 8) & 0xFF));	// P1
	// second part of the offset in P2
	readCommand.push_back((BYTE) (offset & 0xFF));			// P2

	// now size to read
	readCommand.push_back(size);							// Le

	lRetValue = this->Exchange((LPCBYTE)readCommand.data(), (uint32_t)readCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);
	
	// Now probably copy ResponseApdu in buffer?
	memcpy(buffer, baResponseApdu, size);

	return lRetValue;
}

uint64_t CardCommunication::ImplicitUpdateBinary(CONST BYTE efID, CONST CHAR* buffer, BYTE size, BYTE offset)
{
	std::vector<BYTE> writeCommand = { 
		0x00,		// CLA
		0xD6		// INS
	};
	uint64_t lRetValue = 0;
	size_t   bufLen = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	bufLen = size;

	CommandTextBox->AppendText("\nCalled ImplicitUpdateBinary\n");

	if ((bufLen > 30) || (bufLen > (efSize - offset)))
	{
		CommandTextBox->AppendText("Sorry error trying to write because of size limit\n");
		MessageBoxA(NULL, "Sorry error trying to write because of size limit", "Error writing", MB_OK);
		printf("Sorry is not possible to write %s in offset %d because of size %d of EF\n", buffer, offset, efSize);
		return -1;
	}

	if (efID > 0x1f)
	{
		CommandTextBox->AppendText("Sorry ID cannot be greater than 31\n");
		MessageBox(NULL, "Sorry ID cannot be greater than 31", "ID error", MB_OK);
		printf("Sorry in this case ID cannot be greater than: %d\n", 0x1f);
		return -1;
	}

	// P1 is 0x80 | efID
	writeCommand.push_back(0x80 | efID);		// P1

	// second the offset
	writeCommand.push_back(offset);				// P2

	// Now write the size
	writeCommand.push_back((BYTE)bufLen);		// Le

	// Now write the data
	for (size_t i = 0; i < bufLen; i++)
		writeCommand.push_back((BYTE)buffer[i]);

	lRetValue = this->Exchange((LPCBYTE)writeCommand.data(), (uint32_t)writeCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

uint64_t CardCommunication::ImplicitReadBinary(CONST BYTE efID, CHAR* buffer, BYTE size, BYTE offset)
{
	std::vector<BYTE> readCommand = { 
		0x00,		// CLA
		0xB0		// INS
	};
	uint64_t lRetValue = 0;
	size_t   bufLen = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled ImplicitReadBinary\n");

	if ((size > efSize) || (size > (efSize - offset)))
	{
		CommandTextBox->AppendText("Sorry error trying to read because of size limit\n");
		MessageBoxA(NULL, "Sorry error trying to read because of size limit", "Error writing", MB_OK);
		printf("Sorry is not possible to read size %d from offset %d because of size %d of EF\n", size, offset, efSize);
		return -1;
	}

	if (efID > 0x1f)
	{
		CommandTextBox->AppendText("Sorry ID cannot be greater than 31\n");
		MessageBox(NULL, "Sorry ID cannot be greater than 31", "ID error", MB_OK);
		printf("Sorry in this case ID cannot be greater than: %d\n", 0x1f);
		return -1;
	}
	// P1 is 0x80 | efID
	readCommand.push_back(0x80 | efID);		// P1

	// second the offset
	readCommand.push_back(offset);			// P2

	// now size to read
	readCommand.push_back(size);			// Le

	lRetValue = this->Exchange((LPCBYTE)readCommand.data(), (uint32_t)readCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	
	lRetValue = this->GetResponse(buffer, size);

	return lRetValue;
}

// Secure Messages methods
uint64_t CardCommunication::UpdateBinarySecureMessage(CONST uint16_t efID, CONST CHAR* buffer, BYTE size, uint16_t offset, bool encrypt)
{
	std::vector<BYTE> writeCommand = {
	0x04,		// CLA (Secure Messaging)
	0xD6,		// INS (WriteBinary)
	};
	uint64_t lRetValue = 0;
	size_t   bufLen = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled UpdateBinarySecureMessage\n");

	lRetValue = this->SelectEF(efID);

	// Check if it was possible to access the EF
	if (((lRetValue & 0xFF00) != 0x9000) && ((lRetValue & 0xFF00) != 0x6100))
		return lRetValue;

	bufLen = size;

	if ((bufLen > 30) || (bufLen > (efSize - offset)))
	{
		CommandTextBox->AppendText("Sorry error trying to write because of size limit\n");
		MessageBoxA(NULL, "Sorry error trying to write because of size limit", "Error writing", MB_OK);
		printf("Sorry is not possible to write %s in offset %d because of size %d of EF\n", buffer, offset, efSize);
		return -1;
	}

	if (offset & 0x8000)
	{
		CommandTextBox->AppendText("Offset cannot be greater than 32767\n");
		MessageBoxA(NULL, "Offset cannot be greater than 32767", "Offset Error", MB_OK);
		printf("Offset cannot be greater than %d\n", 0x7fff);
		return -1;
	}

	// P1 with b8 = 0 (P1-P2 = offset)
	writeCommand.push_back((BYTE)((offset >> 8) & 0xFF));	// P1
	// second part of the offset in P2
	writeCommand.push_back((BYTE)(offset & 0xFF));			// P2

	// Now write the size
	writeCommand.push_back((BYTE)bufLen + 3);				// Le

	// Now write the data
	for (size_t i = 0; i < bufLen; i++)
		writeCommand.push_back((BYTE)buffer[i]);

	if (!encrypt)
	{
		std::vector<uint8_t> signature = this->crypto->sign(writeCommand);

		for (size_t i = 0; i < 3; i++)
			writeCommand.push_back((BYTE)signature[signature.size() - 3 + i]);
	}
	else
	{
		writeCommand = this->crypto->encrypt(writeCommand);
	}

	lRetValue = this->Exchange((LPCBYTE)writeCommand.data(), (uint32_t)writeCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

uint64_t CardCommunication::ImplicitUpdateBinarySecureMessage(CONST BYTE efID, CONST CHAR* buffer, BYTE size, BYTE offset, bool encrypt)
{
	std::vector<BYTE> writeCommand = {
	0x00,		// CLA
	0xD6		// INS
	};
	uint64_t lRetValue = 0;
	size_t   bufLen = 0;

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	bufLen = size;

	CommandTextBox->AppendText("\nCalled ImplicitUpdateBinarySecureMessage\n");

	if ((bufLen > 30) || (bufLen > (efSize - offset)))
	{
		CommandTextBox->AppendText("Sorry error trying to write because of size limit\n");
		MessageBoxA(NULL, "Sorry error trying to write because of size limit", "Error writing", MB_OK);
		printf("Sorry is not possible to write %s in offset %d because of size %d of EF\n", buffer, offset, efSize);
		return -1;
	}

	if (efID > 0x1f)
	{
		CommandTextBox->AppendText("Sorry ID cannot be greater than 31\n");
		MessageBox(NULL, "Sorry ID cannot be greater than 31", "ID error", MB_OK);
		printf("Sorry in this case ID cannot be greater than: %d\n", 0x1f);
		return -1;
	}

	// P1 is 0x80 | efID
	writeCommand.push_back(0x80 | efID);		// P1

	// second the offset
	writeCommand.push_back(offset);				// P2

	// Now write the size
	writeCommand.push_back((BYTE)bufLen + 3);	// Le

	// Now write the data
	for (size_t i = 0; i < bufLen; i++)
		writeCommand.push_back((BYTE)buffer[i]);

	if (!encrypt)
	{
		std::vector<uint8_t> signature = this->crypto->sign(writeCommand);

		for (size_t i = 0; i < 3; i++)
			writeCommand.push_back((BYTE)signature[signature.size() - 3 + i]);
	}
	else
	{
		writeCommand = this->crypto->encrypt(writeCommand);
	}

	lRetValue = this->Exchange((LPCBYTE)writeCommand.data(), (uint32_t)writeCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

// Create file commands
uint64_t CardCommunication::CreateTransparentFile(CONST uint16_t efID, uint16_t fSize, uint8_t wConditions, uint8_t rConditions)
{
	CommandTextBox->AppendText("\nCalled CreateTransparentFile\n");
	return this->CreateSCFile(efID, this->TRANSPARENT_TYPE, 0x00, fSize, wConditions, rConditions);
}

/*
*	Write condition here will be SECURE MESSAGING always
*/
uint64_t CardCommunication::CreateAdministrativeKeyFile(CONST uint16_t efID, uint16_t fSize, uint8_t rConditions)
{
	CommandTextBox->AppendText("\nCalled CreateAdministrativeKeyFile\n");
	return this->CreateSCFile(efID, this->ADMINISTRATIVE_KEY, 0x00, fSize, ACCESS_SECURE_MESSAGING, rConditions);
}

uint64_t CardCommunication::CreateNTFile(CONST uint16_t efID, uint16_t fSize, uint8_t wConditions, uint8_t rConditions)
{
	CommandTextBox->AppendText("\nCalled CreateNTFile\n");
	return this->CreateSCFile(efID, this->NT_TYPE, 0x00, fSize, wConditions, rConditions);
}

uint64_t CardCommunication::CreateSecretCodeFile(CONST uint16_t efID, uint16_t fSize, uint8_t rConditions)
{
	CommandTextBox->AppendText("\nCalled CreateSecretCodeFile\n");
	return this->CreateSCFile(efID, this->SECRET_CODE, 0x8A, fSize, this->ACCESS_SECURE_MESSAGING, rConditions);
}

uint64_t CardCommunication::SetAccessConditions(CONST uint16_t efID, bool update_access, uint8_t new_access)
{
	std::vector<uint8_t> setaccessconditions_command = {
		0x80,		// CLA
		0x16,		// INS (SetAccessConditions)
	};
	uint64_t lRetValue = 0;
	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled SetAccessConditions\n");

	lRetValue = this->SelectEF(efID);

	// Check if it was possible to access the EF
	if (((lRetValue & 0xFF00) != 0x9000) && ((lRetValue & 0xFF00) != 0x6100))
		return lRetValue;

	if (update_access)
		setaccessconditions_command.push_back(0x00);	// SetAccessCondition for update
	else
		setaccessconditions_command.push_back(0x01);	// SetAccessCondition for reading

	setaccessconditions_command.push_back(new_access);

	lRetValue = this->Exchange((LPCBYTE)setaccessconditions_command.data(), (uint32_t)setaccessconditions_command.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

uint64_t CardCommunication::SetAccessConditionsSecureMessage(CONST uint16_t efID, bool update_access, uint8_t new_access)
{
	std::vector<uint8_t> setaccessconditions_command = {
		0x80,		// CLA
		0x16,		// INS (SetAccessConditions)
	};
	uint64_t lRetValue = 0;
	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled SetAccessConditionsSecureMessage\n");

	lRetValue = this->SelectEF(efID);

	// Check if it was possible to access the EF
	if (((lRetValue & 0xFF00) != 0x9000) && ((lRetValue & 0xFF00) != 0x6100))
		return lRetValue;

	// P1
	if (update_access)
		setaccessconditions_command.push_back(0x00);	// SetAccessCondition for update
	else
		setaccessconditions_command.push_back(0x01);	// SetAccessCondition for reading

	// P2
	setaccessconditions_command.push_back(new_access);

	// Lc
	setaccessconditions_command.push_back(0x03);

	std::vector<uint8_t> signature = this->crypto->sign(setaccessconditions_command);

	for (size_t i = 0; i < 3; i++)
		setaccessconditions_command.push_back((BYTE)signature[signature.size() - 3 + i]);

	lRetValue = this->Exchange((LPCBYTE)setaccessconditions_command.data(), (uint32_t)setaccessconditions_command.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

// Crypto commands
uint64_t CardCommunication::VerifySecretCode(uint8_t secret_code[8])
{
	uint64_t lRetValue = 0;
	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	gcroot<array<unsigned char>^> session_key = gcnew array<unsigned char>(16);
	gcroot<array<Byte>^> secret_codeP = gcnew array<Byte>(8);
	array<unsigned char>^ iv = { 0,0,0,0,0,0,0,0 };

	std::vector<BYTE> verifySecretCode = {
		0x00,		// CLA
		0x20,		// INS (verify secret code)
		0x00,		// P1
		0x00,		// P2
		0x08		// Lc
	};


	for (size_t i = 0; i < 16; i++)
		session_key[i] = this->crypto->SK[i];

	for (size_t i = 0; i < 8; i++)
		secret_codeP[i] = (Byte)secret_code[i];

	CommandTextBox->AppendText("\nCalled VerifySecretCode\n");
	
	array<Byte>^ encrypted = this->crypto->Encrypt3DESTextToMemoryCBC(secret_codeP, session_key, iv);

	for (size_t i = 0; i < 8; i++)
		verifySecretCode.push_back((BYTE)encrypted[i]);
	
	memset(baResponseApdu, 0, 300);

	lRetValue = this->Exchange((LPCBYTE)verifySecretCode.data(), (uint32_t)verifySecretCode.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);
	
	return lRetValue;
}

uint64_t CardCommunication::DoInternalAuthentication(bool local)
{
	uint64_t lRetValue = 0;
	uint8_t random[8];
	uint8_t msg[10];
	std::vector<uint8_t> internal_auth_command = {
		0x00,		// CLA
		0x88,		// instruction (internal auth)
		0x00		// P1
	};
	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	CommandTextBox->AppendText("\nCalled DoInternalAuthentication\n");

	if (local == true)
		internal_auth_command.push_back(0x80); // P2 == local level
	else
		internal_auth_command.push_back(0x00);

	internal_auth_command.push_back(0x08);		// Lc

	for (size_t i = 0; i < 8; i++)
	{
		random[i] = (uint8_t)(0);
		internal_auth_command.push_back(random[i]);
	}

	memset(baResponseApdu, 0, 300);

	lRetValue = this->Exchange((LPCBYTE)internal_auth_command.data(), (uint32_t)internal_auth_command.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	// check if there was an error
	if (((lRetValue & 0xFF00) != 0x9000) && ((lRetValue & 0xFF00) != 0x6100))
		return lRetValue;

	lRetValue = this->GetResponse((CHAR*)baResponseApdu, (BYTE)lRetValue & 0x00FF);

	memcpy(msg, baResponseApdu, 10);

	lRetValue = this->crypto->verify_internal_auth(msg, random);

	return lRetValue;
}

// Private commands
uint64_t CardCommunication::GetResponse(CHAR* buffer, BYTE size)
{
	uint64_t lRetValue;

	std::vector<BYTE> getresponse =
	{
		0x00,		// CLA
		0xC0,		// INS (get response)
		0x00,		// P1
		0x00,		// P2
	};

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;
	
	// add size
	getresponse.push_back(size);

	lRetValue = this->Exchange((LPCBYTE)getresponse.data(), (uint32_t)getresponse.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	memcpy(buffer, baResponseApdu, size);

	return lRetValue;
}

uint64_t CardCommunication::CreateSCFile(CONST uint16_t efID, uint8_t fType, uint8_t fOptionByte, uint16_t fSize, uint8_t wConditions, uint8_t rConditions)
{
	// last byte is size of the next data
	std::vector<BYTE> createCommand = { 0x80, 0xE0, 0x00, 0x00, 0x08 };
	uint64_t lRetValue = 0;
	System::String^ stringP;
	char text_buffer[300];

	BYTE baResponseApdu[300];
	DWORD lResponseApduLen = 0;

	if (efID == 0)
		return -1;

	lRetValue = this->SelectEF(efID);

	// ALWAYS BEFORE CREATING A FILE, CHECK IF ALREADY EXISTS
	if (((lRetValue & 0xFF00) == 0x9000) || ((lRetValue & 0xFF00) == 0x6100))
		return lRetValue;

	// First the ID of new file
	createCommand.push_back((BYTE)((efID >> 8) & 0xFF));
	createCommand.push_back((BYTE)(efID & 0xFF));

	// Now file type
	createCommand.push_back((BYTE)fType);

	// Now file option bytes
	createCommand.push_back((BYTE)fOptionByte);

	// Now file size
	createCommand.push_back((BYTE)((fSize >> 8) & 0xFF));
	createCommand.push_back((BYTE)(fSize & 0xFF));

	// Write conditions
	createCommand.push_back((BYTE)wConditions);

	// Read conditions
	createCommand.push_back((BYTE)rConditions);

	snprintf(text_buffer, 300, "CREATE EF=0x%04X, with next information:\n", efID);
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("CREATE EF=0x%04X, with next information:\n", efID);

	snprintf(text_buffer, 300, "\t- File Type:");
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("\t- File Type:");

	if (fType == this->TRANSPARENT_TYPE)
	{
		snprintf(text_buffer, 300, " TRANSPARENT\n");
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);
		printf(" TRANSPARENT\n");
	}
	else if (fType == this->LINEAL_FIX_RECORD_TYPE)
	{
		snprintf(text_buffer, 300, " LINEAL FIX RECORD\n");
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);
		printf(" LINEAL FIX RECORD\n");
	}

	snprintf(text_buffer, 300, "\t- File Option Bytes: %02X\n", fOptionByte);
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("\t- File Option Bytes: %02X\n", fOptionByte);

	snprintf(text_buffer, 300, "\t- File Size: %04X\n", fSize);
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("\t- File Size: %04X\n", fSize);


	snprintf(text_buffer, 300, "\t- Access Conditions in Write:");
	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);
	printf("\t- Access Conditions in Write:");
	if (wConditions == ACCESS_FREE)
	{
		snprintf(text_buffer, 300, " FREE\n");
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);
		printf(" FREE\n");
	}


	RtlZeroMemory(baResponseApdu, 300);

	lRetValue = this->Exchange((LPCBYTE)createCommand.data(), (uint32_t)createCommand.size(), baResponseApdu, (uint32_t*)&lResponseApduLen);

	return lRetValue;
}

uint64_t CardCommunication::Exchange(LPCBYTE pbSendBuffer, uint32_t cbSendLength, LPBYTE pbRecvBuffer, uint32_t* pcbRecvLength)
{
	uint64_t lRetValue;
	System::String^ stringP;
	char text_buffer[300];

	*pcbRecvLength = rcvLenMax;

	// Now APDU exchange with the buffer given
	lRetValue = SCardTransmit(
					m_hCard,					// Card handle
					ioRequest,					// pointer to send protocol header
					pbSendBuffer,				// send buffer
					cbSendLength,				// send buffer length
					NULL,						// rec. protocol header
					pbRecvBuffer,				// Receive buffer
					(LPDWORD)pcbRecvLength);	// Receive buffer length
	
	printHexString(_T("\n   --> C-Apdu: 0x"), (LPBYTE)pbSendBuffer, cbSendLength);

	if (!lRetValue)
	{
		printHexString(_T("   <-- R-Apdu: 0x"), pbRecvBuffer, *pcbRecvLength);

		snprintf(text_buffer, 300, _T("       SW1SW2: 0x%02X%02X\n"), pbRecvBuffer[*pcbRecvLength - 2], pbRecvBuffer[*pcbRecvLength - 1]);
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);
		_tprintf(_T("       SW1SW2: 0x%02X%02X"), pbRecvBuffer[*pcbRecvLength - 2], pbRecvBuffer[*pcbRecvLength - 1]);

		lRetValue = 0xFFFF & ((pbRecvBuffer[*pcbRecvLength - 2] << 8) | pbRecvBuffer[*pcbRecvLength - 1]);
	}
	
	_tprintf(_T("\n\n"));

	return lRetValue;
}

void CardCommunication::printHexString(CONST TCHAR* sPrefix, LPBYTE baData, DWORD dataLen)
{
	DWORD i;
	System::String^ stringP;

	char text_buffer[300];

	snprintf(text_buffer, 300, "%s", sPrefix);


	stringP = % System::String(text_buffer);
	CommandTextBox->AppendText(stringP);

	_tprintf(_T("%s"), sPrefix);

	for (i = 0; i < dataLen; i++)
	{

		snprintf(text_buffer, 300, "%02X", baData[i]);
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);

		printf("%02X ", baData[i]);
	}

	CommandTextBox->AppendText("\n");
	printf("\n");
}