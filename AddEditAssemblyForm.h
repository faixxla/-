#pragma once
#include "ProductionSystemWrapper.h"

namespace CW {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AddEditAssemblyForm : public System::Windows::Forms::Form
    {
    public:
        property AssemblyData^ ResultData;

        AddEditAssemblyForm(AssemblyData^ inputData)
        {
            InitializeComponent();
            ResultData = inputData;

            if (inputData != nullptr) {
                this->Text = "Редагувати Збірку: " + inputData->Id;

                txtId->Text = inputData->Id;
                txtId->ReadOnly = true;

                txtDuration->Text = inputData->Duration.ToString();
                txtWorkers->Text = inputData->Workers.ToString();
                txtLocation->Text = inputData->Location;
                txtPartsCount->Text = inputData->PartsCount.ToString();
                txtAssemblyTime->Text = inputData->AssemblyTime.ToString();
                txtTool->Text = inputData->Tool;
            }
            else {
                this->Text = "Додати нову Збірку";
                txtId->ReadOnly = false;
            }
        }

    protected:
        ~AddEditAssemblyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private: System::Windows::Forms::Label^ lblId;
    private: System::Windows::Forms::TextBox^ txtId;

    private: System::Windows::Forms::Label^ lblDuration;
    private: System::Windows::Forms::TextBox^ txtDuration;

    private: System::Windows::Forms::Label^ lblWorkers;
    private: System::Windows::Forms::TextBox^ txtWorkers;

    private: System::Windows::Forms::Label^ lblLocation;
    private: System::Windows::Forms::TextBox^ txtLocation;

    private: System::Windows::Forms::Label^ lblPartsCount;
    private: System::Windows::Forms::TextBox^ txtPartsCount;

    private: System::Windows::Forms::Label^ lblAssemblyTime;
    private: System::Windows::Forms::TextBox^ txtAssemblyTime;

    private: System::Windows::Forms::Label^ lblTool;
    private: System::Windows::Forms::TextBox^ txtTool;

    private: System::Windows::Forms::Button^ btnOK;
    private: System::Windows::Forms::Button^ btnCancel;

    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->SuspendLayout();
               this->ClientSize = System::Drawing::Size(620, 300);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->MinimizeBox = false;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->BackColor = System::Drawing::Color::WhiteSmoke;

               int labelWidth = 150;
               int inputWidth = 150;
               int x1 = -10;
               int x2 = 290;
               int yStart = 20;
               int yStep = 40;
               int y = yStart;

               this->lblId = (gcnew System::Windows::Forms::Label());
               this->lblId->Text = L"ID процесу:";
               this->lblId->Location = System::Drawing::Point(x1, y);
               this->lblId->Size = System::Drawing::Size(labelWidth, 20);
               this->lblId->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblId);

