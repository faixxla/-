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
        property TabletData^ ResultData; // Змінили на TabletData

        AddEditTestingForm(TabletData^ inputData)
        {
            InitializeComponent();
            ResultData = inputData;

            if (inputData != nullptr) {
                this->Text = "Редагувати Планшет";
                txtType->Text = inputData->Type; txtType->ReadOnly = true;
                txtOS->Text = inputData->OS;
                txtBrand->Text = inputData->Brand;
                txtPrice->Text = inputData->Price.ToString();
                txtMemory->Text = inputData->Memory;
                txtMaterial->Text = inputData->Material;
                chkStylus->Checked = inputData->HasStylus;
            }
            else {
                this->Text = "Додати Планшет";
            }
        }

    protected:
        ~AddEditTestingForm() { if (components) delete components; }

    private: System::Windows::Forms::TextBox^ txtType;
    private: System::Windows::Forms::TextBox^ txtOS;
    private: System::Windows::Forms::TextBox^ txtBrand;
    private: System::Windows::Forms::TextBox^ txtPrice;

           // Специфічні
    private: System::Windows::Forms::TextBox^ txtMemory;
    private: System::Windows::Forms::TextBox^ txtMaterial;
    private: System::Windows::Forms::CheckBox^ chkStylus;

    private: System::Windows::Forms::Button^ btnOK;
    private: System::Windows::Forms::Button^ btnCancel;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->ClientSize = System::Drawing::Size(400, 350);
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               int y = 20; int lblW = 120; int txtW = 200; int gap = 35;

               // Helper function as a private method instead of a lambda
               AddField("Модель (Type):", txtType, y, lblW, txtW, gap);
               y += gap;
               AddField("ОС:", txtOS, y, lblW, txtW, gap);
               y += gap;
               AddField("Бренд:", txtBrand, y, lblW, txtW, gap);
               y += gap;
               AddField("Ціна:", txtPrice, y, lblW, txtW, gap);
               y += gap;
               AddField("Пам'ять:", txtMemory, y, lblW, txtW, gap);
               y += gap;
               AddField("Матеріал:", txtMaterial, y, lblW, txtW, gap);
               y += gap;

               // Checkbox Stylus
               Label^ lblS = gcnew Label(); lblS->Text = "Стілус?"; lblS->Location = Point(10, y);
               chkStylus = gcnew CheckBox(); chkStylus->Location = Point(140, y); chkStylus->Text = "Так, є підтримка"; chkStylus->AutoSize = true;
               this->Controls->Add(lblS); this->Controls->Add(chkStylus); y += gap + 10;

               btnOK = gcnew Button(); btnOK->Text = "OK"; btnOK->Location = Point(180, y); btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
               btnOK->Click += gcnew EventHandler(this, &AddEditTestingForm::btnOK_Click);

               btnCancel = gcnew Button(); btnCancel->Text = "Cancel"; btnCancel->Location = Point(270, y);

               this->Controls->Add(btnOK); this->Controls->Add(btnCancel);
           }

    // Add this private helper method to replace the lambda
    private: void AddField(System::String^ name, System::Windows::Forms::TextBox^% txt, int y, int lblW, int txtW, int gap)
    {
        System::Windows::Forms::Label^ lbl = gcnew System::Windows::Forms::Label();
        lbl->Text = name;
        lbl->Location = System::Drawing::Point(10, y);
        lbl->Size = System::Drawing::Size(lblW, 20);
        txt = gcnew System::Windows::Forms::TextBox();
        txt->Location = System::Drawing::Point(140, y);
        txt->Size = System::Drawing::Size(txtW, 20);
        this->Controls->Add(lbl);
        this->Controls->Add(txt);
    }
#pragma endregion

    private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            if (String::IsNullOrWhiteSpace(txtType->Text)) throw gcnew Exception("Введіть модель!");
            double price = Double::Parse(txtPrice->Text);

            if (ResultData == nullptr) ResultData = gcnew TabletData();

            ResultData->Type = txtType->Text;
            ResultData->OS = txtOS->Text;
            ResultData->Brand = txtBrand->Text;
            ResultData->Price = price;
            ResultData->Memory = txtMemory->Text;
            ResultData->Material = txtMaterial->Text;
            ResultData->HasStylus = chkStylus->Checked;

            this->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка: " + ex->Message);
            this->DialogResult = System::Windows::Forms::DialogResult::None;
        }
    }
    };
}