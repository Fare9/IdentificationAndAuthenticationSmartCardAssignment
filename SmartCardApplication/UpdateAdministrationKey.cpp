#include "UpdateAdministrationKey.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormUpdateAdministrationKey(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::UpdateAdministrationKey form;

	Application::Run(% form);
}