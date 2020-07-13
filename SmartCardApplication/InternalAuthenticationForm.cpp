#include "InternalAuthenticationForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormInternalAuthentication(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::InternalAuthenticationForm form;

	Application::Run(% form);
}