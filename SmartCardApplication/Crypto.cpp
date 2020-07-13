#include "Crypto.h"
#include <string>

Crypto::Crypto(uint16_t NT)
{
    this->NT = NT;
    NT_Set = false;
}

Crypto::Crypto(uint16_t NT, char MasterKey[16])
{
    this->NT = NT;

    for (size_t i = 0; i < 16; i++)
        this->MasterKey[i] = MasterKey[i];
}

Crypto::~Crypto() = default;

void Crypto::setMasterKey(char MasterKey[16])
{
    for (size_t i = 0; i < 16; i++)
        this->MasterKey[i] = MasterKey[i];
}

void Crypto::setCommandTextBox(System::Windows::Forms::RichTextBox^ CommandTextBox)
{
    this->CommandTextBox = CommandTextBox;
}

uint64_t Crypto::derive_temporal_key(uint16_t NT)
{    
    std::string str_buffer;

    gcroot<array<unsigned char>^> deskeyMK1MK2 = gcnew array<unsigned char>(16);
    gcroot<array<unsigned char>^> deskeyMK2MK1 = gcnew array<unsigned char>(16);
    
    str_buffer += "Deriving Temporal Key from: ";
    str_buffer += std::to_string(NT);
    str_buffer += "\n";

    uint16_t local_nt = NT;
    local_nt = (local_nt + 1) % 65535;

    array<Byte>^ data = { 0x00, 0x00, 0x00, (Byte)((local_nt >> 8) & 0xFF), (Byte)(local_nt & 0xFF), 0x00, 0x00, 0x00 };

    
    for (size_t i = 0; i < 16; i++)
    {
        deskeyMK1MK2[i] = this->MasterKey[i];
        deskeyMK2MK1[i] = this->MasterKey[(i + 8) % 16];
    }


    // 3DES MK1 || MK2, data
    array<Byte>^ TK1 = this->Encrypt3DESTextToMemoryECB(data, deskeyMK1MK2);

    // 3DES MK2 || MK1, data
    array<Byte>^ TK2 = this->Encrypt3DESTextToMemoryECB(data, deskeyMK2MK1);

    for (size_t i = 0; i < (size_t)TK1->Length; i++)
        TK[i] = TK1[i];
    for (size_t i = 0; i < (size_t)TK2->Length; i++)
        TK[i + 8] = TK2[i];

    str_buffer += "Derived temporal key: ";
    for (size_t i = 0; i < (size_t)16; i++)
    {
        str_buffer += std::to_string(TK[i]);
        if (i != 15)
            str_buffer += ",";
    }

    str_buffer += "\n";

    CommandTextBox->AppendText(% System::String(str_buffer.c_str()));

    return 0;
}

uint64_t Crypto::derive_session_key(uint16_t NT)
{
    std::string str_buffer;

    gcroot<array<unsigned char>^> deskeyMK1MK2 = gcnew array<unsigned char>(16);
    gcroot<array<unsigned char>^> deskeyMK2MK1 = gcnew array<unsigned char>(16);

    str_buffer += "Deriving Session Key from: ";
    str_buffer += std::to_string(NT);
    str_buffer += "\n";

    if (this->derive_temporal_key(NT) != 0)
    {
        CommandTextBox->AppendText("Not possible to derive temporal key\n");
        return -1;
    }

    uint16_t local_nt = NT;
    local_nt = (local_nt + 2) % 65535;

    array<Byte>^ data = { 0x00, 0x00, 0x00, (Byte)((local_nt >> 8) & 0xFF), (Byte)(local_nt & 0xFF), 0x00, 0x00, 0x00 };

    for (size_t i = 0; i < 16; i++)
    {
        deskeyMK1MK2[i] = this->MasterKey[i];
        deskeyMK2MK1[i] = this->MasterKey[(i + 8) % 16];
    }

    // 3DES MK1 || MK2, data
    array<Byte>^ SK1 = this->Encrypt3DESTextToMemoryECB(data, deskeyMK1MK2);

    // 3DES MK2 || MK1, data
    array<Byte>^ SK2 = this->Encrypt3DESTextToMemoryECB(data, deskeyMK2MK1);

    for (size_t i = 0; i < (size_t)SK1->Length; i++)
        SK[i] = SK1[i];
    for (size_t i = 0; i < (size_t)SK2->Length; i++)
        SK[i + 8] = SK2[i];

    str_buffer += "Derived session key: ";
    for (size_t i = 0; i < (size_t)16; i++)
    {
        str_buffer += std::to_string(SK[i]);
        if (i != 15)
            str_buffer += ",";
    }

    str_buffer += "\n";

    CommandTextBox->AppendText(% System::String(str_buffer.c_str()));

    return 0;
}

