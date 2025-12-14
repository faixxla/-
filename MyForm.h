#pragma once
#include "AddEditPackagingForm.h" // Тепер це форма для Ноутбука
#include "AddEditTestingForm.h"   // Тепер це форма для Планшета
#include "AddEditAssemblyForm.h"  // Тепер це форма для Телефона
#include "ProductionSystemWrapper.h"

namespace CW {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			wrapper = gcnew ProductionSystemWrapper();
			SetupAllControls();

			try {
				// Завантажуємо дані при старті
				wrapper->LoadFromFile(L"electronics_store.txt");
			}
			catch (Exception^ ex) {
				// Ігноруємо помилку при першому запуску, якщо файлу немає
			}
			ShowPhoneView(); // Стартуємо з вкладки Телефонів
		}

	protected:
		~MyForm()
		{
			if (components) delete components;
		}

	private: ProductionSystemWrapper^ wrapper;
	private: System::Windows::Forms::DataGridView^ mainDataGridView;

		   // --- Кнопки дій ---
	private: System::Windows::Forms::Button^ btnSingleSim; // Було MaxDuration
	private: System::Windows::Forms::Button^ btnAddPhone;
	private: System::Windows::Forms::Button^ btnEditPhone;

	private: System::Windows::Forms::Button^ btnFindStylus; // Було AnalyzeTests
	private: System::Windows::Forms::Button^ btnAddTablet;
	private: System::Windows::Forms::Button^ btnEditTablet;

	private: System::Windows::Forms::Button^ btnFindWifi;   // Було FindPacking
	private: System::Windows::Forms::Button^ btnAddLaptop;
	private: System::Windows::Forms::Button^ btnEditLaptop;

	private: System::Windows::Forms::Button^ btnSave;
	private: System::Windows::Forms::Button^ btnLoad;

		   // --- Елементи дизайну (меню зліва) ---
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnMenuPhone;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Button^ btnMenuTablet;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::Button^ btnMenuLaptop;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::PictureBox^ pictureBox9;

		   // --- Заголовки ---
	private: System::Windows::Forms::Label^ lblHeaderPhone;
	private: System::Windows::Forms::Label^ lblHeaderTablet;
	private: System::Windows::Forms::Label^ lblHeaderLaptop;

	private: System::ComponentModel::IContainer^ components;

		   // --- Допоміжні методи ---

		   void LoadDataGrid(System::Collections::IEnumerable^ dataList)
		   {
			   mainDataGridView->DataSource = nullptr;
			   mainDataGridView->DataSource = dataList;
			   mainDataGridView->AutoResizeColumns(DataGridViewAutoSizeColumnsMode::AllCells);
		   }

		   void HideAllFunctionalControls() {
			   // Ховаємо кнопки телефонів
			   btnSingleSim->Visible = false;
			   btnAddPhone->Visible = false;
			   btnEditPhone->Visible = false;
			   lblHeaderPhone->Visible = false;

			   // Ховаємо кнопки планшетів
			   btnFindStylus->Visible = false;
			   btnAddTablet->Visible = false;
			   btnEditTablet->Visible = false;
			   lblHeaderTablet->Visible = false;

			   // Ховаємо кнопки ноутбуків
			   btnFindWifi->Visible = false;
			   btnAddLaptop->Visible = false;
			   btnEditLaptop->Visible = false;
			   lblHeaderLaptop->Visible = false;
		   }

		   void ShowPhoneView() {
			   HideAllFunctionalControls();
			   LoadDataGrid(wrapper->GetAllPhones());
			   btnSingleSim->Visible = true;
			   btnAddPhone->Visible = true;
			   btnEditPhone->Visible = true;
			   lblHeaderPhone->Visible = true;
		   }

		   void ShowTabletView() {
			   HideAllFunctionalControls();
			   LoadDataGrid(wrapper->GetAllTablets());
			   btnFindStylus->Visible = true;
			   btnAddTablet->Visible = true;
			   btnEditTablet->Visible = true;
			   lblHeaderTablet->Visible = true;
		   }

		   void ShowLaptopView() {
			   HideAllFunctionalControls();
			   LoadDataGrid(wrapper->GetAllLaptops());
			   btnFindWifi->Visible = true;
			   btnAddLaptop->Visible = true;
			   btnEditLaptop->Visible = true;
			   lblHeaderLaptop->Visible = true;
		   }

		   void SetupAllControls() {
			   // Основна таблиця
			   mainDataGridView = gcnew System::Windows::Forms::DataGridView();
			   mainDataGridView->Location = System::Drawing::Point(370, 100);
			   mainDataGridView->Size = System::Drawing::Size(768, 300);
			   mainDataGridView->ReadOnly = true;
			   mainDataGridView->AutoGenerateColumns = true;
			   this->Controls->Add(mainDataGridView);

			   int y_pos = 410;
			   int x_pos = 370;

			   // === ТЕЛЕФОНИ ===
			   btnSingleSim = gcnew System::Windows::Forms::Button();
			   btnSingleSim->Text = L"Знайти з 1 SIM-картою";
			   btnSingleSim->Location = System::Drawing::Point(x_pos, y_pos);
			   btnSingleSim->Size = System::Drawing::Size(200, 40);
			   btnSingleSim->Click += gcnew System::EventHandler(this, &MyForm::btnSingleSim_Click);
			   this->Controls->Add(btnSingleSim);

			   btnAddPhone = gcnew System::Windows::Forms::Button();
			   btnAddPhone->Text = L"Додати Телефон";
			   btnAddPhone->Location = System::Drawing::Point(x_pos + 210, y_pos);
			   btnAddPhone->Size = System::Drawing::Size(150, 40);
			   btnAddPhone->Click += gcnew System::EventHandler(this, &MyForm::btnAddPhone_Click);
			   this->Controls->Add(btnAddPhone);

			   btnEditPhone = gcnew System::Windows::Forms::Button();
			   btnEditPhone->Text = L"Редагувати";
			   btnEditPhone->Location = System::Drawing::Point(x_pos + 370, y_pos);
			   btnEditPhone->Size = System::Drawing::Size(150, 40);
			   btnEditPhone->Click += gcnew System::EventHandler(this, &MyForm::btnEditPhone_Click);
			   this->Controls->Add(btnEditPhone);

			   // === ПЛАНШЕТИ ===
			   btnFindStylus = gcnew System::Windows::Forms::Button();
			   btnFindStylus->Text = L"Перевірка наявності стілуса";
			   btnFindStylus->Location = System::Drawing::Point(x_pos, y_pos);
			   btnFindStylus->Size = System::Drawing::Size(200, 40);
			   btnFindStylus->Click += gcnew System::EventHandler(this, &MyForm::btnFindStylus_Click);
			   this->Controls->Add(btnFindStylus);

			   btnAddTablet = gcnew System::Windows::Forms::Button();
			   btnAddTablet->Text = L"Додати Планшет";
			   btnAddTablet->Location = System::Drawing::Point(x_pos + 210, y_pos);
			   btnAddTablet->Size = System::Drawing::Size(150, 40);
			   btnAddTablet->Click += gcnew System::EventHandler(this, &MyForm::btnAddTablet_Click);
			   this->Controls->Add(btnAddTablet);

			   btnEditTablet = gcnew System::Windows::Forms::Button();
			   btnEditTablet->Text = L"Редагувати";
			   btnEditTablet->Location = System::Drawing::Point(x_pos + 370, y_pos);
			   btnEditTablet->Size = System::Drawing::Size(150, 40);
			   btnEditTablet->Click += gcnew System::EventHandler(this, &MyForm::btnEditTablet_Click);
			   this->Controls->Add(btnEditTablet);

			   // === НОУТБУКИ ===
			   btnFindWifi = gcnew System::Windows::Forms::Button();
			   btnFindWifi->Text = L"Перевірка підтримки Wi-Fi";
			   btnFindWifi->Location = System::Drawing::Point(x_pos, y_pos);
			   btnFindWifi->Size = System::Drawing::Size(200, 40);
			   btnFindWifi->Click += gcnew System::EventHandler(this, &MyForm::btnFindWifi_Click);
			   this->Controls->Add(btnFindWifi);

			   btnAddLaptop = gcnew System::Windows::Forms::Button();
			   btnAddLaptop->Text = L"Додати Ноутбук";
			   btnAddLaptop->Location = System::Drawing::Point(x_pos + 210, y_pos);
			   btnAddLaptop->Size = System::Drawing::Size(150, 40);
			   btnAddLaptop->Click += gcnew System::EventHandler(this, &MyForm::btnAddLaptop_Click);
			   this->Controls->Add(btnAddLaptop);

			   btnEditLaptop = gcnew System::Windows::Forms::Button();
			   btnEditLaptop->Text = L"Редагувати";
			   btnEditLaptop->Location = System::Drawing::Point(x_pos + 370, y_pos);
			   btnEditLaptop->Size = System::Drawing::Size(150, 40);
			   btnEditLaptop->Click += gcnew System::EventHandler(this, &MyForm::btnEditLaptop_Click);
			   this->Controls->Add(btnEditLaptop);

			   // === ЗАГАЛЬНІ ===
			   btnSave = gcnew System::Windows::Forms::Button();
			   btnSave->Text = L"Зберегти у файл";
			   btnSave->Location = System::Drawing::Point(x_pos, y_pos + 50);
			   btnSave->Size = System::Drawing::Size(200, 40);
			   btnSave->Click += gcnew System::EventHandler(this, &MyForm::btnSave_Click);
			   this->Controls->Add(btnSave);

			   btnLoad = gcnew System::Windows::Forms::Button();
			   btnLoad->Text = L"Завантажити";
			   btnLoad->Location = System::Drawing::Point(x_pos + 210, y_pos + 50);
			   btnLoad->Size = System::Drawing::Size(200, 40);
			   btnLoad->Click += gcnew System::EventHandler(this, &MyForm::btnLoad_Click);
			   this->Controls->Add(btnLoad);

			   HideAllFunctionalControls();
		   }

		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->btnMenuPhone = (gcnew System::Windows::Forms::Button());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			   this->btnMenuTablet = (gcnew System::Windows::Forms::Button());
			   this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			   this->btnMenuLaptop = (gcnew System::Windows::Forms::Button());
			   this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			   this->lblHeaderPhone = (gcnew System::Windows::Forms::Label());
			   this->lblHeaderTablet = (gcnew System::Windows::Forms::Label());
			   this->lblHeaderLaptop = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->BackColor = System::Drawing::SystemColors::Window;
			   this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			   this->pictureBox1->Location = System::Drawing::Point(21, 0);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(442, 199);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   // 
			   // btnMenuPhone
			   // 
			   this->btnMenuPhone->BackColor = System::Drawing::SystemColors::Window;
			   this->btnMenuPhone->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->btnMenuPhone->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->btnMenuPhone->Location = System::Drawing::Point(85, 205);
			   this->btnMenuPhone->Name = L"btnMenuPhone";
			   this->btnMenuPhone->Size = System::Drawing::Size(378, 53);
			   this->btnMenuPhone->TabIndex = 1;
			   this->btnMenuPhone->Text = L"Телефони";
			   this->btnMenuPhone->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnMenuPhone->UseVisualStyleBackColor = false;
			   this->btnMenuPhone->Click += gcnew System::EventHandler(this, &MyForm::btnMenuPhone_Click);
			   // 
			   // pictureBox2
			   // 
			   this->pictureBox2->Location = System::Drawing::Point(21, 205);
			   this->pictureBox2->Name = L"pictureBox2";
			   this->pictureBox2->Size = System::Drawing::Size(59, 52);
			   this->pictureBox2->TabIndex = 2;
			   this->pictureBox2->TabStop = false;
			   // 
			   // pictureBox3
			   // 
			   this->pictureBox3->Location = System::Drawing::Point(21, 263);
			   this->pictureBox3->Name = L"pictureBox3";
			   this->pictureBox3->Size = System::Drawing::Size(59, 54);
			   this->pictureBox3->TabIndex = 4;
			   this->pictureBox3->TabStop = false;
			   // 
			   // btnMenuTablet
			   // 
			   this->btnMenuTablet->BackColor = System::Drawing::SystemColors::Window;
			   this->btnMenuTablet->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->btnMenuTablet->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->btnMenuTablet->Location = System::Drawing::Point(87, 264);
			   this->btnMenuTablet->Name = L"btnMenuTablet";
			   this->btnMenuTablet->Size = System::Drawing::Size(376, 53);
			   this->btnMenuTablet->TabIndex = 3;
			   this->btnMenuTablet->Text = L"Планшети";
			   this->btnMenuTablet->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnMenuTablet->UseVisualStyleBackColor = false;
			   this->btnMenuTablet->Click += gcnew System::EventHandler(this, &MyForm::btnMenuTablet_Click);
			   // 
			   // pictureBox5
			   // 
			   this->pictureBox5->Location = System::Drawing::Point(21, 323);
			   this->pictureBox5->Name = L"pictureBox5";
			   this->pictureBox5->Size = System::Drawing::Size(59, 52);
			   this->pictureBox5->TabIndex = 6;
			   this->pictureBox5->TabStop = false;
			   // 
			   // btnMenuLaptop
			   // 
			   this->btnMenuLaptop->BackColor = System::Drawing::SystemColors::Window;
			   this->btnMenuLaptop->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->btnMenuLaptop->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->btnMenuLaptop->Location = System::Drawing::Point(86, 322);
			   this->btnMenuLaptop->Name = L"btnMenuLaptop";
			   this->btnMenuLaptop->Size = System::Drawing::Size(377, 53);
			   this->btnMenuLaptop->TabIndex = 5;
			   this->btnMenuLaptop->Text = L"Ноутбуки";
			   this->btnMenuLaptop->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->btnMenuLaptop->UseVisualStyleBackColor = false;
			   this->btnMenuLaptop->Click += gcnew System::EventHandler(this, &MyForm::btnMenuLaptop_Click);
			   // 
			   // pictureBox8
			   // 
			   this->pictureBox8->BackColor = System::Drawing::SystemColors::Window;
			   this->pictureBox8->Location = System::Drawing::Point(0, 0);
			   this->pictureBox8->Name = L"pictureBox8";
			   this->pictureBox8->Size = System::Drawing::Size(481, 952);
			   this->pictureBox8->TabIndex = 13;
			   this->pictureBox8->TabStop = false;
			   // 
			   // pictureBox9
			   // 
			   this->pictureBox9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->pictureBox9->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->pictureBox9->Location = System::Drawing::Point(0, 0);
			   this->pictureBox9->Name = L"pictureBox9";
			   this->pictureBox9->Size = System::Drawing::Size(1698, 116);
			   this->pictureBox9->TabIndex = 14;
			   this->pictureBox9->TabStop = false;
			   // 
			   // lblHeaderPhone
			   // 
			   this->lblHeaderPhone->AutoSize = true;
			   this->lblHeaderPhone->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->lblHeaderPhone->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 25.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->lblHeaderPhone->Location = System::Drawing::Point(515, 26);
			   this->lblHeaderPhone->Name = L"lblHeaderPhone";
			   this->lblHeaderPhone->Size = System::Drawing::Size(212, 59);
			   this->lblHeaderPhone->TabIndex = 15;
			   this->lblHeaderPhone->Text = L"Телефони";
			   // 
			   // lblHeaderTablet
			   // 
			   this->lblHeaderTablet->AutoSize = true;
			   this->lblHeaderTablet->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->lblHeaderTablet->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 25.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->lblHeaderTablet->Location = System::Drawing::Point(515, 26);
			   this->lblHeaderTablet->Name = L"lblHeaderTablet";
			   this->lblHeaderTablet->Size = System::Drawing::Size(165, 59);
			   this->lblHeaderTablet->TabIndex = 15;
			   this->lblHeaderTablet->Text = L"Планшети";
			   // 
			   // lblHeaderLaptop
			   // 
			   this->lblHeaderLaptop->AutoSize = true;
			   this->lblHeaderLaptop->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->lblHeaderLaptop->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 25.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->lblHeaderLaptop->Location = System::Drawing::Point(515, 26);
			   this->lblHeaderLaptop->Name = L"lblHeaderLaptop";
			   this->lblHeaderLaptop->Size = System::Drawing::Size(176, 59);
			   this->lblHeaderLaptop->TabIndex = 15;
			   this->lblHeaderLaptop->Text = L"Ноутбуки";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::Gainsboro;
			   this->ClientSize = System::Drawing::Size(1300, 600);
			   this->Controls->Add(this->lblHeaderLaptop);
			   this->Controls->Add(this->lblHeaderTablet);
			   this->Controls->Add(this->lblHeaderPhone);
			   this->Controls->Add(this->pictureBox5);
			   this->Controls->Add(this->btnMenuLaptop);
			   this->Controls->Add(this->pictureBox3);
			   this->Controls->Add(this->btnMenuTablet);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->btnMenuPhone);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->pictureBox8);
			   this->Controls->Add(this->pictureBox9);
			   this->Name = L"MyForm";
			   this->Text = L"Магазин Електроніки";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }

		   // --- МЕНЮ (ПЕРЕМИКАННЯ ВІКОН) ---
	private: System::Void btnMenuPhone_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowPhoneView();
	}
	private: System::Void btnMenuTablet_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowTabletView();
	}
	private: System::Void btnMenuLaptop_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowLaptopView();
	}

		   // --- ЛОГІКА ТЕЛЕФОНІВ ---
	private: System::Void btnAddPhone_Click(System::Object^ sender, System::EventArgs^ e) {
		// Викликаємо форму (колишня AssemblyForm)
		AddEditAssemblyForm^ form = gcnew AddEditAssemblyForm(nullptr);
		if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			wrapper->AddPhone(form->ResultData);
			ShowPhoneView();
			MessageBox::Show("Телефон успішно додано!");
		}
	}
	private: System::Void btnEditPhone_Click(System::Object^ sender, System::EventArgs^ e) {
		if (mainDataGridView->SelectedRows->Count != 1) return;
		try {
			PhoneData^ sel = safe_cast<PhoneData^>(mainDataGridView->SelectedRows[0]->DataBoundItem);
			AddEditAssemblyForm^ form = gcnew AddEditAssemblyForm(sel);
			if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				wrapper->UpdatePhone(form->ResultData->Type, form->ResultData->Price, form->ResultData->ScreenSize, form->ResultData->SimType, form->ResultData->Battery);
				ShowPhoneView();
			}
		}
		catch (...) { MessageBox::Show("Помилка вибору."); }
	}
	private: System::Void btnSingleSim_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadDataGrid(wrapper->GetSingleSimPhones());
		MessageBox::Show("Відображено телефони, які підтримують лише 1 SIM-карту.");
	}

		   // --- ЛОГІКА ПЛАНШЕТІВ ---
	private: System::Void btnAddTablet_Click(System::Object^ sender, System::EventArgs^ e) {
		AddEditTestingForm^ form = gcnew AddEditTestingForm(nullptr);
		if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			wrapper->AddTablet(form->ResultData);
			ShowTabletView();
		}
	}
	private: System::Void btnEditTablet_Click(System::Object^ sender, System::EventArgs^ e) {
		if (mainDataGridView->SelectedRows->Count != 1) return;
		try {
			TabletData^ sel = safe_cast<TabletData^>(mainDataGridView->SelectedRows[0]->DataBoundItem);
			AddEditTestingForm^ form = gcnew AddEditTestingForm(sel);
			if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				wrapper->UpdateTablet(form->ResultData->Type, form->ResultData->Price, form->ResultData->Memory, form->ResultData->Material, form->ResultData->HasStylus);
				ShowTabletView();
			}
		}
		catch (...) {}
	}
	private: System::Void btnFindStylus_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadDataGrid(wrapper->GetTabletsWithStylus());
		MessageBox::Show("Відображено планшети, які мають стілус.");
	}

		   // --- ЛОГІКА НОУТБУКІВ ---
	private: System::Void btnAddLaptop_Click(System::Object^ sender, System::EventArgs^ e) {
		AddEditPackagingForm^ form = gcnew AddEditPackagingForm(nullptr);
		if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			wrapper->AddLaptop(form->ResultData);
			ShowLaptopView();
		}
	}
	private: System::Void btnEditLaptop_Click(System::Object^ sender, System::EventArgs^ e) {
		if (mainDataGridView->SelectedRows->Count != 1) return;
		try {
			LaptopData^ sel = safe_cast<LaptopData^>(mainDataGridView->SelectedRows[0]->DataBoundItem);
			AddEditPackagingForm^ form = gcnew AddEditPackagingForm(sel);
			if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				wrapper->UpdateLaptop(form->ResultData->Type, form->ResultData->Price, form->ResultData->KeyboardType, form->ResultData->AudioInfo, form->ResultData->Wireless);
				ShowLaptopView();
			}
		}
		catch (...) {}
	}
	private: System::Void btnFindWifi_Click(System::Object^ sender, System::EventArgs^ e) {
		LoadDataGrid(wrapper->GetLaptopsWithWifi());
		MessageBox::Show("Відображено ноутбуки з підтримкою Wi-Fi.");
	}

		   // --- ФАЙЛИ ---
	private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			wrapper->SaveToFile(L"processes.txt");
			MessageBox::Show("Дані збережено у processes.txt");
		}
		catch (Exception^ ex) { MessageBox::Show("Помилка: " + ex->Message); }
	}
	private: System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			wrapper->LoadFromFile(L"processes.txt");
			// Оновлюємо поточне вікно
			if (lblHeaderPhone->Visible) ShowPhoneView();
			else if (lblHeaderTablet->Visible) ShowTabletView();
			else ShowLaptopView();
			MessageBox::Show("Дані завантажено!");
		}
		catch (Exception^ ex) { MessageBox::Show("Помилка: " + ex->Message); }
	}

	};
}