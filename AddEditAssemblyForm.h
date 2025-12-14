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
        property PhoneData^ ResultData; // Змінили на PhoneData

        AddEditAssemblyForm(PhoneData^ inputData)
        {
            InitializeComponent();
            ResultData = inputData;

            if (inputData != nullptr) {
                this->Text = "Редагувати Телефон: " + inputData->Type;

                // Заповнюємо поля
                txtType->Text = inputData->Type;
                txtType->ReadOnly = true; // Тип (як ID) не змінюємо при редагуванні

                txtOS->Text = inputData->OS;
                txtBrand->Text = inputData->Brand;
                txtPrice->Text = inputData->Price.ToString();
                txtScreen->Text = inputData->ScreenSize.ToString();
                txtSim->Text = inputData->SimType;
                txtBattery->Text = inputData->Battery;
            }
            else {
                this->Text = "Додати новий Телефон";
                txtType->ReadOnly = false;
            }
        }

    protected:
        ~AddEditAssemblyForm()
        {
            if (components) delete components;
        }

        // --- Поля форми ---
    private: System::Windows::Forms::Label^ lblType;
    private: System::Windows::Forms::TextBox^ txtType;
    private: System::Windows::Forms::Label^ lblOS;
    private: System::Windows::Forms::TextBox^ txtOS;
    private: System::Windows::Forms::Label^ lblBrand;
    private: System::Windows::Forms::TextBox^ txtBrand;
    private: System::Windows::Forms::Label^ lblPrice;
    private: System::Windows::Forms::TextBox^ txtPrice;

           // Специфічні для телефону
    private: System::Windows::Forms::Label^ lblScreen;
    private: System::Windows::Forms::TextBox^ txtScreen;
    private: System::Windows::Forms::Label^ lblSim;
    private: System::Windows::Forms::TextBox^ txtSim;
    private: System::Windows::Forms::Label^ lblBattery;
    private: System::Windows::Forms::TextBox^ txtBattery;

    private: System::Windows::Forms::Button^ btnOK;
    private: System::Windows::Forms::Button^ btnCancel;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->SuspendLayout();
               this->ClientSize = System::Drawing::Size(400, 350);
               this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               this->Text = L"Телефон";

               int y = 20; int lblW = 120; int txtW = 200; int gap = 35;

               // Type
               lblType = gcnew Label(); lblType->Text = "Модель (Type):"; lblType->Location = Point(10, y); lblType->Size = System::Drawing::Size(lblW, 20);
               txtType = gcnew TextBox(); txtType->Location = Point(140, y); txtType->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblType); this->Controls->Add(txtType); y += gap;

               // OS
               lblOS = gcnew Label(); lblOS->Text = "ОС (Android/iOS):"; lblOS->Location = Point(10, y); lblOS->Size = System::Drawing::Size(lblW, 20);
               txtOS = gcnew TextBox(); txtOS->Location = Point(140, y); txtOS->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblOS); this->Controls->Add(txtOS); y += gap;

               // Brand
               lblBrand = gcnew Label(); lblBrand->Text = "Бренд:"; lblBrand->Location = Point(10, y); lblBrand->Size = System::Drawing::Size(lblW, 20);
               txtBrand = gcnew TextBox(); txtBrand->Location = Point(140, y); txtBrand->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblBrand); this->Controls->Add(txtBrand); y += gap;

               // Price
               lblPrice = gcnew Label(); lblPrice->Text = "Ціна:"; lblPrice->Location = Point(10, y); lblPrice->Size = System::Drawing::Size(lblW, 20);
               txtPrice = gcnew TextBox(); txtPrice->Location = Point(140, y); txtPrice->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblPrice); this->Controls->Add(txtPrice); y += gap;

               // Screen
               lblScreen = gcnew Label(); lblScreen->Text = "Діагональ:"; lblScreen->Location = Point(10, y); lblScreen->Size = System::Drawing::Size(lblW, 20);
               txtScreen = gcnew TextBox(); txtScreen->Location = Point(140, y); txtScreen->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblScreen); this->Controls->Add(txtScreen); y += gap;

               // SIM
               lblSim = gcnew Label(); lblSim->Text = "Тип SIM:"; lblSim->Location = Point(10, y); lblSim->Size = System::Drawing::Size(lblW, 20);
               txtSim = gcnew TextBox(); txtSim->Location = Point(140, y); txtSim->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblSim); this->Controls->Add(txtSim); y += gap;

               // Battery
               lblBattery = gcnew Label(); lblBattery->Text = "Батарея:"; lblBattery->Location = Point(10, y); lblBattery->Size = System::Drawing::Size(lblW, 20);
               txtBattery = gcnew TextBox(); txtBattery->Location = Point(140, y); txtBattery->Size = System::Drawing::Size(txtW, 20);
               this->Controls->Add(lblBattery); this->Controls->Add(txtBattery); y += gap + 10;

               // Buttons
               btnOK = gcnew Button(); btnOK->Text = "OK"; btnOK->Location = Point(180, y); btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
               btnOK->Click += gcnew EventHandler(this, &AddEditAssemblyForm::btnOK_Click);

               btnCancel = gcnew Button(); btnCancel->Text = "Cancel"; btnCancel->Location = Point(270, y); btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;

               this->Controls->Add(btnOK); this->Controls->Add(btnCancel);
               this->ResumeLayout(false);
           }
#pragma endregion

    private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            // Валідація
            if (String::IsNullOrWhiteSpace(txtType->Text) || String::IsNullOrWhiteSpace(txtBrand->Text))
                throw gcnew Exception("Поля 'Модель' та 'Бренд' обов'язкові!");

            double price = Double::Parse(txtPrice->Text);
            double screen = Double::Parse(txtScreen->Text);

            if (price < 0 || screen <= 0) throw gcnew Exception("Ціна та екран мають бути додатніми числами.");

            if (ResultData == nullptr) ResultData = gcnew PhoneData();

            ResultData->Type = txtType->Text;
            ResultData->OS = txtOS->Text;
            ResultData->Brand = txtBrand->Text;
            ResultData->Price = price;
            ResultData->ScreenSize = screen;
            ResultData->SimType = txtSim->Text;
            ResultData->Battery = txtBattery->Text;

            this->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка: " + ex->Message);
            this->DialogResult = System::Windows::Forms::DialogResult::None;
        }
    }
    };
}