uint64_t Crypto::verify_internal_auth(uint8_t* msg, uint8_t* rand)
{
    std::string str_buffer;

    System::String^ stringP;
    char text_buffer[300];
    gcroot<array<unsigned char>^> temporal_key = gcnew array<unsigned char>(16);
    gcroot<array<Byte>^> signature = gcnew array<Byte>(8);
    gcroot<array<Byte>^> randP = gcnew array<Byte>(8);

    uint64_t lRetvalue = 0;
    uint16_t nt;

    str_buffer += "Verify internal auth\n";

    nt = (uint16_t)((uint16_t)(msg[0] << 8) | (uint16_t)msg[1]);

    str_buffer += "NT: ";
    str_buffer += std::to_string(nt);
    str_buffer += "\n";

    if (!NT_Set)
    {
        this->NT = (nt - 2);
        NT_Set = true;
    }

    str_buffer += "Signature: ";
    for (size_t i = 2; i < 10; i++)
    {
        signature[i - 2] = msg[i];
        str_buffer += std::to_string(msg[i]);
        str_buffer += " ";
    }
    str_buffer += "\n";
    
    str_buffer += "Random: ";
    for (size_t i = 0; i < 8; i++)
    {
        randP[i] = rand[i];
        str_buffer += std::to_string(rand[i]);
        str_buffer += " ";
    }
    str_buffer += "\n";


    
    if (this->NT != (nt - 2))
    {
        snprintf(text_buffer, 300, "Received value of NT %d doesn't match with the one we have %d\n", nt, this->NT + 2);
        stringP = % System::String(text_buffer);
        CommandTextBox->AppendText(stringP);

        lRetvalue++;
    }

    // Calculates session key
    if (this->derive_session_key(this->NT) != 0)
    {
        CommandTextBox->AppendText("Error deriving session key\n");
        return -1;
    }

    for (size_t i = 0; i < 16; i++)
        temporal_key[i] = this->TK[i];

    
    array<Byte>^ calc_signature = this->Encrypt3DESTextToMemoryECB(randP, temporal_key);

    str_buffer += "Calculated Signature: ";
    for (size_t i = 0; i < 8; i++)
    {
        str_buffer += std::to_string(calc_signature[i]);
        str_buffer += " ";

        if (signature[i] != calc_signature[i])
        {
            CommandTextBox->AppendText("\nERROR in verification\n");
            lRetvalue = -3;
            break;
        }
    }

    str_buffer += "\n";

    CommandTextBox->AppendText(% System::String(str_buffer.c_str()));

    this->NT = (this->NT + 2) % 65535;

    return lRetvalue;
}

std::vector<uint8_t> Crypto::get_internal_auth(uint16_t NT, uint8_t rand[8])
{
    std::vector<uint8_t> calc_signature;
    gcroot<array<Byte>^> randP = gcnew array<Byte>(8);
    gcroot<array<unsigned char>^> temporal_key = gcnew array<unsigned char>(16);

    uint16_t local_nt = NT - 2;

    if (this->derive_session_key(local_nt) != 0)
    {
        this->CommandTextBox->AppendText("Couldn't derive the session key\n");
        return calc_signature;
    }

    for (size_t i = 0; i < 16; i++)
        temporal_key[i] = this->TK[i];
    for (size_t i = 0; i < 8; i++)
        randP[i] = rand[i];

    array<Byte>^ calc_signatureP = this->Encrypt3DESTextToMemoryECB(randP, temporal_key);

    for (size_t i = 0; i < (size_t)calc_signatureP->Length; i++)
        calc_signature.push_back((uint8_t)calc_signatureP[i]);

    local_nt = (NT + 2) % 65535;

    return calc_signature;
}

