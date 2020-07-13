#include "PersonalizeSCForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void initFormPersonalizeSC(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	SmartCardApplication::PersonalizeSCForm form;
	Application::Run(% form);
}