#pragma once

#include "DeviceManager.h"
#include "SmartCardForm.h"

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ SCReadersComboBox;
	protected:

	private:
		/// My variables
		DeviceManager *dm;
		int selected_index = -1;
		SmartCardForm smartcardform;


	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ connectButton;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SCReadersComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->connectButton = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(85, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(443, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"SmartCard Reader Application for Identification & Authentication UC3M";
			// 
			// SCReadersComboBox
			// 
			this->SCReadersComboBox->FormattingEnabled = true;
			this->SCReadersComboBox->Location = System::Drawing::Point(21, 224);
			this->SCReadersComboBox->Name = L"SCReadersComboBox";
			this->SCReadersComboBox->Size = System::Drawing::Size(632, 24);
			this->SCReadersComboBox->TabIndex = 1;
			this->SCReadersComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::SCReadersComboBox_SelectedIndexChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(18, 192);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(129, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Select your reader:";
			// 
			// connectButton
			// 
			this->connectButton->Location = System::Drawing::Point(546, 126);
			this->connectButton->Name = L"connectButton";
			this->connectButton->Size = System::Drawing::Size(130, 54);
			this->connectButton->TabIndex = 3;
			this->connectButton->Text = L"Connect with card";
			this->connectButton->UseVisualStyleBackColor = true;
			this->connectButton->Click += gcnew System::EventHandler(this, &MainForm::connectButton_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->connectButton);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->SCReadersComboBox);
			this->groupBox1->Location = System::Drawing::Point(34, 64);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(708, 269);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"SmartCard Application";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(101, 154);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(144, 17);
			this->label5->TabIndex = 7;
			this->label5->Text = L"Jorge Sánchez Freire";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(100, 126);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(188, 17);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Eduardo Blázquez González";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(85, 103);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(61, 17);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Authors:";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(659, 224);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(32, 32);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainForm::pictureBox1_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(778, 362);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SmartCard";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	 
	// Load function, necessary to check all readers
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		// Start the device manager
		dm = new DeviceManager();

		// Fill the data for the readers
		dm->ObtainReaders();
		std::vector<LPSTR> readers = dm->getReaders();
		for (size_t i = 0; i < readers.size(); i++)
		{
			System::String^ a = % System::String(readers[i]);
			SCReadersComboBox->Items->Add(a);
		}
	}

	// Executed each time user select different reader
	private: System::Void SCReadersComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		selected_index = SCReadersComboBox->SelectedIndex;
		printf("Selected index has changed to: %d\n", selected_index);
	}

	// Once user connects to the reader and starts connection with the smart card
	private: System::Void connectButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (selected_index == -1)
		{
			/***
			*	If there's no selected index, disable possible actions
			*	show error message, and once selected, enable actions
			*	again.
			*/
			SCReadersComboBox->Enabled = false;
			connectButton->Enabled = false;
			MessageBoxA(NULL, "Please specify a reader", "Error", MB_OK);
			SCReadersComboBox->Enabled = true;
			connectButton->Enabled = true;

		}
		else
		{
			// Selected the index

			// select the choosen by user from the vector
			dm->SetSelectedReader(dm->getReaders()[selected_index]);
				

			// disable actions
			SCReadersComboBox->Enabled = false;
			connectButton->Enabled = false;

			// check if card is present, if user tries to do something weird
			// continue complaining
			if (dm->WaitForCardPresent() == -1)
			{
				MessageBoxA(NULL, "Please insert the card in the reader", "Warning", MB_OK);

				// enable actions again
				SCReadersComboBox->Enabled = true;
				connectButton->Enabled = true;
				return;
			}
				
			// activate card now that card is present
			dm->ActivateCard();
			dm->ReleaseMemory();

			// now show new form and hide this one
			smartcardform.Show();
			smartcardform.InitVariables(dm, this);

			this->Hide();
		}
	}

	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
		SCReadersComboBox->Items->Clear();
		// Fill the data for the readers
		dm->ObtainReaders();
		std::vector<LPSTR> readers = dm->getReaders();

		for (size_t i = 0; i < readers.size(); i++)
		{
			System::String^ a = % System::String(readers[i]);
			SCReadersComboBox->Items->Add(a);
		}
	}

};
}
