#pragma once
#include "ProductionSystemWrapper.h"

namespace CW {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class AddEditPackagingForm : public System::Windows::Forms::Form
    {
    public:
        property LaptopData^ ResultData; // Змінили на LaptopData

        AddEditPackagingForm(LaptopData^ inputData)
        {
            InitializeComponent();
            ResultData = inputData;

            if (inputData != nullptr) {
                this->Text = "Редагувати Ноутбук";
                txtType->Text = inputData->Type; txtType->ReadOnly = true;
                txtOS->Text = inputData->OS;
                txtBrand->Text = inputData->Brand;
                txtPrice->Text = inputData->Price.ToString();
                txtKeyb->Text = inputData->KeyboardType;
                txtAudio->Text = inputData->AudioInfo;
                txtWire->Text = inputData->Wireless;
            }
            else {
                this->Text = "Додати Ноутбук";
            }
        }

    protected:
        ~AddEditPackagingForm() { if (components) delete components; }

    private: System::Windows::Forms::TextBox^ txtType;
    private: System::Windows::Forms::TextBox^ txtOS;
    private: System::Windows::Forms::TextBox^ txtBrand;
    private: System::Windows::Forms::TextBox^ txtPrice;

           // Специфічні
    private: System::Windows::Forms::TextBox^ txtKeyb;
    private: System::Windows::Forms::TextBox^ txtAudio;
    private: System::Windows::Forms::TextBox^ txtWire;

    private: System::Windows::Forms::Button^ btnOK;
    private: System::Windows::Forms::Button^ btnCancel;
    private: System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
           void InitializeComponent(void)
           {
               this->ClientSize = System::Drawing::Size(400, 350);
               this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
               int y = 20; int lblW = 120; int txtW = 200; int gap = 35;

               AddField("Модель (Type):", txtType, y, lblW, txtW, gap);
               AddField("ОС:", txtOS, y, lblW, txtW, gap);
               AddField("Бренд:", txtBrand, y, lblW, txtW, gap);
               AddField("Ціна:", txtPrice, y, lblW, txtW, gap);
               AddField("Клавіатура:", txtKeyb, y, lblW, txtW, gap);
               AddField("Аудіо:", txtAudio, y, lblW, txtW, gap);
               AddField("Бездрот. зв'язок:", txtWire, y, lblW, txtW, gap);

               btnOK = gcnew Button(); btnOK->Text = "OK"; btnOK->Location = Point(180, y); btnOK->DialogResult = System::Windows::Forms::DialogResult::OK;
               btnOK->Click += gcnew EventHandler(this, &AddEditPackagingForm::btnOK_Click);

               btnCancel = gcnew Button(); btnCancel->Text = "Cancel"; btnCancel->Location = Point(270, y);
               this->Controls->Add(btnOK); this->Controls->Add(btnCancel);
           }
#pragma endregion

    private: System::Void btnOK_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            if (String::IsNullOrWhiteSpace(txtType->Text)) throw gcnew Exception("Введіть модель!");
            double price = Double::Parse(txtPrice->Text);

            if (ResultData == nullptr) ResultData = gcnew LaptopData();

            ResultData->Type = txtType->Text;
            ResultData->OS = txtOS->Text;
            ResultData->Brand = txtBrand->Text;
            ResultData->Price = price;
            ResultData->KeyboardType = txtKeyb->Text;
            ResultData->AudioInfo = txtAudio->Text;
            ResultData->Wireless = txtWire->Text;

            this->Close();
        }
        catch (Exception^ ex) {
            MessageBox::Show("Помилка: " + ex->Message);
            this->DialogResult = System::Windows::Forms::DialogResult::None;
        }
    }

    private: void AddField(System::String^ name, System::Windows::Forms::TextBox^% txt, int& y, int lblW, int txtW, int gap)
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
    y += gap;
}
    };
}