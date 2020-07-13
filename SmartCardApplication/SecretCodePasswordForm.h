#pragma once

#include <Windows.h>
#include "CardCommunication.h"

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SecretCodePasswordForm
	/// </summary>
	public ref class SecretCodePasswordForm : public System::Windows::Forms::Form
	{
	public:
		SecretCodePasswordForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void setVars(CardCommunication* cc)
		{
			this->cc = cc;
			this->verify_correct = false;
		}

		bool get_verify_correct()
		{
			return verify_correct;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SecretCodePasswordForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ showPassword;
	protected:

	private:
		CardCommunication* cc;
		bool verify_correct;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SecretCodePasswordForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->showPassword = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(38, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(127, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Write Secret Code:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(41, 89);
			this->textBox1->MaxLength = 16;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(359, 22);
			this->textBox1->TabIndex = 1;
			this->textBox1->UseSystemPasswordChar = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(148, 149);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(143, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Check Secret Code";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SecretCodePasswordForm::button1_Click);
			// 
			// showPassword
			// 
			this->showPassword->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPassword.Image")));
			this->showPassword->Location = System::Drawing::Point(415, 79);
			this->showPassword->Name = L"showPassword";
			this->showPassword->Size = System::Drawing::Size(33, 32);
			this->showPassword->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->showPassword->TabIndex = 14;
			this->showPassword->TabStop = false;
			this->showPassword->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &SecretCodePasswordForm::MouseDown);
			this->showPassword->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &SecretCodePasswordForm::MouseUp);
			// 
			// SecretCodePasswordForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(471, 221);
			this->Controls->Add(this->showPassword);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SecretCodePasswordForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SecretCodePasswordForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void MouseDown(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
		this->textBox1->UseSystemPasswordChar = false;
	}

	private: System::Void MouseUp(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
		this->textBox1->UseSystemPasswordChar = true;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		array<Char>^ secret_codeP = this->textBox1->Text->ToCharArray();
		char aux_char[16];
		char secret_code[8];
		uint64_t lRetValue;
		memset(aux_char, 0, 16);
		memset(secret_code, 0, 8);

		if (secret_codeP->Length != 16)
		{
			MessageBoxA(NULL, "Secret code must be 8 hex numbers (16 nibbles)", "Secret code length error", MB_OK);
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

		lRetValue = cc->VerifySecretCode((uint8_t*) secret_code);

		if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			verify_correct = true;
		else
			verify_correct = false;

		this->Close();
	}
};
}
