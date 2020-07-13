#include "ReadingNameForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void initFormReadingName(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::ReadingNameForm form;

	Application::Run(% form);
}