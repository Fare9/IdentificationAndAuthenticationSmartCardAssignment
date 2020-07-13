#pragma once

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ReadingNameForm
	/// </summary>
	public ref class ReadingNameForm : public System::Windows::Forms::Form
	{
	public:
		ReadingNameForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void setName(const char* name)
		{
			System::String^ stringP;

			stringP = % System::String(name);

			NameTextBox->Text = stringP;
		}

		void setSurName(const char* surname)
		{
			System::String^ stringP;

			stringP = % System::String(surname);

			SurnameTextBox->Text = stringP;
		}

		void setParentForm(System::Windows::Forms::Form^ parentForm)
		{
			this->parentForm = parentForm;
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ReadingNameForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ NameTextBox;
	private: System::Windows::Forms::TextBox^ SurnameTextBox;

	private:
		System::Windows::Forms::Form^ parentForm;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ReadingNameForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->NameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SurnameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(32, 41);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Name";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(32, 133);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 17);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Surname";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(180, 17);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Name written in Smart Card";
			// 
			// NameTextBox
			// 
			this->NameTextBox->Location = System::Drawing::Point(35, 75);
			this->NameTextBox->Name = L"NameTextBox";
			this->NameTextBox->ReadOnly = true;
			this->NameTextBox->Size = System::Drawing::Size(404, 22);
			this->NameTextBox->TabIndex = 3;
			// 
			// SurnameTextBox
			// 
			this->SurnameTextBox->Location = System::Drawing::Point(35, 171);
			this->SurnameTextBox->Name = L"SurnameTextBox";
			this->SurnameTextBox->ReadOnly = true;
			this->SurnameTextBox->Size = System::Drawing::Size(404, 22);
			this->SurnameTextBox->TabIndex = 4;
			// 
			// ReadingNameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(471, 221);
			this->Controls->Add(this->SurnameTextBox);
			this->Controls->Add(this->NameTextBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ReadingNameForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ReadingNameForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ReadingNameForm::ReadingNameForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void ReadingNameForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		parentForm->Enabled = true;
	}
};
}
