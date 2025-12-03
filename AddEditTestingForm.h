#pragma once
#include "ProductionSystemWrapper.h"

namespace CW {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AddEditTestingForm : public System::Windows::Forms::Form
    {
    public:
        property TestingData^ ResultData;

        AddEditTestingForm(TestingData^ inputData)
        {
            InitializeComponent();
            ResultData = inputData;

            if (inputData != nullptr) {
                this->Text = "Редагувати Випробування: " + inputData->Id;

                // 1. Поля ProductionProcess (Базові)
                txtId->Text = inputData->Id;
                txtId->ReadOnly = true;
                txtDuration->Text = inputData->Duration.ToString();
                txtWorkers->Text = inputData->Workers.ToString();
                txtLocation->Text = inputData->Location;

                // 2. Поля TestingProcess (Строкові)
                txtTestType->Text = inputData->TestType;
                txtParameters->Text = inputData->Parameters;
                txtStatus->Text = inputData->Status;

                // 3. Поля Аналізу (Кількісні та Булеві)
                txtMaxLoad->Text = inputData->MaxLoad.ToString();
                txtMeasuredTolerance->Text = inputData->MeasuredTolerance.ToString();
                txtTargetTolerance->Text = inputData->TargetTolerance.ToString();
                checkPassedSafety->Checked = inputData->HasPassedSafety;
            }
            else {
                this->Text = "Додати нове Випробування";
                txtId->ReadOnly = false;
            }
        }

    protected:
        ~AddEditTestingForm()
        {
            if (components)
            {
                delete components;
            }
        }

        // --- Приватні поля (ПЕРЕЙМЕНОВАНІ ДЛЯ ЧИТАБЕЛЬНОСТІ) ---
    private: System::Windows::Forms::Label^ lblId;
    private: System::Windows::Forms::TextBox^ txtId;
    private: System::Windows::Forms::Label^ lblDuration;
    private: System::Windows::Forms::TextBox^ txtDuration;
    private: System::Windows::Forms::Label^ lblWorkers;
    private: System::Windows::Forms::TextBox^ txtWorkers;
    private: System::Windows::Forms::Label^ lblLocation;
    private: System::Windows::Forms::TextBox^ txtLocation;

           // --- ПОЛЯ TestingProcess (Строкові) ---
    private: System::Windows::Forms::Label^ lblTestType;
    private: System::Windows::Forms::TextBox^ txtTestType;
    private: System::Windows::Forms::Label^ lblParameters;
    private: System::Windows::Forms::TextBox^ txtParameters;
    private: System::Windows::Forms::Label^ lblStatus;
    private: System::Windows::Forms::TextBox^ txtStatus;

           // --- ПОЛЯ Аналізу (Кількісні) ---
    private: System::Windows::Forms::Label^ lblMaxLoad;
    private: System::Windows::Forms::TextBox^ txtMaxLoad;
    private: System::Windows::Forms::Label^ lblMeasuredTolerance;
    private: System::Windows::Forms::TextBox^ txtMeasuredTolerance;
    private: System::Windows::Forms::Label^ lblTargetTolerance;
    private: System::Windows::Forms::TextBox^ txtTargetTolerance;
    private: System::Windows::Forms::Label^ lblPassedSafety;
    private: System::Windows::Forms::CheckBox^ checkPassedSafety;


    private: System::Windows::Forms::Button^ btnOK;
    private: System::Windows::Forms::Button^ btnCancel;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               // Створюємо всі компоненти
               this->lblId = (gcnew System::Windows::Forms::Label());
               this->txtId = (gcnew System::Windows::Forms::TextBox());
               this->lblDuration = (gcnew System::Windows::Forms::Label());
               this->txtDuration = (gcnew System::Windows::Forms::TextBox());
               this->lblWorkers = (gcnew System::Windows::Forms::Label());
               this->txtWorkers = (gcnew System::Windows::Forms::TextBox());
               this->lblLocation = (gcnew System::Windows::Forms::Label());
               this->txtLocation = (gcnew System::Windows::Forms::TextBox());

               this->lblTestType = (gcnew System::Windows::Forms::Label());
               this->txtTestType = (gcnew System::Windows::Forms::TextBox());
               this->lblParameters = (gcnew System::Windows::Forms::Label());
               this->txtParameters = (gcnew System::Windows::Forms::TextBox());
               this->lblStatus = (gcnew System::Windows::Forms::Label());
               this->txtStatus = (gcnew System::Windows::Forms::TextBox());

