#include "ReadingIDCredentialForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormReadingIDCredential(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::ReadingIDCredentialForm form;

	Application::Run(% form);
}