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
	/// Summary for UpdateIDCredentialForm
	/// </summary>
	public ref class UpdateIDCredentialForm : public System::Windows::Forms::Form
	{
	public:
		UpdateIDCredentialForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void setVars(CardCommunication* cc, System::Windows::Forms::Form^ parentForm, System::Windows::Forms::RichTextBox^ CommandTextBox)
		{
			this->cc = cc;
			this->parentForm = parentForm;
			this->CommandTextBox = CommandTextBox;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateIDCredentialForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button1;
	protected:

	private:
		CardCommunication* cc;
		System::Windows::Forms::Form^ parentForm;
		System::Windows::Forms::RichTextBox^ CommandTextBox;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UpdateIDCredentialForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(34, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"ID Credential";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(37, 78);
			this->textBox1->MaxLength = 16;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(414, 22);
			this->textBox1->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(157, 118);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(157, 36);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Write ID Credential";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UpdateIDCredentialForm::button1_Click);
			// 
			// UpdateIDCredentialForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(499, 177);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UpdateIDCredentialForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UpdateIDCredentialForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &UpdateIDCredentialForm::UpdateIDCredentialForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void UpdateIDCredentialForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		parentForm->Enabled = true;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ stringP;
		char text_buffer[300];
		uint64_t lRetValue;

		char id_credential[10];
		memset(id_credential, 0, 10);

		array<Char>^ id_credentialP = this->textBox1->Text->ToCharArray();

		if (id_credentialP->Length == 0)
		{
			MessageBoxA(NULL, "Error ID Credential cannot be 0 length", "Error in id credential", MB_OK);
			return;
		}

		// copy id credential
		for (size_t i = 0; i < id_credentialP->Length; i++)
		{
			id_credential[i] = (char)id_credentialP[i];
		}

		snprintf(text_buffer, 300, "Writing the id credential: %s\n", id_credential);
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);

		lRetValue = cc->UpdateBinarySecureMessage(0x0002, id_credential, 10, 0, false);

		if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			MessageBoxA(NULL, "Value correctly set in ID Credential", "Success", MB_OK);
		else
			MessageBoxA(NULL, "Error setting ID Credential", "Error", MB_OK);

		parentForm->Enabled = true;
		this->Close();
	}
	};
}
