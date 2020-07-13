#pragma once

#include "CardCommunication.h"
#include "Crypto.h"

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for UpdateAdministrationKey
	/// </summary>
	public ref class UpdateAdministrationKey : public System::Windows::Forms::Form
	{
	public:
		UpdateAdministrationKey(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void setVariables(CardCommunication* cc,
			Crypto* cr,
			System::Windows::Forms::Button^ updateName,
			System::Windows::Forms::Button^ updateIDCredential,
			System::Windows::Forms::Button^ updateSecretCode,
			System::Windows::Forms::Button^ updateAdministrativeKey,
			System::Windows::Forms::Button^ internalAuthenticate,
			System::Windows::Forms::Button^ personalizeCard,
			System::Windows::Forms::Button^ readIDCredential)
		{
			this->cc = cc;
			this->cr = cr;
			this->updateName = updateName;
			this->updateIDCredential = updateIDCredential;
			this->updateSecretCode = updateSecretCode;
			this->updateAdministrativeKey = updateAdministrativeKey;
			this->internalAuthenticate = internalAuthenticate;
			this->personalizeCard = personalizeCard;
			this->readIDCredential = readIDCredential;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateAdministrationKey()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::PictureBox^ showPassword;
	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		CardCommunication* cc;
		Crypto* cr;
		System::Windows::Forms::Button^ updateName;
		System::Windows::Forms::Button^ updateIDCredential;
		System::Windows::Forms::Button^ updateSecretCode;
		System::Windows::Forms::Button^ updateAdministrativeKey;
		System::Windows::Forms::Button^ internalAuthenticate;
		System::Windows::Forms::Button^ personalizeCard;
		System::Windows::Forms::Button^ readIDCredential;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UpdateAdministrationKey::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->showPassword = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(31, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(196, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Write New Administrative Key:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(34, 76);
			this->textBox1->MaxLength = 32;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(418, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->UseSystemPasswordChar = true;
			// 
			// showPassword
			// 
			this->showPassword->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPassword.Image")));
			this->showPassword->Location = System::Drawing::Point(474, 66);
			this->showPassword->Name = L"showPassword";
			this->showPassword->Size = System::Drawing::Size(33, 32);
			this->showPassword->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->showPassword->TabIndex = 6;
			this->showPassword->TabStop = false;
			this->showPassword->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UpdateAdministrationKey::showPassword_MouseDown);
			this->showPassword->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UpdateAdministrationKey::showPassword_MouseUp);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(173, 104);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(145, 36);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Update Key";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UpdateAdministrationKey::button1_Click);
			// 
			// UpdateAdministrationKey
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(519, 152);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->showPassword);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UpdateAdministrationKey";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UpdateAdministrationKey";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void showPassword_MouseDown(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
		this->textBox1->UseSystemPasswordChar = false;
	}

	private: System::Void showPassword_MouseUp(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
		this->textBox1->UseSystemPasswordChar = true;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		array<Char>^ administrative_keyP = this->textBox1->Text->ToCharArray();
		char aux_char[32];
		char administrative_key[16];
		uint64_t lRetValue;
		memset(aux_char, 0, 32);
		memset(administrative_key, 0, 16);

		this->button1->Enabled = false;
		this->textBox1->Enabled = false;

		// check if number has 32 of length
		if (administrative_keyP->Length != 32)
		{
			MessageBoxA(NULL, "Administrative Key must be 16 hex numbers (32 nibbles)", "Error", MB_OK);
			return;
		}

		// check if every introduced characters is hexadecimal character
		for (size_t i = 0; i < administrative_keyP->Length; i++)
		{
			aux_char[i] = (char)administrative_keyP[i];

			if (!isxdigit(aux_char[i]))
			{
				MessageBoxA(NULL, "You introduced bad hex character", "Error", MB_OK);
				return;
			}
		}

		// finally create the Administrative key
		size_t j = 0;
		for (size_t i = 0; i < 32; i += 2)
		{
			administrative_key[j] = (aux_char[i] <= '9' ? aux_char[i] - '0' : toupper(aux_char[i]) - 'A' + 10) << 4;
			administrative_key[j] |= aux_char[i + 1] <= '9' ? aux_char[i + 1] - '0' : toupper(aux_char[i + 1]) - 'A' + 10;
			j += 1;
		}

		// update administrative key
		lRetValue = cc->UpdateBinarySecureMessage(0x0003, administrative_key, 16, 0, true);

		if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
		{
			MessageBoxA(NULL, "Administrative Key updated successfully", "Success", MB_OK);
			MessageBoxA(NULL, "Now please insert new administrative key", "Info", MB_OK);
			updateName->Enabled = false;
			updateIDCredential->Enabled = false;
			updateSecretCode->Enabled = false;
			updateAdministrativeKey->Enabled = false;
			personalizeCard->Enabled = false;
			readIDCredential->Enabled = true;

			internalAuthenticate->Enabled = true;

			this->Close();
		}
		else
		{
			MessageBoxA(NULL, "Error updating Administrative Key", "Error", MB_OK);
			this->button1->Enabled = true;
			this->textBox1->Enabled = true;
		}
	}
};
}