               this->txtId = (gcnew System::Windows::Forms::TextBox());
               this->txtId->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtId->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtId);
               y += yStep;

               this->lblDuration = (gcnew System::Windows::Forms::Label());
               this->lblDuration->Text = L"Тривалість (год):";
               this->lblDuration->Location = System::Drawing::Point(x1, y);
               this->lblDuration->Size = System::Drawing::Size(labelWidth, 20);
               this->lblDuration->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblDuration);

               this->txtDuration = (gcnew System::Windows::Forms::TextBox());
               this->txtDuration->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtDuration->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtDuration);
               y += yStep;

               this->lblWorkers = (gcnew System::Windows::Forms::Label());
               this->lblWorkers->Text = L"К-ть працівників:";
               this->lblWorkers->Location = System::Drawing::Point(x1, y);
               this->lblWorkers->Size = System::Drawing::Size(labelWidth, 20);
               this->lblWorkers->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblWorkers);

               this->txtWorkers = (gcnew System::Windows::Forms::TextBox());
               this->txtWorkers->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtWorkers->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtWorkers);
               y += yStep;

               this->lblLocation = (gcnew System::Windows::Forms::Label());
               this->lblLocation->Text = L"Місцезнаходження:";
               this->lblLocation->Location = System::Drawing::Point(x1, y);
               this->lblLocation->Size = System::Drawing::Size(labelWidth, 20);
               this->lblLocation->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblLocation);

               this->txtLocation = (gcnew System::Windows::Forms::TextBox());
               this->txtLocation->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtLocation->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtLocation);

               y = yStart;

               this->lblPartsCount = (gcnew System::Windows::Forms::Label());
               this->lblPartsCount->Text = L"К-ть деталей:";
               this->lblPartsCount->Location = System::Drawing::Point(x2, y);
               this->lblPartsCount->Size = System::Drawing::Size(labelWidth, 20);
               this->lblPartsCount->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblPartsCount);

               this->txtPartsCount = (gcnew System::Windows::Forms::TextBox());
               this->txtPartsCount->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->txtPartsCount->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtPartsCount);
               y += yStep;

               this->lblAssemblyTime = (gcnew System::Windows::Forms::Label());
               this->lblAssemblyTime->Text = L"Час збирання (год):";
               this->lblAssemblyTime->Location = System::Drawing::Point(x2, y);
               this->lblAssemblyTime->Size = System::Drawing::Size(labelWidth, 20);
               this->lblAssemblyTime->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblAssemblyTime);

               this->txtAssemblyTime = (gcnew System::Windows::Forms::TextBox());
               this->txtAssemblyTime->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->txtAssemblyTime->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtAssemblyTime);
               y += yStep;

               this->lblTool = (gcnew System::Windows::Forms::Label());
               this->lblTool->Text = L"Інструмент:";
               this->lblTool->Location = System::Drawing::Point(x2, y);
               this->lblTool->Size = System::Drawing::Size(labelWidth, 20);
               this->lblTool->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblTool);

               this->txtTool = (gcnew System::Windows::Forms::TextBox());
               this->txtTool->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->txtTool->Size = System::Drawing::Size(inputWidth, 20);
               this->Controls->Add(this->txtTool);

               int btnY = 240;
               int btnWidth = 100;
               int btnSpacing = 20;

               this->btnOK = (gcnew System::Windows::Forms::Button());
               this->btnOK->Text = L"OK";
               this->btnOK->Location = System::Drawing::Point(620 - btnWidth * 2 - btnSpacing * 2, btnY);
               this->btnOK->Size = System::Drawing::Size(btnWidth, 30);
               this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
               this->btnOK->Click += gcnew System::EventHandler(this, &AddEditAssemblyForm::btnOK_Click);
               this->Controls->Add(this->btnOK);

               this->btnCancel = (gcnew System::Windows::Forms::Button());
               this->btnCancel->Text = L"Скасувати";
               this->btnCancel->Location = System::Drawing::Point(620 - btnWidth - btnSpacing, btnY);
               this->btnCancel->Size = System::Drawing::Size(btnWidth, 30);
               this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
               this->Controls->Add(this->btnCancel);

               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

    private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            if (txtId->Text->Length == 0 || txtLocation->Text->Length == 0 || txtTool->Text->Length == 0) {
                throw gcnew Exception("Поля ID, Місцезнаходження та Інструмент не можуть бути порожніми.");
            }

            double duration = Double::Parse(txtDuration->Text);
            int workers = Int32::Parse(txtWorkers->Text);
            int partsCount = Int32::Parse(txtPartsCount->Text);
            double assemblyTime = Double::Parse(txtAssemblyTime->Text);

            if (duration <= 0 || workers <= 0 || partsCount <= 0 || assemblyTime <= 0) {
                throw gcnew Exception("Тривалість, працівники, деталі та час збирання повинні бути більші за 0.");
            }

            if (ResultData == nullptr) {
                ResultData = gcnew AssemblyData();
            }

            ResultData->Id = txtId->Text;
            ResultData->Duration = duration;
            ResultData->Workers = workers;
            ResultData->Location = txtLocation->Text;
            ResultData->PartsCount = partsCount;
            ResultData->AssemblyTime = assemblyTime;
            ResultData->Tool = txtTool->Text;

            this->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Невірний формат або значення даних. " + ex->Message,
                "Помилка вводу", MessageBoxButtons::OK, MessageBoxIcon::Error);

            this->DialogResult = System::Windows::Forms::DialogResult::None;
        }
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }
    };
}