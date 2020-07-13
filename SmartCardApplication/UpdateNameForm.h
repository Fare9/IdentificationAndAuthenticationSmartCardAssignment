#pragma once

#include "CardCommunication.h"

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for UpdateNameForm
	/// </summary>
	public ref class UpdateNameForm : public System::Windows::Forms::Form
	{
	public:
		UpdateNameForm(void)
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
		~UpdateNameForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::TextBox^ nameBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ surnameBox;

	private:
		/// My variables
		CardCommunication* cc;
		System::Windows::Forms::Form^ parentForm;
		System::Windows::Forms::RichTextBox^ CommandTextBox;
	private: System::Windows::Forms::Button^ button1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(UpdateNameForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->nameBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->surnameBox = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 59);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(250, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Write your name (max 10 characters): ";
			// 
			// nameBox
			// 
			this->nameBox->Location = System::Drawing::Point(50, 94);
			this->nameBox->MaxLength = 10;
			this->nameBox->Name = L"nameBox";
			this->nameBox->Size = System::Drawing::Size(367, 22);
			this->nameBox->TabIndex = 1;
			this->nameBox->Text = L"Example";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(47, 148);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(266, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Write your surname (max 20 characters):";
			// 
			// surnameBox
			// 
			this->surnameBox->Location = System::Drawing::Point(50, 189);
			this->surnameBox->MaxLength = 20;
			this->surnameBox->Name = L"surnameBox";
			this->surnameBox->Size = System::Drawing::Size(367, 22);
			this->surnameBox->TabIndex = 3;
			this->surnameBox->Text = L"Examplez";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(186, 252);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(111, 32);
			this->button1->TabIndex = 4;
			this->button1->Text = L"WriteName";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UpdateNameForm::button1_Click);
			// 
			// UpdateNameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(499, 329);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->surnameBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->nameBox);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"UpdateNameForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"UpdateNameForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &UpdateNameForm::UpdateNameForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void UpdateNameForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
	{
		parentForm->Enabled = true;
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		System::String^ stringP;
		char text_buffer[300];

		char name[10], surname[20];
		memset(name, 0, 10);
		memset(surname, 0, 20);

		array<Char>^ wname = this->nameBox->Text->ToCharArray();
		array<Char>^ wsurname = this->surnameBox->Text->ToCharArray();

		if (wname->Length == 0 || wname->Length > 10)
		{
			MessageBoxA(NULL, "Error Name cannot be 0 or greater than 10", "Error in name", MB_OK);
			return;
		}
		
		if (wsurname->Length == 0 || wsurname->Length > 20)
		{
			MessageBoxA(NULL, "Error Surname cannot be 0 or greater than 10", "Error in surname", MB_OK);
			return;
		}

		// copy name
		for (size_t i = 0; i < wname->Length; i++)
		{
			name[i] = (char)wname[i];
		}

		for (size_t i = 0; i < wsurname->Length; i++)
		{
			surname[i] = (char)wsurname[i];
		}

		snprintf(text_buffer, 300, "Writing the name: %s\n", name);
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);
		snprintf(text_buffer, 300, "Writing the surname: %s\n", surname);
		stringP = % System::String(text_buffer);
		CommandTextBox->AppendText(stringP);

		cc->UpdateBinarySecureMessage(0x0001, name, 10, 0, false);
		cc->UpdateBinarySecureMessage(0x0001, surname, 20, 10, false);

		parentForm->Enabled = true;
		this->Close();
	}

};
}
