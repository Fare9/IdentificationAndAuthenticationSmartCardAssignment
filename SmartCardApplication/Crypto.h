#pragma once


#include <stdint.h>
#include <vector>
#include <vcclr.h>

using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Text;
using namespace System::IO;

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

