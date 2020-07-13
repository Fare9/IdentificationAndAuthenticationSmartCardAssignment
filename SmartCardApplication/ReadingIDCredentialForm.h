#pragma once

namespace SmartCardApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ReadingIDCredentialForm
	/// </summary>
	public ref class ReadingIDCredentialForm : public System::Windows::Forms::Form
	{
	public:
		ReadingIDCredentialForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		void setIDCredential(const char* id_credential)
		{
			System::String^ stringP;

			stringP = % System::String(id_credential);

			IDCredentialTextBox->Text = stringP;
		}

		void setParentForm(System::Windows::Forms::Form^ parentForm)
		{
			this->parentForm = parentForm;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ReadingIDCredentialForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Form^ parentForm;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ IDCredentialTextBox;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ReadingIDCredentialForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->IDCredentialTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(93, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"ID Credential:";
			// 
			// IDCredentialTextBox
			// 
			this->IDCredentialTextBox->Location = System::Drawing::Point(50, 93);
			this->IDCredentialTextBox->Name = L"IDCredentialTextBox";
			this->IDCredentialTextBox->ReadOnly = true;
			this->IDCredentialTextBox->Size = System::Drawing::Size(404, 22);
			this->IDCredentialTextBox->TabIndex = 4;
			// 
			// ReadingIDCredentialForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(490, 145);
			this->Controls->Add(this->IDCredentialTextBox);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"ReadingIDCredentialForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"ReadingIDCredentialForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ReadingIDCredentialForm::ReadingNameForm_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void ReadingNameForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		parentForm->Enabled = true;
	}

	};
}
