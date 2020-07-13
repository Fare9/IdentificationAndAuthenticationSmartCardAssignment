#include "SecretCodePasswordForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initSecretCodePasswordForm(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::SecretCodePasswordForm form;

	Application::Run(% form);
}