std::vector<uint8_t> Crypto::encrypt(std::vector<uint8_t> command)
{
    std::vector<uint8_t> output, data, aux, signature;
    gcroot<array<unsigned char>^> session_key = gcnew array<unsigned char>(16);
    array<unsigned char>^ iv = { 0,0,0,0,0,0,0,0 };
    array<Byte>^ encrypted;
    if (command.size() < 5)
    {
        this->CommandTextBox->AppendText("Command must be at least 5 bytes long\n");
        return output;
    }

    for (size_t i = 5; i < command.size(); i++)
        data.push_back(command[i]);

    aux = this->sign(command);

    signature.push_back(aux[aux.size() - 3]);
    signature.push_back(aux[aux.size() - 2]);
    signature.push_back(aux[aux.size() - 1]);

    if (data.size() > 0)
    {
        for (size_t i = 0; i < 16; i++)
            session_key[i] = this->SK[i];
        
        gcroot<array<Byte>^> dataP = gcnew array<Byte>(data.size());

        for (size_t i = 0; i < data.size(); i++)
            dataP[i] = (Byte)data[i];

        encrypted = this->Encrypt3DESTextToMemoryCBC(dataP, session_key, iv);
    }

    for (size_t i = 0; i < 5; i++)
        output.push_back(command[i]);
    for (size_t i = 0; i < (size_t)encrypted->Length; i++)
        output.push_back((uint8_t)encrypted[i]);
    for (size_t i = 0; i < (size_t)signature.size(); i++)
        output.push_back(signature[i]);

    return output;
}

std::vector<uint8_t> Crypto::sign(std::vector<uint8_t> data)
{
    std::vector<uint8_t> output, current_block;
    gcroot<array<unsigned char>^> session_key = gcnew array<unsigned char>(16);
    gcroot<array<unsigned char>^> des_session_key = gcnew array<unsigned char>(8);
    array<Byte>^ signature;
    gcroot<array<Byte>^> current_blockP = gcnew array<Byte>(8);
    array<Byte>^ prev_block = { 0, 0, 0, 0, 0, 0, 0, 0 };
    size_t last_index = 0;
    std::string str_buffer;

    str_buffer += "Signing data: ";
    for (size_t i = 0; i < data.size(); i++)
    {
        str_buffer += std::to_string(data[i]);
        str_buffer += " ";
    }
    str_buffer += "\n";

    // Session key, and IV = 0
    for (size_t i = 0; i < 16; i++)
        session_key[i] = this->SK[i];
    for (size_t i = 0; i < 8; i++)
        des_session_key[i] = this->SK[i];

    for (size_t i = 0; i < data.size(); i += 8)
    {
        current_block.clear();
        if ((i + 8) <= data.size())
            last_index = i + 8;
        else
            last_index = data.size();

        for (size_t j = i; j < last_index; j++)
            current_block.push_back(data[j]);

        while (current_block.size() != 8) current_block.push_back(0);
        
        for (size_t j = 0; j < 8; j++)
            current_block[j] = current_block[j] ^ prev_block[j];

        for (size_t j = 0; j < 8; j++)
            current_blockP[j] = (Byte)current_block[j];

        if (i < (data.size() - 8))
            prev_block = this->EncryptDESTextToMemoryECB(current_blockP, des_session_key);
        else
            signature = this->Encrypt3DESTextToMemoryECB(current_blockP, session_key);
    }

    for (size_t i = 0; i < (size_t)signature->Length; i++)
        output.push_back((uint8_t) signature[i]);

    str_buffer += "Data signed: ";
    for (size_t i = 0; i < output.size(); i++)
    {
        str_buffer += std::to_string(output[i]);
        str_buffer += " ";
    }
    str_buffer += "\n";

    return output;
}

bool Crypto::verify_signature(uint8_t data[])
{
    std::vector<uint8_t> parameter, calc_sign, recv_signature;

    for (size_t i = 0; i < sizeof(data) - 3; i++)
    {
        parameter.push_back(data[i]);
        recv_signature.push_back(data[i]);
    }

    calc_sign = this->sign(parameter);
    
    return calc_sign == recv_signature;
}

