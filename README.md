# IdentificationAndAuthenticationSmartCardAssignment
Smart Card Assignment from the UC3M Cybersecurity Master Identification &amp; Authentication Class

If you're planning to join the UC3M Cybersecurity Master and you bump into the Identification &amp; Authentication Class without knowing who the f*** works these electronic devices that are the smart cards, don't worry here you have a repository with the solution for the year 2019-2020, it took me around 30 hours to implement this program, considering the documentation time, and the time taken to implement the GUI together with the Smart Card protocol.

You can find the card communication implementation in this class:

[CardCommunication.h][1]

[CardCommunicaiton.cpp][2]

```cpp
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
```

Communication with the smart card reader, obtain readers, wait for cards, and so on:

[DeviceManager.cpp][3]

[DeviceManager.h][4]

```cpp
class DeviceManager
{
public:
	DeviceManager();

	~DeviceManager();

	virtual uint64_t ObtainReaders();
	virtual uint64_t WaitForCardPresent();
	virtual uint64_t WaitForCardRemoval();
	virtual uint64_t ActivateCard();
	virtual uint64_t Disconnect();
	virtual uint64_t ReleaseContext();
	virtual uint64_t ReleaseMemory();
	virtual void SetSelectedReader(LPSTR selected_reader);

	virtual std::vector<LPSTR>& getReaders();

	virtual CardCommunication*	getCardCommunication();

private:

	std::vector<LPSTR>	sc_readers;					// Smart cards readers list
	SCARDCONTEXT		m_hContext;					// Resource manager handle 
	SCARDHANDLE			m_hCard;					// Card Handle
	TCHAR				m_szSelectedReader[256];	// Selected card reader name.
	DWORD				m_dwActiveProtocol;			// Active protocol (T=0, T=1 or undefined).
	LPTSTR				pszaReaders[16];			// Name of the readers
	LPTSTR				pmszReaders = NULL;
	CardCommunication*  cardCommunication;


	virtual LPCTSTR SCardGetErrorString(uint64_t lRetValue);
	virtual int64_t getOptionFromUser(uint64_t nOfOptions);
};
```

Finally cryptography for the smart card

[Cypto.cpp][5]

[Crypto.h][6]

```cpp
class Crypto
{
public:
	Crypto(uint16_t NT);
	Crypto(uint16_t NT, char MasterKey[16]);
	~Crypto();

	// Setters
	virtual void setMasterKey(char MasterKey[16]);
	virtual void setCommandTextBox(System::Windows::Forms::RichTextBox^ CommandTextBox);

	// Key, encryption, signing, signature
	virtual uint64_t derive_temporal_key(uint16_t NT);
	virtual uint64_t derive_session_key(uint16_t NT);
	virtual uint64_t verify_internal_auth(uint8_t* msg, uint8_t* rand);
	virtual std::vector<uint8_t> get_internal_auth(uint16_t NT, uint8_t rand[8]);
	virtual std::vector<uint8_t> encrypt(std::vector<uint8_t> command);
	virtual std::vector<uint8_t> sign(std::vector<uint8_t> data);
	virtual bool verify_signature(uint8_t data[]);

	// Encryption/Decryption algorithms

	// DES-ECB
	virtual array<Byte>^ EncryptDESTextToMemoryECB(array<Byte>^ Data, array<Byte>^ Key);
	// 3DES-ECB
	virtual array<Byte>^ Encrypt3DESTextToMemoryECB(array<Byte>^ Data, array<Byte>^ Key);
	virtual array<Byte>^ Decrypt3DESTextFromMemoryECB(array<Byte>^ Data, array<Byte>^ Key);
	// 3DES-CBC
	virtual array<Byte>^ Encrypt3DESTextToMemoryCBC(array<Byte>^ Data, array<Byte>^ Key, array<Byte>^ IV);

	
	uint16_t NT;			// NT Value
	uint8_t  SK[16];		// Session Key
	uint8_t  TK[16];		// Temporal Key

private:
	
	char MasterKey[16] = { 'M','A','S','T','E','R','A','D','M','K','E','Y','_','0','0','2' };
	bool NT_Set;

	gcroot<System::Windows::Forms::RichTextBox^> CommandTextBox;	// Command text box to write
};
```

[1]: https://github.com/Fare9/IdentificationAndAuthenticationSmartCardAssignment/blob/master/SmartCardApplication/header/CardCommunication.h
[2]: https://github.com/Fare9/IdentificationAndAuthenticationSmartCardAssignment/blob/master/SmartCardApplication/src/CardCommunication.cpp
[3]: https://github.com/Fare9/IdentificationAndAuthenticationSmartCardAssignment/blob/master/SmartCardApplication/header/DeviceManager.h
[4]: https://github.com/Fare9/IdentificationAndAuthenticationSmartCardAssignment/blob/master/SmartCardApplication/src/DeviceManager.cpp
[5]: https://github.com/Fare9/IdentificationAndAuthenticationSmartCardAssignment/blob/master/SmartCardApplication/Crypto.cpp
[6]: https://github.com/Fare9/IdentificationAndAuthenticationSmartCardAssignment/blob/master/SmartCardApplication/Crypto.h
