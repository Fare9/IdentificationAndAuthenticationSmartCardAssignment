#include "SmartCardForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormSmartCard(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::SmartCardForm form;

	Application::Run(% form);
}