array<Byte>^ Crypto::EncryptDESTextToMemoryECB(array<Byte>^ Data, array<Byte>^ Key)
{
    // Create a MemoryStream.
    MemoryStream^ mStream = gcnew MemoryStream;

    // Create a CryptoStream using the MemoryStream 
    DESCryptoServiceProvider^ des = gcnew DESCryptoServiceProvider;
    des->Key = Key;
    des->Mode = CipherMode::ECB;
    des->Padding = PaddingMode::None;
    CryptoStream^ cStream = gcnew CryptoStream(mStream, des->CreateEncryptor(), CryptoStreamMode::Write);

    // Convert the passed string to a byte array.
    array<Byte>^ toEncrypt = Data;

    // Write the byte array to the crypto stream and flush it.
    cStream->Write(toEncrypt, 0, toEncrypt->Length);
    cStream->FlushFinalBlock();

    // Get an array of bytes from the 
    // MemoryStream that holds the 
    // encrypted data.
    array<Byte>^ ret = mStream->ToArray();

    // Close the streams.
    cStream->Close();
    mStream->Close();

    // Return the encrypted buffer.
    return ret;
}

array<Byte>^ Crypto::Encrypt3DESTextToMemoryECB(array<Byte>^ Data, array<Byte>^ Key)
{
    // Create a MemoryStream.
    MemoryStream^ mStream = gcnew MemoryStream;

    // Create a CryptoStream using the MemoryStream 
    TripleDESCryptoServiceProvider^ tripledes = gcnew TripleDESCryptoServiceProvider;
    tripledes->Key = Key;
    tripledes->Mode = CipherMode::ECB;
    tripledes->Padding = PaddingMode::None;
    CryptoStream^ cStream = gcnew CryptoStream(mStream, tripledes->CreateEncryptor(), CryptoStreamMode::Write);

    // Convert the passed string to a byte array.
    array<Byte>^ toEncrypt = Data;

    // Write the byte array to the crypto stream and flush it.
    cStream->Write(toEncrypt, 0, toEncrypt->Length);
    cStream->FlushFinalBlock();

    // Get an array of bytes from the 
    // MemoryStream that holds the 
    // encrypted data.
    array<Byte>^ ret = mStream->ToArray();

    // Close the streams.
    cStream->Close();
    mStream->Close();

    // Return the encrypted buffer.
    return ret;
}

array<Byte>^ Crypto::Decrypt3DESTextFromMemoryECB(array<Byte>^ Data, array<Byte>^ Key)
{
    // Create a new MemoryStream using the passed 
      // array of encrypted data.
    MemoryStream^ msDecrypt = gcnew MemoryStream(Data);

    // Create a CryptoStream using the MemoryStream 
    TripleDESCryptoServiceProvider^ tripledes = gcnew TripleDESCryptoServiceProvider;
    tripledes->Key = Key;
    tripledes->Mode = CipherMode::ECB;
    tripledes->Padding = PaddingMode::None;
    CryptoStream^ csDecrypt = gcnew CryptoStream(msDecrypt, tripledes->CreateDecryptor(), CryptoStreamMode::Read);

    // Create buffer to hold the decrypted data.
    array<Byte>^ fromEncrypt = gcnew array<Byte>(Data->Length);

    // Read the decrypted data out of the crypto stream
    // and place it into the temporary buffer.
    csDecrypt->Read(fromEncrypt, 0, fromEncrypt->Length);

    //Convert the buffer into a string and return it.
    return fromEncrypt;
}

array<Byte>^ Crypto::Encrypt3DESTextToMemoryCBC(array<Byte>^ Data, array<Byte>^ Key, array<Byte>^ IV)
{
    // Create a MemoryStream.
    MemoryStream^ mStream = gcnew MemoryStream;

    // Create a CryptoStream using the MemoryStream 
    TripleDESCryptoServiceProvider^ tripledes = gcnew TripleDESCryptoServiceProvider;
    tripledes->Key = Key;
    tripledes->IV = IV;
    tripledes->Mode = CipherMode::CBC;
    tripledes->Padding = PaddingMode::None;
    CryptoStream^ cStream = gcnew CryptoStream(mStream, tripledes->CreateEncryptor(), CryptoStreamMode::Write);

    // Convert the passed string to a byte array.
    array<Byte>^ toEncrypt = Data;

    // Write the byte array to the crypto stream and flush it.
    cStream->Write(toEncrypt, 0, toEncrypt->Length);
    cStream->FlushFinalBlock();

    // Get an array of bytes from the 
    // MemoryStream that holds the 
    // encrypted data.
    array<Byte>^ ret = mStream->ToArray();

    // Close the streams.
    cStream->Close();
    mStream->Close();

    // Return the encrypted buffer.
    return ret;
}