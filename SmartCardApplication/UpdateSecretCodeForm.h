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
	/// Summary for UpdateSecretCodeForm
	/// </summary>
	public ref class UpdateSecretCodeForm : public System::Windows::Forms::Form
	{
	public:
		UpdateSecretCodeForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void setVariables(CardCommunication* cc,
			Crypto* cr)
		{
			this->cc = cc;
			this->cr = cr;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateSecretCodeForm()
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UpdateSecretCodeForm::typeid));
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
			this->label1->Location = System::Drawing::Point(36, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(158, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Write New Secret Code:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(39, 78);
			this->textBox1->MaxLength = 16;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(418, 22);
			this->textBox1->TabIndex = 3;
			this->textBox1->UseSystemPasswordChar = true;
			// 
			// showPassword
			// 
			this->showPassword->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPassword.Image")));
			this->showPassword->Location = System::Drawing::Point(474, 68);
			this->showPassword->Name = L"showPassword";
			this->showPassword->Size = System::Drawing::Size(33, 32);
			this->showPassword->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->showPassword->TabIndex = 7;
			this->showPassword->TabStop = false;
			this->showPassword->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &UpdateSecretCodeForm::showPassword_MouseDown);
			this->showPassword->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &UpdateSecretCodeForm::showPassword_MouseUp);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(178, 106);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(145, 36);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Update Code";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UpdateSecretCodeForm::button1_Click);
			// 
			// UpdateSecretCodeForm
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
			this->Name = L"UpdateSecretCodeForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UpdateSecretCodeForm";
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
		array<Char>^ secret_codeP = this->textBox1->Text->ToCharArray();
		char aux_char[16];
		char secret_code[8];
		uint64_t lRetValue;
		memset(aux_char, 0, 16);
		memset(secret_code, 0, 8);

		this->button1->Enabled = false;
		this->textBox1->Enabled = false;

		// check if number has 32 of length
		if (secret_codeP->Length != 16)
		{
			MessageBoxA(NULL, "Secret Code must be 8 hex numbers (16 nibbles)", "Error", MB_OK);
			return;
		}

		// check if every introduced characters is hexadecimal character
		for (size_t i = 0; i < secret_codeP->Length; i++)
		{
			aux_char[i] = (char)secret_codeP[i];

			if (!isxdigit(aux_char[i]))
			{
				MessageBoxA(NULL, "You introduced bad hex character", "Error", MB_OK);
				return;
			}
		}

		// finally create the Administrative key
		size_t j = 0;
		for (size_t i = 0; i < 16; i += 2)
		{
			secret_code[j] = (aux_char[i] <= '9' ? aux_char[i] - '0' : toupper(aux_char[i]) - 'A' + 10) << 4;
			secret_code[j] |= aux_char[i + 1] <= '9' ? aux_char[i + 1] - '0' : toupper(aux_char[i + 1]) - 'A' + 10;
			j += 1;
		}

		// update secret code
		lRetValue = cc->UpdateBinarySecureMessage(0x0005, secret_code, 8, 0, true);

		if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
		{
			MessageBoxA(NULL, "Secret code updated successfully", "Success", MB_OK);
			this->Close();
		}
		else
		{
			MessageBoxA(NULL, "Error updating Secret code", "Error", MB_OK);
			this->button1->Enabled = true;
			this->textBox1->Enabled = true;
		}
	}
};
}