               this->lblMaxLoad = (gcnew System::Windows::Forms::Label());
               this->txtMaxLoad = (gcnew System::Windows::Forms::TextBox());
               this->lblMeasuredTolerance = (gcnew System::Windows::Forms::Label());
               this->txtMeasuredTolerance = (gcnew System::Windows::Forms::TextBox());
               this->lblTargetTolerance = (gcnew System::Windows::Forms::Label());
               this->txtTargetTolerance = (gcnew System::Windows::Forms::TextBox());
               this->lblPassedSafety = (gcnew System::Windows::Forms::Label());
               this->checkPassedSafety = (gcnew System::Windows::Forms::CheckBox());

               this->btnOK = (gcnew System::Windows::Forms::Button());
               this->btnCancel = (gcnew System::Windows::Forms::Button());

               this->SuspendLayout();
               this->ClientSize = System::Drawing::Size(660, 420); // Збільшений розмір для 11 полів
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->MaximizeBox = false;
               this->MinimizeBox = false;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->BackColor = System::Drawing::Color::WhiteSmoke;

               // Константи для розташування
               int labelWidth = 150;
               int inputWidth = 150;
               int x1 = 10;
               int x2 = 330;
               int yStart = 20;
               int yStep = 30;
               int y = yStart;

               // Привласнення розмірів і вирівнювання (задаємо для всіх елементів)
               System::Drawing::Size labelSz = System::Drawing::Size(labelWidth, 20);
               System::Drawing::Size inputSz = System::Drawing::Size(inputWidth, 20);

               // ============ СТОВПЕЦЬ 1: ProductionProcess & Строкові поля ============

               // ID
               this->lblId->Text = L"ID процесу:";
               this->lblId->Location = System::Drawing::Point(x1, y);
               this->lblId->Size = labelSz; this->lblId->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblId);
               this->txtId->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtId->Size = inputSz;
               this->Controls->Add(this->txtId); y += yStep;

               // Тривалість (Duration)
               this->lblDuration->Text = L"Тривалість (год):";
               this->lblDuration->Location = System::Drawing::Point(x1, y);
               this->lblDuration->Size = labelSz; this->lblDuration->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblDuration);
               this->txtDuration->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtDuration->Size = inputSz;
               this->Controls->Add(this->txtDuration); y += yStep;

               // Працівники (Workers)
               this->lblWorkers->Text = L"К-ть працівників:";
               this->lblWorkers->Location = System::Drawing::Point(x1, y);
               this->lblWorkers->Size = labelSz; this->lblWorkers->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblWorkers);
               this->txtWorkers->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtWorkers->Size = inputSz;
               this->Controls->Add(this->txtWorkers); y += yStep;

               // Місцезнаходження (Location)
               this->lblLocation->Text = L"Місцезнаходження:";
               this->lblLocation->Location = System::Drawing::Point(x1, y);
               this->lblLocation->Size = labelSz; this->lblLocation->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblLocation);
               this->txtLocation->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtLocation->Size = inputSz;
               this->Controls->Add(this->txtLocation); y += yStep;

               // Тип випробування (TestType)
               this->lblTestType->Text = L"Тип випробування:";
               this->lblTestType->Location = System::Drawing::Point(x1, y);
               this->lblTestType->Size = labelSz; this->lblTestType->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblTestType);
               this->txtTestType->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtTestType->Size = inputSz;
               this->Controls->Add(this->txtTestType); y += yStep;

               // Параметри випробування (Parameters)
               this->lblParameters->Text = L"Параметри:";
               this->lblParameters->Location = System::Drawing::Point(x1, y);
               this->lblParameters->Size = labelSz; this->lblParameters->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblParameters);
               this->txtParameters->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtParameters->Size = inputSz;
               this->Controls->Add(this->txtParameters); y += yStep;

               // Статус (Status)
               this->lblStatus->Text = L"Статус:";
               this->lblStatus->Location = System::Drawing::Point(x1, y);
               this->lblStatus->Size = labelSz; this->lblStatus->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblStatus);
               this->txtStatus->Location = System::Drawing::Point(x1 + labelWidth + 5, y);
               this->txtStatus->Size = inputSz;
               this->Controls->Add(this->txtStatus);

               // ============ СТОВПЕЦЬ 2: Поля Аналізу ============
               y = yStart; // Скидаємо Y на початок

               // Макс. навантаження (MaxLoad)
               this->lblMaxLoad->Text = L"Макс. навантаження:";
               this->lblMaxLoad->Location = System::Drawing::Point(x2, y);
               this->lblMaxLoad->Size = labelSz; this->lblMaxLoad->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblMaxLoad);
               this->txtMaxLoad->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->txtMaxLoad->Size = inputSz;
               this->Controls->Add(this->txtMaxLoad); y += yStep;

               // Виміряна точність (MeasuredTolerance)
               this->lblMeasuredTolerance->Text = L"Виміряна точність:";
               this->lblMeasuredTolerance->Location = System::Drawing::Point(x2, y);
               this->lblMeasuredTolerance->Size = labelSz; this->lblMeasuredTolerance->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblMeasuredTolerance);
               this->txtMeasuredTolerance->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->txtMeasuredTolerance->Size = inputSz;
               this->Controls->Add(this->txtMeasuredTolerance); y += yStep;

               // Цільовий допуск (TargetTolerance)
               this->lblTargetTolerance->Text = L"Цільовий допуск:";
               this->lblTargetTolerance->Location = System::Drawing::Point(x2, y);
               this->lblTargetTolerance->Size = labelSz; this->lblTargetTolerance->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblTargetTolerance);
               this->txtTargetTolerance->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->txtTargetTolerance->Size = inputSz;
               this->Controls->Add(this->txtTargetTolerance); y += yStep;

               // Пройдено безпеку (HasPassedSafety) - CheckBox
               this->lblPassedSafety->Text = L"Пройдено безпеку:";
               this->lblPassedSafety->Location = System::Drawing::Point(x2, y);
               this->lblPassedSafety->Size = labelSz; this->lblPassedSafety->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
               this->Controls->Add(this->lblPassedSafety);
               this->checkPassedSafety->Location = System::Drawing::Point(x2 + labelWidth + 5, y);
               this->checkPassedSafety->Size = System::Drawing::Size(20, 20);
               this->Controls->Add(this->checkPassedSafety);

               // --- КНОПКИ (У нижній частині форми) ---
               int btnY = 360;
               int btnWidth = 100;
               int btnSpacing = 20;

               this->btnOK->Text = L"OK";
               this->btnOK->Location = System::Drawing::Point(660 - btnWidth * 2 - btnSpacing * 2, btnY);
               this->btnOK->Size = System::Drawing::Size(btnWidth, 30);
               this->btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
               this->btnOK->Click += gcnew System::EventHandler(this, &AddEditTestingForm::btnOK_Click);
               this->Controls->Add(this->btnOK);

               this->btnCancel->Text = L"Скасувати";
               this->btnCancel->Location = System::Drawing::Point(660 - btnWidth - btnSpacing, btnY);
               this->btnCancel->Size = System::Drawing::Size(btnWidth, 30);
               this->btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
               this->btnCancel->Click += gcnew System::EventHandler(this, &AddEditTestingForm::btnCancel_Click);
               this->Controls->Add(this->btnCancel);

               this->ResumeLayout(false);
               this->PerformLayout();
           }
