#include "UpdateIDCredentialForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void initUpdateIDCredentialForm(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::UpdateIDCredentialForm form;
	Application::Run(% form);
}