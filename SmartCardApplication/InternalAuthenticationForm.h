#pragma once

#include "CardCommunication.h"
#include "Crypto.h"
#include <Windows.h>

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for InternalAuthenticationForm
	/// </summary>
	public ref class InternalAuthenticationForm : public System::Windows::Forms::Form
	{
	public:
		InternalAuthenticationForm(void)
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
		~InternalAuthenticationForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ authenticate;
	private: System::Windows::Forms::PictureBox^ showPassword;


	protected:

	private:
		// Private variables
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(InternalAuthenticationForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->authenticate = (gcnew System::Windows::Forms::Button());
			this->showPassword = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(25, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Write the key:";
			this->label1->Click += gcnew System::EventHandler(this, &InternalAuthenticationForm::label1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(28, 74);
			this->textBox1->MaxLength = 32;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(418, 22);
			this->textBox1->TabIndex = 1;
			this->textBox1->UseSystemPasswordChar = true;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &InternalAuthenticationForm::textBox1_TextChanged);
			// 
			// authenticate
			// 
			this->authenticate->Location = System::Drawing::Point(185, 116);
			this->authenticate->Name = L"authenticate";
			this->authenticate->Size = System::Drawing::Size(109, 23);
			this->authenticate->TabIndex = 2;
			this->authenticate->Text = L"Authenticate";
			this->authenticate->UseVisualStyleBackColor = true;
			this->authenticate->Click += gcnew System::EventHandler(this, &InternalAuthenticationForm::authenticate_Click);
			// 
			// showPassword
			// 
			this->showPassword->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPassword.Image")));
			this->showPassword->Location = System::Drawing::Point(452, 64);
			this->showPassword->Name = L"showPassword";
			this->showPassword->Size = System::Drawing::Size(33, 32);
			this->showPassword->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->showPassword->TabIndex = 5;
			this->showPassword->TabStop = false;
			this->showPassword->Click += gcnew System::EventHandler(this, &InternalAuthenticationForm::showPassword_Click);
			this->showPassword->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &InternalAuthenticationForm::showPassword_MouseDown);
			this->showPassword->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &InternalAuthenticationForm::showPassword_MouseUp);
			// 
			// InternalAuthenticationForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(519, 152);
			this->Controls->Add(this->showPassword);
			this->Controls->Add(this->authenticate);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"InternalAuthenticationForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"InternalAuthenticationForm";
			this->Load += gcnew System::EventHandler(this, &InternalAuthenticationForm::InternalAuthenticationForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Authenticate button
	private: System::Void authenticate_Click(System::Object^ sender, System::EventArgs^ e) {
		char aux_char[32];
		char administrative_key[16];
		memset(aux_char, 0, 32);
		memset(administrative_key, 0, 16);

		if (this->textBox1->Text->Length != 32)
			MessageBoxA(NULL, "Key length must be 16 hex numbers (32 nibbles)", "Key Length Error", MB_OK);
		else
		{
			array<Char>^ masterkey = this->textBox1->Text->ToCharArray();

			// check if every introduced characters is hexadecimal character
			for (size_t i = 0; i < masterkey->Length; i++)
			{
				aux_char[i] = (char)masterkey[i];

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

			// Set current master/administrative key
			this->cr->setMasterKey(administrative_key);

			uint64_t lRetValue;
			uint64_t lRetValueAdministrativeKey = cc->SelectEF(0x0003); // check if exists local Administrative Key
			uint64_t lRetValueNT = cc->SelectEF(0x0004); // check if exists local NT

			if ( (((lRetValueAdministrativeKey & 0xFF00) != 0x9000) && ((lRetValueAdministrativeKey & 0xFF00) != 0x6100)) 
				|| (((lRetValueNT & 0xFF00) != 0x9000) && ((lRetValueNT & 0xFF00) != 0x6100)) )
				lRetValue = cc->DoInternalAuthentication(false);	// do global internal authentication
			else
				lRetValue = cc->DoInternalAuthentication(true);		// do local internal authentication

			if (lRetValue != 0)
			{
				MessageBoxA(NULL, "Authentication error, probably given key not correct", "Authentication error", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Authentication correct, you can now send secure messages", "Authentication correct", MB_OK);
				// Activate all buttons
				// where internal authentication
				// was necessary
				updateName->Enabled = true;
				updateIDCredential->Enabled = true;
				updateSecretCode->Enabled = true;
				updateAdministrativeKey->Enabled = true;
				personalizeCard->Enabled = true;
				readIDCredential->Enabled = true;
				// avoid new internal authentication
				internalAuthenticate->Enabled = false;
				// close this tab
				this->Close();
			}
		}
	}

	private: System::Void showPassword_MouseDown(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
		this->textBox1->UseSystemPasswordChar = false;
	}

	private: System::Void showPassword_MouseUp(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
		this->textBox1->UseSystemPasswordChar = true;
	}

	private: System::Void showPassword_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void InternalAuthenticationForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
