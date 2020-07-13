#pragma once

#include "DeviceManager.h"
#include "ReadingNameForm.h"
#include "UpdateNameForm.h"
#include "InternalAuthenticationForm.h"
#include "PersonalizeSCForm.h"
#include "UpdateIDCredentialForm.h"
#include "SecretCodePasswordForm.h"
#include "UpdateAdministrationKey.h"
#include "UpdateSecretCodeForm.h"
#include "ReadingIDCredentialForm.h"

#include "Crypto.h"

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SmartCardForm
	/// </summary>
	public ref class SmartCardForm : public System::Windows::Forms::Form
	{
	public:
		SmartCardForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void InitVariables(DeviceManager* dm, System::Windows::Forms::Form^ parentForm)
		{
			this->dm = dm;
			this->parentForm = parentForm;

			this->cc = dm->getCardCommunication();
			this->cc->SetCommandTextBox(CommandTextBox);
			this->cr = new Crypto(0xFFFF);
			this->cr->setCommandTextBox(CommandTextBox);
			this->cc->SetCrypto(this->cr);
		}

		
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SmartCardForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:

	private:
		DeviceManager* dm;
		CardCommunication* cc;
		Crypto *cr;
		System::Windows::Forms::Form^ parentForm;
		ReadingNameForm^ readingnameform;
		UpdateNameForm^ updatenameform;
		InternalAuthenticationForm^ internalauthenticationform;
		UpdateIDCredentialForm^ updateidcredentialform;
		SecretCodePasswordForm^ secretcodepasswordform;
		PersonalizeSCForm^ personalizescform;
		UpdateAdministrationKey^ updateadministrativekey;
		UpdateSecretCodeForm^ updatesecretcodeform;
		ReadingIDCredentialForm^ readingidcredentialform;
		
	private: System::Windows::Forms::RichTextBox^ CommandTextBox;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button7;

	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;




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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SmartCardForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->CommandTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(158, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(286, 36);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Smart Card Reader";
			// 
			// CommandTextBox
			// 
			this->CommandTextBox->Location = System::Drawing::Point(31, 474);
			this->CommandTextBox->Name = L"CommandTextBox";
			this->CommandTextBox->ReadOnly = true;
			this->CommandTextBox->Size = System::Drawing::Size(760, 249);
			this->CommandTextBox->TabIndex = 1;
			this->CommandTextBox->Text = L"";
			this->CommandTextBox->TextChanged += gcnew System::EventHandler(this, &SmartCardForm::CommandTextBox_TextChanged);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(325, 311);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(173, 56);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Send AnswerToReset";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SmartCardForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(27, 34);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(134, 54);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Read Name";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &SmartCardForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(205, 34);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(134, 54);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Update Name";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &SmartCardForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(456, 168);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(133, 54);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Do Internal Authentication";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &SmartCardForm::button4_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button6);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Location = System::Drawing::Point(23, 95);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(368, 210);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Mandatory Commands";
			this->groupBox1->Visible = false;
			// 
			// button6
			// 
			this->button6->Enabled = false;
			this->button6->Location = System::Drawing::Point(205, 120);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(134, 54);
			this->button6->TabIndex = 6;
			this->button6->Text = L"Update ID Credential";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Visible = false;
			this->button6->Click += gcnew System::EventHandler(this, &SmartCardForm::button6_Click);
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->Location = System::Drawing::Point(27, 120);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(134, 54);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Read ID Credential";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Visible = false;
			this->button5->Click += gcnew System::EventHandler(this, &SmartCardForm::button5_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button8);
			this->groupBox2->Controls->Add(this->button7);
			this->groupBox2->Location = System::Drawing::Point(423, 262);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(345, 175);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Improvements";
			this->groupBox2->Visible = false;
			// 
			// button8
			// 
			this->button8->Enabled = false;
			this->button8->Location = System::Drawing::Point(172, 97);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(141, 66);
			this->button8->TabIndex = 1;
			this->button8->Text = L"Update Administrative Key";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Visible = false;
			this->button8->Click += gcnew System::EventHandler(this, &SmartCardForm::button8_Click);
			// 
			// button7
			// 
			this->button7->Enabled = false;
			this->button7->Location = System::Drawing::Point(30, 36);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(136, 55);
			this->button7->TabIndex = 0;
			this->button7->Text = L"Update Secret Code";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &SmartCardForm::button7_Click);
			// 
			// button9
			// 
			this->button9->Enabled = false;
			this->button9->Location = System::Drawing::Point(646, 168);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(145, 54);
			this->button9->TabIndex = 10;
			this->button9->Text = L"Personalize Card";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Visible = false;
			this->button9->Click += gcnew System::EventHandler(this, &SmartCardForm::button9_Click);
			// 
			// SmartCardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(842, 756);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->CommandTextBox);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SmartCardForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SmartCardForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SmartCardForm::SmartCardForm_FormClosing);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void createFile()
	{
		Stream^ myStream;
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
		saveFileDialog1->Filter = "txt files (*.txt)|*.txt";

		if (MessageBoxA(NULL, "Do you want to save log to file?", "Log File", MB_YESNO) == IDYES)
		{
			if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				if ((myStream = saveFileDialog1->OpenFile()) != nullptr)
				{
					StreamWriter^ sw = gcnew StreamWriter(myStream);
					sw->Write(L"=================================================\n");
					sw->Write(L"UC3M Smart Card Application Reader\n");
					sw->Write(L"Programmers:\n");
					sw->Write(L"\t- Eduardo Blázquez González (100421280)\n");
					sw->Write(L"\t- Jorge Sánchez Freire (100391589)\n");
					sw->Write(L"LOG File:\n");
					sw->Write(L"=================================================\n\n");
					sw->Write(CommandTextBox->Text);
					sw->Close();
					myStream->Close();
				}
			}
		}
	}

	private: System::Void CommandTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		CommandTextBox->SelectionStart = CommandTextBox->Text->Length;
		CommandTextBox->ScrollToCaret();
	}

	private: System::Void SmartCardForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		this->dm->Disconnect();

		CommandTextBox->AppendText("Disconnected from Card\n");

		createFile();

		exit(0);
	}
			// Button for send answer to reset
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		uint64_t lRetValue = this->cc->SendAnswerToReset();

		printf("%d\n", lRetValue);

		this->button1->Visible = false;
		this->groupBox1->Visible = true;
		this->groupBox2->Visible = true;
		this->button2->Visible = true;
		this->button3->Visible = true;
		this->button4->Visible = true;
		this->button5->Visible = true;
		this->button6->Visible = true;
		this->button7->Visible = true;
		this->button8->Visible = true;
		this->button9->Visible = true;
		
		cc->SelectDF("COURSE1920_STD02");
	}
		   // Button for reading name
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		System::String^ stringP;
		char name_read[11];
		char surname_read[21];
		memset(name_read, 0, 11);
		memset(surname_read, 0, 21);

		readingnameform = gcnew ReadingNameForm();


		cc->ReadBinary(0x0001, name_read, 10, 0);
		cc->ReadBinary(0x0001, surname_read, 20, 10);

		stringP = % System::String(name_read);

		CommandTextBox->AppendText("Name read: ");
		CommandTextBox->AppendText(stringP);
		CommandTextBox->AppendText("\n");
		CommandTextBox->AppendText("Surname read: ");
		stringP = % System::String(surname_read);
		CommandTextBox->AppendText(stringP);
		CommandTextBox->AppendText("\n");

	
		readingnameform->Show();
		readingnameform->setName(name_read);
		readingnameform->setSurName(surname_read);
		readingnameform->setParentForm(this);
		this->Enabled = false;
	}
		   // Button for updating name
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		updatenameform = gcnew UpdateNameForm();

		updatenameform->setVars(cc, this, CommandTextBox);
		updatenameform->Show();
		this->Enabled = false;
	}
		   // Button for internal authentication
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		internalauthenticationform = gcnew InternalAuthenticationForm();

		internalauthenticationform->setVariables(cc, cr, button3, button6, button7, button8, button4, button9, button5);

		internalauthenticationform->Show();
	}
		   // Button for personalize card
	private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
		personalizescform = gcnew PersonalizeSCForm();
		personalizescform->setVariables(cc, cr, button3, button6, button7, button8, button4, button9, button5);

		personalizescform->Show();
	}
		   // Button for ipdate the id credential
	private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
		updateidcredentialform = gcnew UpdateIDCredentialForm();
		updateidcredentialform->setVars(cc, this, CommandTextBox);

		updateidcredentialform->Show();
		this->Enabled = false;
	}
		   // Button for read credential
	private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
		char id_credential[16];
		memset(id_credential, 0, 16);

		if (secretcodepasswordform == nullptr || secretcodepasswordform->get_verify_correct() == false)
		{
			secretcodepasswordform = gcnew SecretCodePasswordForm();
			secretcodepasswordform->setVars(cc);

			secretcodepasswordform->ShowDialog();

			if (secretcodepasswordform->get_verify_correct())
			{
				MessageBoxA(NULL, "Secret code correct, now you can read ID credential always", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Secret code not correct", "Error", MB_OK);
				return;
			}
		}

		cc->ReadBinary(0x0002, id_credential, 16, 0);

		readingidcredentialform = gcnew ReadingIDCredentialForm();
		readingidcredentialform->setParentForm(this);
		readingidcredentialform->setIDCredential(id_credential);
		readingidcredentialform->Show();

		this->Enabled = false;

	}
		   // Button for updating the Adminsitrative key
	private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
		updateadministrativekey = gcnew UpdateAdministrationKey();

		updateadministrativekey->setVariables(cc, cr, button3, button6, button7, button8, button4, button9, button5);

		updateadministrativekey->Show();
	}
		   // Button for updating Secret code
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		updatesecretcodeform = gcnew UpdateSecretCodeForm();

		updatesecretcodeform->setVariables(cc, cr);

		updatesecretcodeform->Show();
	}
};
}
