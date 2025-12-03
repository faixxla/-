#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
   /* setlocale(LC_ALL, "ukr");
    system("chcp 65001");*/
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    CW::MyForm form;
    Application::Run(% form);
}