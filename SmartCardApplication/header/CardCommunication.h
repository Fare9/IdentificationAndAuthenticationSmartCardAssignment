#ifndef CARDCOMMUNICATION_H
#define CARDCOMMUNICATION_H

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef _UNICODE
#undef _UNICODE
#endif

#include <winscard.h>
#include <tchar.h>
#include <iostream>
#include <cstdint>
#include <Windows.h>
#include <vector>
#include <conio.h>
#include <ctime>

#include <../Crypto.h>

#include <vcclr.h>

class CardCommunication
{
public:
	CardCommunication(SCARDCONTEXT m_hContext, SCARDHANDLE m_hCard, DWORD m_dwActiveProtocol);
	~CardCommunication();

	virtual void SetCommandTextBox(gcroot<System::Windows::Forms::RichTextBox^> CommandTextBox);
	virtual void SetCrypto(Crypto* crypto);

	virtual uint64_t SendAnswerToReset();
	virtual uint64_t SelectDF(CONST CHAR* dfName);
	virtual uint64_t SelectEF(CONST uint16_t efID);
	// Transparent Files
	virtual uint64_t UpdateBinary(CONST uint16_t efID, CONST CHAR* buffer, BYTE size, uint16_t offset);
	virtual uint64_t ReadBinary(CONST uint16_t efID, CHAR* buffer, BYTE size, uint16_t offset);
	virtual uint64_t ImplicitUpdateBinary(CONST BYTE efID, CONST CHAR* buffer, BYTE size, BYTE offset);
	virtual uint64_t ImplicitReadBinary(CONST BYTE efID, CHAR* buffer, BYTE size, BYTE offset);
	// Secure Messages For Update
	virtual uint64_t UpdateBinarySecureMessage(CONST uint16_t efID, CONST CHAR* buffer, BYTE size, uint16_t offset, bool encrypt);
	virtual uint64_t ImplicitUpdateBinarySecureMessage(CONST BYTE efID, CONST CHAR* buffer, BYTE size, BYTE offset, bool encrypt);

	// File creation
	virtual uint64_t CreateTransparentFile(CONST uint16_t efID, uint16_t fSize, uint8_t wConditions, uint8_t rConditions);
	virtual uint64_t CreateAdministrativeKeyFile(CONST uint16_t efID, uint16_t fSize, uint8_t rConditions);
	virtual uint64_t CreateNTFile(CONST uint16_t efID, uint16_t fSize, uint8_t wConditions, uint8_t rConditions);
	virtual uint64_t CreateSecretCodeFile(CONST uint16_t efID, uint16_t fSize, uint8_t rConditions);
	// Set Access Conditions
	virtual uint64_t SetAccessConditions(CONST uint16_t efID, bool update_access, uint8_t new_access);
	virtual uint64_t SetAccessConditionsSecureMessage(CONST uint16_t efID, bool update_access, uint8_t new_access);

	// Auth and verification
	virtual uint64_t VerifySecretCode(uint8_t secret_code[8]);
	virtual uint64_t DoInternalAuthentication(bool local);


	// FILE TYPES
	const uint8_t TRANSPARENT_TYPE			= 0x00;
	const uint8_t LINEAL_FIX_RECORD_TYPE	= 0x02;
	const uint8_t CYCLIC_RECORD_TYPE		= 0x06;
	/*
	*	"Create File" command checks while it's creating an administrative key file or a key file that
	*	the update access condition is secure messaging or BLOCKED.
	*/
	const uint8_t NT_TYPE					= 0x11;
	const uint8_t ADMINISTRATIVE_KEY		= 0x19;
	const uint8_t SECRET_CODE				= 0x21;

	// ACCESS CONDITIONS
	const uint8_t ACCESS_FREE = 0x00;
	const uint8_t ACCESS_SECRET_CODE = 0x01;
	const uint8_t ACCESS_SECURE_MESSAGING = 0x02;
	const uint8_t ACCESS_BLOCKED = 0x03;

	const uint32_t			efSize = 30;

private:
	SCARDCONTEXT			m_hContext;				 // Resource manager handle 
	SCARDHANDLE				m_hCard;				 // Card Handle
	LPCSCARD_IO_REQUEST		ioRequest;
	const uint32_t			rcvLenMax = 300;
	Crypto*					crypto;
	gcroot<System::Windows::Forms::RichTextBox^> CommandTextBox;	// Command text box to write

	// Private Methods that shouldn't be used
	// here are the complex implementations
	virtual uint64_t GetResponse(CHAR* buffer, BYTE size);
	virtual uint64_t CreateSCFile(CONST uint16_t efID, uint8_t fType, uint8_t fOptionByte, uint16_t fSize, uint8_t wConditions, uint8_t rConditions);
	virtual uint64_t Exchange(LPCBYTE pbSendBuffer, uint32_t cbSendLength, LPBYTE pbRecvBuffer, uint32_t* pcbRecvLength);
	virtual void printHexString(CONST TCHAR* sPrefix, LPBYTE baData, DWORD dataLen);
};

#endif // !CARDCOMMUNICATION_H
