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
	/// Summary for PersonalizeSCForm
	/// </summary>
	public ref class PersonalizeSCForm : public System::Windows::Forms::Form
	{
	public:
		PersonalizeSCForm(void)
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
		~PersonalizeSCForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::TextBox^ AdministrativeKey;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ showPassword;
	private: System::Windows::Forms::TextBox^ SecretCode;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;

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

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::IO::FileSystemWatcher^ fileSystemWatcher1;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PersonalizeSCForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->AdministrativeKey = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->showPassword = (gcnew System::Windows::Forms::PictureBox());
			this->SecretCode = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->fileSystemWatcher1 = (gcnew System::IO::FileSystemWatcher());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(178, 50);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(180, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Smart Card Personalization";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(25, 107);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(147, 57);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Create Personal Data";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(352, 107);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(147, 57);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Set Personal Data Permissions";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(25, 203);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(147, 57);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Create ID Credential";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(352, 203);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(147, 57);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Set ID Credential Permissions";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(25, 296);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(147, 57);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Create Administrative Key";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(352, 296);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(147, 57);
			this->button6->TabIndex = 6;
			this->button6->Text = L"Set Administrative Key Permissions";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(25, 480);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(147, 57);
			this->button7->TabIndex = 7;
			this->button7->Text = L"Create NT File";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(352, 480);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(147, 57);
			this->button8->TabIndex = 8;
			this->button8->Text = L"Set NT File Permissions";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button8_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(25, 587);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(147, 57);
			this->button9->TabIndex = 9;
			this->button9->Text = L"Create Secret Code";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button9_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(352, 587);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(147, 57);
			this->button10->TabIndex = 10;
			this->button10->Text = L"Set Secret Code Permissions";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &PersonalizeSCForm::button10_Click);
			// 
			// AdministrativeKey
			// 
			this->AdministrativeKey->Location = System::Drawing::Point(25, 412);
			this->AdministrativeKey->MaxLength = 32;
			this->AdministrativeKey->Name = L"AdministrativeKey";
			this->AdministrativeKey->Size = System::Drawing::Size(404, 22);
			this->AdministrativeKey->TabIndex = 11;
			this->AdministrativeKey->Text = L"01020304050607080910111213141516";
			this->AdministrativeKey->UseSystemPasswordChar = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(22, 388);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(243, 17);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Administrative Key (16 hex numbers):";
			// 
			// showPassword
			// 
			this->showPassword->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"showPassword.Image")));
			this->showPassword->Location = System::Drawing::Point(435, 402);
			this->showPassword->Name = L"showPassword";
			this->showPassword->Size = System::Drawing::Size(33, 32);
			this->showPassword->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->showPassword->TabIndex = 13;
			this->showPassword->TabStop = false;
			this->showPassword->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PersonalizeSCForm::showAdministrativeKey_MouseDown);
			this->showPassword->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &PersonalizeSCForm::showAdministrativeKey_MouseUp);
			// 
			// SecretCode
			// 
			this->SecretCode->Location = System::Drawing::Point(25, 681);
			this->SecretCode->MaxLength = 16;
			this->SecretCode->Name = L"SecretCode";
			this->SecretCode->Size = System::Drawing::Size(404, 22);
			this->SecretCode->TabIndex = 14;
			this->SecretCode->Text = L"1122334455667788";
			this->SecretCode->UseSystemPasswordChar = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(22, 657);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(197, 17);
			this->label3->TabIndex = 15;
			this->label3->Text = L"Secret Code (8 hex numbers):";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(435, 671);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(33, 32);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 16;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &PersonalizeSCForm::showSecretCode_MouseDown);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &PersonalizeSCForm::showSecretCode_MouseUp);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(178, 127);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(151, 17);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Personal Data Present";
			this->label4->Visible = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(178, 223);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(142, 17);
			this->label5->TabIndex = 18;
			this->label5->Text = L"ID Credential Present";
			this->label5->Visible = false;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(178, 316);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(102, 17);
			this->label6->TabIndex = 19;
			this->label6->Text = L"A. Key Present";
			this->label6->Visible = false;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(178, 500);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(106, 17);
			this->label7->TabIndex = 20;
			this->label7->Text = L"NT File Present";
			this->label7->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(178, 607);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(139, 17);
			this->label8->TabIndex = 21;
			this->label8->Text = L"Secret Code Present";
			this->label8->Visible = false;
			// 
			// fileSystemWatcher1
			// 
			this->fileSystemWatcher1->EnableRaisingEvents = true;
			this->fileSystemWatcher1->SynchronizingObject = this;
			this->fileSystemWatcher1->Changed += gcnew System::IO::FileSystemEventHandler(this, &PersonalizeSCForm::fileSystemWatcher1_Changed);
			// 
			// PersonalizeSCForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(545, 715);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->SecretCode);
			this->Controls->Add(this->showPassword);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->AdministrativeKey);
			this->Controls->Add(this->button10);
			this->Controls->Add(this->button9);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"PersonalizeSCForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PersonalizeSCForm";
			this->Load += gcnew System::EventHandler(this, &PersonalizeSCForm::Form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->showPassword))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		System::Void Form_Load(System::Object^ sender, System::EventArgs^ e)
		{
			uint64_t lRetValue;


			lRetValue = cc->SelectEF(0x0001);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100) // check if Personal Data file exists
			{
				this->button1->Enabled = false;
				this->label4->Visible = true;
			}
			lRetValue = cc->SelectEF(0x0002);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100) // check if ID Credential exists
			{
				this->button3->Enabled = false;
				this->label5->Visible = true;
			}
			lRetValue = cc->SelectEF(0x0003);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100) // check if administrative key exists
			{
				this->button5->Enabled = false;
				this->label6->Visible = true;
				this->AdministrativeKey->Enabled = false;
			}
			lRetValue = cc->SelectEF(0x0004);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100) // check if NT exists
			{
				this->button7->Enabled = false;
				this->label7->Visible = true;
			}
			lRetValue = cc->SelectEF(0x0005);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100) // check if secret code exists
			{
				this->button9->Enabled = false;
				this->label8->Visible = true;
				this->SecretCode->Enabled = false;
			}

		}

		private: System::Void showAdministrativeKey_MouseDown(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
			this->AdministrativeKey->UseSystemPasswordChar = false;
		}

		private: System::Void showAdministrativeKey_MouseUp(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
			this->AdministrativeKey->UseSystemPasswordChar = true;
		}

		private: System::Void showSecretCode_MouseDown(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
			this->SecretCode->UseSystemPasswordChar = false;
		}

		private: System::Void showSecretCode_MouseUp(Object^ /*sender*/, System::Windows::Forms::MouseEventArgs^ e) {
			this->SecretCode->UseSystemPasswordChar = true;
		}

		// Create the personal data EF
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			uint64_t lRetValue = cc->CreateTransparentFile(0x0001, 30, cc->ACCESS_FREE, cc->ACCESS_FREE);
			this->button1->Enabled = false;
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Personal Data EF created successfully", "Success", MB_OK);
				this->label4->Visible = true;
			}
			else
			{
				MessageBoxA(NULL, "Error creating Personal Data EF", "Error", MB_OK);
				this->button1->Enabled = true;
			}
		}
		// Set Personal Data EF permissions
		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			uint64_t lRetValue = cc->SetAccessConditions(0x0001, true, cc->ACCESS_SECURE_MESSAGING);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Personal Data EF permissions updated", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Personal Data EF permissions error updating", "Error", MB_OK);
			}
		}

		// Create the ID Credential EF
		private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			uint64_t lRetValue = cc->CreateTransparentFile(0x0002, 16, cc->ACCESS_FREE, cc->ACCESS_FREE);
			this->button3->Enabled = false;
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "ID Credential created successfully", "Success", MB_OK);
				this->label5->Visible = true;
			}
			else
			{
				MessageBoxA(NULL, "Error creating ID Credential EF", "Error", MB_OK);
				this->button3->Enabled = true;
			}
		}
		// Set ID Credential EF Permissions
		private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
			uint64_t lRetValue1 = cc->SetAccessConditions(0x0002, true, cc->ACCESS_SECURE_MESSAGING);
			uint64_t lRetValue2 = cc->SetAccessConditions(0x0002, false, cc->ACCESS_SECRET_CODE);
			if ((lRetValue1 == 0x9000 || (lRetValue1 & 0xFF00) == 0x6100)
				&& (lRetValue2 == 0x9000 || (lRetValue2 & 0xFF00) == 0x6100))
			{
				MessageBoxA(NULL, "ID Credential EF permissions updated", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "ID Credential EF permissions error updating", "Error", MB_OK);
			}
		}
			   
		// Create Administrative Key EF
		private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			array<Char>^ administrative_keyP = this->AdministrativeKey->Text->ToCharArray();
			char aux_char[32];
			char administrative_key[16];
			memset(aux_char, 0, 32);
			memset(administrative_key, 0, 16);

			this->button5->Enabled = false;

			// check if number has 32 of length
			if (administrative_keyP->Length != 32)
			{
				MessageBoxA(NULL, "Administrative Key must be 16 hex numbers (32 nibbles)", "Error", MB_OK);
				this->button5->Enabled = true;
				return;
			}

			// check if every introduced characters is hexadecimal character
			for (size_t i = 0; i < administrative_keyP->Length; i++)
			{
				aux_char[i] = (char)administrative_keyP[i];

				if (!isxdigit(aux_char[i]))
				{
					MessageBoxA(NULL, "You introduced bad hex character", "Error", MB_OK);
					this->button9->Enabled = true;
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

			uint64_t lRetValue = cc->CreateAdministrativeKeyFile(0x0003, 16, cc->ACCESS_BLOCKED);

			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Administrative Key created successfully", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Error creating Administrative Key EF", "Error", MB_OK);
				this->button5->Enabled = true;
				return;
			}

			lRetValue = cc->UpdateBinarySecureMessage(0x0003, administrative_key, 16, 0, true);

			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Administrative Key written successfully", "Success", MB_OK);
				this->label6->Visible = true;
				this->AdministrativeKey->Enabled = false;
			}
			else
			{
				MessageBoxA(NULL, "Error writing Administrative Key", "Error", MB_OK);
				this->button5->Enabled = true;
			}
		}
		// Set Administrative Key EF permissions
		private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			uint64_t lRetValue = cc->SetAccessConditions(0x0003, false, cc->ACCESS_BLOCKED);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Administrative Key permissions changed successfully", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Error changing Administrative Key permissions", "Error", MB_OK);
			}
		}
		
		// Create NT file
		private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
			CHAR NT_value[2] = { 0x00, 0x00 };
			this->button7->Enabled = false;

			uint64_t lRetValue = cc->CreateNTFile(0x0004, 2, cc->ACCESS_FREE, cc->ACCESS_FREE);

			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "NT EF created successfully", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Error creating NT EF", "Error", MB_OK);
				this->button7->Enabled = true;
				return;
			}

			lRetValue = cc->UpdateBinary(0x0004, (const CHAR*)NT_value, 2, 0);
			
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "NT EF written successfully", "Success", MB_OK);
				this->label7->Visible = true;
			}
			else
			{
				MessageBoxA(NULL, "Error writing NT EF", "Error", MB_OK);
				this->button7->Enabled = true;
			}

			return;
		}
		// Set NT File permissions
		private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e) {
			uint64_t lRetValue = cc->SetAccessConditions(0x0004, true, cc->ACCESS_BLOCKED);
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "NT EF permissions changed successfully", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Error changing NT EF permissions", "Error", MB_OK);
			}
		}
			   
		// Create Secret Code EF
		private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
			array<Char>^ secret_codeP = this->SecretCode->Text->ToCharArray();
			char aux_char[16];
			char secret_code[8];
			memset(aux_char, 0, 16);
			memset(secret_code, 0, 8);

			this->button9->Enabled = false;

			// check if number has 16 of length
			if (secret_codeP->Length != 16)
			{
				MessageBoxA(NULL, "Secret Code must be 8 hex numbers (16 nibbles)", "Error", MB_OK);
				this->button9->Enabled = true;
				return;
			}

			// check if every introduced characters is hexadecimal character
			for (size_t i = 0; i < secret_codeP->Length; i++)
			{
				aux_char[i] = (char)secret_codeP[i];

				if (!isxdigit(aux_char[i]))
				{
					MessageBoxA(NULL, "You introduced bad hex character", "Error", MB_OK);
					this->button9->Enabled = true;
					return;
				}
			}

			// finally create the secret code
			size_t j = 0;
			for (size_t i = 0; i < 16; i += 2)
			{
				secret_code[j] = (aux_char[i] <= '9' ? aux_char[i] - '0' : toupper(aux_char[i]) - 'A' + 10) << 4;
				secret_code[j] |= aux_char[i+1] <= '9' ? aux_char[i+1] - '0' : toupper(aux_char[i + 1]) - 'A' + 10;
				j += 1;
			}

			uint64_t lRetValue = cc->CreateSecretCodeFile(0x0005, 8, cc->ACCESS_FREE);
			this->button9->Enabled = false;

			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Secret Code created successfully", "Success", MB_OK);	
			}
			else
			{
				MessageBoxA(NULL, "Error creating Secret Code EF", "Error", MB_OK);		
				return;
			}

			lRetValue = cc->UpdateBinarySecureMessage(0x0005, secret_code, 8, 0, true);

			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Secret Code written successfully", "Success", MB_OK);
				this->label8->Visible = true;
				this->SecretCode->Enabled = false;
			}
			else
			{
				MessageBoxA(NULL, "Error writing Secret Code", "Error", MB_OK);
				this->button9->Enabled = true;
			}
		}
		// Set Secret Code EF permissions
		private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {

			uint64_t lRetValue = cc->SetAccessConditions(0x0005, false, cc->ACCESS_BLOCKED);
			
			if (lRetValue == 0x9000 || (lRetValue & 0xFF00) == 0x6100)
			{
				MessageBoxA(NULL, "Secret Code permissions changed successfully", "Success", MB_OK);
			}
			else
			{
				MessageBoxA(NULL, "Error changing Secret Code permissions", "Error", MB_OK);
			}

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
				
private: System::Void fileSystemWatcher1_Changed(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
}
};
}
