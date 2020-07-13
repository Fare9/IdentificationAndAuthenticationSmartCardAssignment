#include "UpdateNameForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormUpdateName(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::UpdateNameForm form;

	Application::Run(% form);
}