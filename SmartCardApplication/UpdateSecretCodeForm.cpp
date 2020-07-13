#include "UpdateSecretCodeForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormUpdateSecretCode(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::UpdateSecretCodeForm form;

	Application::Run(% form);
}