#pragma endregion

           // --- Обробник кнопки OK (Логіка перевірки та збору даних) ---
    private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            // 1. Базова перевірка строкових полів
            if (txtId->Text->Length == 0 || txtLocation->Text->Length == 0 || txtStatus->Text->Length == 0) {
                throw gcnew Exception("Поля ID, Місцезнаходження та Статус не можуть бути порожніми.");
            }

            // 2. Спроба парсингу числових даних
            double duration = Double::Parse(txtDuration->Text);
            int workers = Int32::Parse(txtWorkers->Text);

            // Парсинг нових числових полів
            double maxLoad = Double::Parse(txtMaxLoad->Text);
            double measuredTolerance = Double::Parse(txtMeasuredTolerance->Text);
            double targetTolerance = Double::Parse(txtTargetTolerance->Text);


            // 3. Перевірка числових обмежень
            if (duration <= 0 || workers <= 0) {
                throw gcnew Exception("Тривалість та працівники повинні бути більші за 0.");
            }
            if (targetTolerance < 0) {
                throw gcnew Exception("Цільовий допуск не може бути від'ємним.");
            }

            // 4. Створення/оновлення об'єкта ResultData
            if (ResultData == nullptr) {
                ResultData = gcnew TestingData();
            }

            // --- ПРИСВОЄННЯ ЗНАЧЕНЬ ---

            // Базові/Строкові поля
            ResultData->Id = txtId->Text;
            ResultData->Duration = duration;
            ResultData->Workers = workers;
            ResultData->Location = txtLocation->Text;
            ResultData->TestType = txtTestType->Text;
            ResultData->Parameters = txtParameters->Text;
            ResultData->Status = txtStatus->Text;

            // Поля Аналізу
            ResultData->MaxLoad = maxLoad;
            ResultData->MeasuredTolerance = measuredTolerance;
            ResultData->TargetTolerance = targetTolerance;
            ResultData->HasPassedSafety = checkPassedSafety->Checked; // Отримуємо булеве значення з CheckBox

            // Закриття форми
            this->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Невірний формат або значення даних. " + ex->Message,
                "Помилка вводу", MessageBoxButtons::OK, MessageBoxIcon::Error);

            this->DialogResult = System::Windows::Forms::DialogResult::None;
        }
    }

    private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e) {
        this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Close();
    }
    };
}