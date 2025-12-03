#pragma once
#include "AddEditPackagingForm.h"
#include "AddEditTestingForm.h"
#include "AddEditAssemblyForm.h"
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
				wrapper->LoadFromFile(L"processes.txt");
			}
			catch (Exception^ ex) {
				MessageBox::Show("Помилка при початковому завантаженні файлу: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			ShowAssemblyView();
		}
	
		protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: ProductionSystemWrapper^ wrapper;
	private: System::Windows::Forms::DataGridView^ mainDataGridView;
	private: System::Windows::Forms::TextBox^ txtPackageType;
	private: System::Windows::Forms::TextBox^ txtMaterialSubstring;
	private: System::Windows::Forms::Button^ btnMaxDuration;
	private: System::Windows::Forms::Button^ btnAddAssembly;
	private: System::Windows::Forms::Button^ btnEditAssembly;
	private: System::Windows::Forms::Button^ btnAnalyzeTests;
	private: System::Windows::Forms::Button^ btnEditTesting;
	private: System::Windows::Forms::Button^ btnFindPacking;
	private: System::Windows::Forms::Button^ btnEditPackaging;
	private: System::Windows::Forms::Button^ btnSave;
	private: System::Windows::Forms::Button^ btnLoad;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ btnAddPackaging;
	private: System::Windows::Forms::Button^ btnAddTesting;

	private: System::ComponentModel::IContainer^ components;

	void LoadDataGrid(System::Collections::IEnumerable^ dataList)
    {
        mainDataGridView->DataSource = nullptr; 
        mainDataGridView->DataSource = dataList;
        mainDataGridView->AutoResizeColumns(DataGridViewAutoSizeColumnsMode::AllCells);
    }
	void HideAllFunctionalControls() {
		btnMaxDuration->Visible = false;
		btnAddAssembly->Visible = false;
		btnEditAssembly->Visible = false;

		btnAnalyzeTests->Visible = false;
		btnEditTesting->Visible = false;

		btnFindPacking->Visible = false;
		btnEditPackaging->Visible = false;
		txtPackageType->Visible = false;
		txtMaterialSubstring->Visible = false;
		btnAddPackaging->Visible = false;
		btnAddTesting->Visible = false;
		label1->Visible = false;
		label2->Visible = false;
		label3->Visible = false;
	}

	void ShowAssemblyView() {
		HideAllFunctionalControls();
		LoadDataGrid(wrapper->GetAllAssemblies());
		btnMaxDuration->Visible = true;
		btnAddAssembly->Visible = true;
		btnEditAssembly->Visible = true;
		label1->Visible = true;
	}

	void ShowTestingView() {
		HideAllFunctionalControls();
		LoadDataGrid(wrapper->GetAllTests());
		btnAnalyzeTests->Visible = true;
		btnAddTesting->Visible = true;
		btnEditTesting->Visible = true;
		label2->Visible = true;
	}

	void ShowPackingView() {
		HideAllFunctionalControls();
		LoadDataGrid(wrapper->GetAllPackagings());
		btnFindPacking->Visible = true;
		btnEditPackaging->Visible = true;
		txtPackageType->Visible = true;
		btnAddPackaging->Visible = true;
		txtMaterialSubstring->Visible = true;
		label3->Visible = true;
	}

	void SetupAllControls() {
		mainDataGridView = gcnew System::Windows::Forms::DataGridView();
		mainDataGridView->Location = System::Drawing::Point(370, 100);
		mainDataGridView->Size = System::Drawing::Size(768, 300);
		mainDataGridView->ReadOnly = true;
		mainDataGridView->AutoGenerateColumns = true;
		mainDataGridView->Anchor =
			System::Windows::Forms::AnchorStyles::Top |
			System::Windows::Forms::AnchorStyles::Left |
			System::Windows::Forms::AnchorStyles::Right;
		mainDataGridView->Font = gcnew System::Drawing::Font("Segoe UI", 10.0F, System::Drawing::FontStyle::Regular);
		this->Controls->Add(mainDataGridView);

		int y_pos = 410;
		int x_pos = 370;

		btnMaxDuration = gcnew System::Windows::Forms::Button();
		btnMaxDuration->Text = L"Збірка з MAX тривалістю";
		btnMaxDuration->Location = System::Drawing::Point(x_pos, y_pos);
		btnMaxDuration->Size = System::Drawing::Size(200, 40);
		btnMaxDuration->Click += gcnew System::EventHandler(this, &MyForm::btnMaxDuration_Click);
		this->Controls->Add(btnMaxDuration);

		btnAddAssembly = gcnew System::Windows::Forms::Button();
		btnAddAssembly->Text = L"Додати збірку";
		btnAddAssembly->Location = System::Drawing::Point(x_pos + 200, y_pos);
		btnAddAssembly->Size = System::Drawing::Size(150, 40);
		btnAddAssembly->Click += gcnew System::EventHandler(this, &MyForm::btnAddAssembly_Click);
		this->Controls->Add(btnAddAssembly);

		btnEditAssembly = gcnew System::Windows::Forms::Button();
		btnEditAssembly->Text = L"Модифікувати збірку";
		btnEditAssembly->Location = System::Drawing::Point(x_pos + 350, y_pos);
		btnEditAssembly->Size = System::Drawing::Size(150, 40);
		btnEditAssembly->Click += gcnew System::EventHandler(this, &MyForm::btnEditAssembly_Click);
		this->Controls->Add(btnEditAssembly);


		btnAnalyzeTests = gcnew System::Windows::Forms::Button();
		btnAnalyzeTests->Text = L"Аналізувати всі випробування";
		btnAnalyzeTests->Location = System::Drawing::Point(x_pos, y_pos);
		btnAnalyzeTests->Size = System::Drawing::Size(250, 40);
		btnAnalyzeTests->Click += gcnew System::EventHandler(this, &MyForm::btnAnalyzeTests_Click);
		this->Controls->Add(btnAnalyzeTests);

		btnEditTesting = gcnew System::Windows::Forms::Button();
		btnEditTesting->Text = L"Модифікувати випробування";
		btnEditTesting->Location = System::Drawing::Point(x_pos + 250, y_pos);
		btnEditTesting->Size = System::Drawing::Size(180, 40);
		btnEditTesting->Click += gcnew System::EventHandler(this, &MyForm::btnEditTesting_Click);
		this->Controls->Add(btnEditTesting);

		btnAddTesting = gcnew System::Windows::Forms::Button();
		btnAddTesting->Text = L"Додати тест";
		btnAddTesting->Location = System::Drawing::Point(x_pos + 400, y_pos + 47);
		btnAddTesting->Size = System::Drawing::Size(180, 40);
		btnAddTesting->Click += gcnew System::EventHandler(this, &MyForm::btnAddTesting_Click);
		this->Controls->Add(btnAddTesting);

		System::Windows::Forms::Label^ lblType = gcnew System::Windows::Forms::Label();
		lblType->Text = L"Тип упаковки:";
		lblType->Location = System::Drawing::Point(x_pos, y_pos + 5);
		lblType->Size = System::Drawing::Size(100, 20);
		this->Controls->Add(lblType);

		txtPackageType = gcnew System::Windows::Forms::TextBox();
		txtPackageType->Location = System::Drawing::Point(x_pos, y_pos + 25);
		txtPackageType->Size = System::Drawing::Size(150, 20);
		this->Controls->Add(txtPackageType);

		System::Windows::Forms::Label^ lblMaterial = gcnew System::Windows::Forms::Label();
		lblMaterial->Text = L"Матеріал (підрядок):";
		lblMaterial->Location = System::Drawing::Point(x_pos + 160, y_pos + 5);
		lblMaterial->Size = System::Drawing::Size(150, 20);
		this->Controls->Add(lblMaterial);

		txtMaterialSubstring = gcnew System::Windows::Forms::TextBox();
		txtMaterialSubstring->Location = System::Drawing::Point(x_pos + 160, y_pos + 25);
		txtMaterialSubstring->Size = System::Drawing::Size(150, 20);
		this->Controls->Add(txtMaterialSubstring);

		btnFindPacking = gcnew System::Windows::Forms::Button();
		btnFindPacking->Text = L"Знайти за критеріями";
		btnFindPacking->Location = System::Drawing::Point(x_pos + 315, y_pos + 7);
		btnFindPacking->Size = System::Drawing::Size(200, 40);
		btnFindPacking->Click += gcnew System::EventHandler(this, &MyForm::btnFindPacking_Click);
		this->Controls->Add(btnFindPacking);

		btnEditPackaging = gcnew System::Windows::Forms::Button();
		btnEditPackaging->Text = L"Модифікувати упаковку";
		btnEditPackaging->Location = System::Drawing::Point(x_pos + 515, y_pos + 7);
		btnEditPackaging->Size = System::Drawing::Size(180, 40);
		btnEditPackaging->Click += gcnew System::EventHandler(this, &MyForm::btnEditPackaging_Click);
		this->Controls->Add(btnEditPackaging);

		btnAddPackaging = gcnew System::Windows::Forms::Button();
		btnAddPackaging->Text = L"Додати упаковку";
		btnAddPackaging->Location = System::Drawing::Point(x_pos + 400, y_pos + 47);
		btnAddPackaging->Size = System::Drawing::Size(180, 40);
		btnAddPackaging->Click += gcnew System::EventHandler(this, &MyForm::btnAddPackaging_Click);
		this->Controls->Add(btnAddPackaging);

		btnSave = gcnew System::Windows::Forms::Button();
		btnSave->Text = L"Зберегти зміни до файлу";
		btnSave->Location = System::Drawing::Point(x_pos, y_pos + 47);
		btnSave->Size = System::Drawing::Size(200, 40);
		btnSave->Click += gcnew System::EventHandler(this, &MyForm::btnSave_Click);
		this->Controls->Add(btnSave);

		btnLoad = gcnew System::Windows::Forms::Button();
		btnLoad->Text = L"Завантажити з файлу";
		btnLoad->Location = System::Drawing::Point(x_pos + 200, y_pos + 47);
		btnLoad->Size = System::Drawing::Size(200, 40);
		btnLoad->Click += gcnew System::EventHandler(this, &MyForm::btnLoad_Click);
		this->Controls->Add(btnLoad);

		HideAllFunctionalControls();
	}
#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			   this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
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
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::SystemColors::Window;
			   this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button1->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button1->Location = System::Drawing::Point(85, 205);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(378, 53);
			   this->button1->TabIndex = 1;
			   this->button1->Text = L"Assembly";
			   this->button1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
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
			   // button2
			   // 
			   this->button2->BackColor = System::Drawing::SystemColors::Window;
			   this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button2->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button2->Location = System::Drawing::Point(87, 264);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(376, 53);
			   this->button2->TabIndex = 3;
			   this->button2->Text = L"Testing";
			   this->button2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->button2->UseVisualStyleBackColor = false;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // pictureBox5
			   // 
			   this->pictureBox5->Location = System::Drawing::Point(21, 323);
			   this->pictureBox5->Name = L"pictureBox5";
			   this->pictureBox5->Size = System::Drawing::Size(59, 52);
			   this->pictureBox5->TabIndex = 6;
			   this->pictureBox5->TabStop = false;
			   // 
			   // button4
			   // 
			   this->button4->BackColor = System::Drawing::SystemColors::Window;
			   this->button4->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button4->Font = (gcnew System::Drawing::Font(L"Candara", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->button4->Location = System::Drawing::Point(86, 322);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(377, 53);
			   this->button4->TabIndex = 5;
			   this->button4->Text = L"Packing";
			   this->button4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			   this->button4->UseVisualStyleBackColor = false;
			   this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
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
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 25.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label1->Location = System::Drawing::Point(515, 26);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(212, 59);
			   this->label1->TabIndex = 15;
			   this->label1->Text = L"Assembly";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 25.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label2->Location = System::Drawing::Point(515, 26);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(165, 59);
			   this->label2->TabIndex = 15;
			   this->label2->Text = L"Testing";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->BackColor = System::Drawing::Color::WhiteSmoke;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 25.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label3->Location = System::Drawing::Point(515, 26);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(176, 59);
			   this->label3->TabIndex = 15;
			   this->label3->Text = L"Packing";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::Gainsboro;
			   this->ClientSize = System::Drawing::Size(1699, 681);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->pictureBox5);
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->pictureBox3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->pictureBox2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->pictureBox8);
			   this->Controls->Add(this->pictureBox9);
			   this->MinimumSize = System::Drawing::Size(1000, 600);
			   this->Name = L"MyForm";
			   this->Text = L"ManagmentSystem";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		ShowAssemblyView();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowAssemblyView();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowTestingView();
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		ShowPackingView();
	}
	private: System::Void btnMaxDuration_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			AssemblyData^ maxAssembly = wrapper->GetAssemblyWithMaxDuration();
			if (maxAssembly) {
				String^ msg = String::Format("ID: {0}\nТривалість: {1:F1} год\nМісце: {2}",
					maxAssembly->Id, maxAssembly->Duration, maxAssembly->Location);
				MessageBox::Show(msg, "Збірка з найбільшою тривалістю", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Список збірок порожній.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Помилка: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void btnAnalyzeTests_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			List<TestingData^>^ analyzedTests = wrapper->GetAnalyzedTests();
			LoadDataGrid(analyzedTests);
			MessageBox::Show("Аналіз випробувань завершено. Результати у колонці 'AnalysisResult'.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Помилка: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
	private: System::Void btnFindPacking_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			List<PackagingData^>^ foundPackages = wrapper->FindPackagingByCriteria(
				txtPackageType->Text,
				txtMaterialSubstring->Text
			);

			LoadDataGrid(foundPackages);

			MessageBox::Show("Знайдено " + foundPackages->Count.ToString() + " упаковок за критеріями. Відображено в таблиці.", "Пошук завершено", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Помилка: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

private: System::Void btnAddAssembly_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		AddEditAssemblyForm^ addForm = gcnew AddEditAssemblyForm(nullptr);

		if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			wrapper->AddAssembly(addForm->ResultData);
			ShowAssemblyView();
			MessageBox::Show("Збірку успішно додано.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка при додаванні: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnAddTesting_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		AddEditTestingForm^ addForm = gcnew AddEditTestingForm(nullptr);

		if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			wrapper->AddTesting(addForm->ResultData);
			ShowTestingView();
			MessageBox::Show("Збірку успішно додано.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка при додаванні: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnAddPackaging_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		AddEditPackagingForm^ addForm = gcnew AddEditPackagingForm(nullptr);

		if (addForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			wrapper->AddPackaging(addForm->ResultData);
			ShowPackingView();
			MessageBox::Show("Збірку успішно додано.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка при додаванні: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
private: System::Void btnEditAssembly_Click(System::Object^ sender, System::EventArgs^ e) {
	if (mainDataGridView->SelectedRows->Count != 1) {
		MessageBox::Show("Будь ласка, виділіть один рядок для редагування.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try {
		AssemblyData^ selectedData = safe_cast<AssemblyData^>(mainDataGridView->SelectedRows[0]->DataBoundItem);

		AssemblyData^ editData = gcnew AssemblyData();
		editData->Id = selectedData->Id;
		editData->Duration = selectedData->Duration;
		editData->Workers = selectedData->Workers;
		editData->Location = selectedData->Location;
		editData->PartsCount = selectedData->PartsCount;
		editData->AssemblyTime = selectedData->AssemblyTime;
		editData->Tool = selectedData->Tool;

		AddEditAssemblyForm^ editForm = gcnew AddEditAssemblyForm(editData);

		if (editForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (wrapper->UpdateAssembly(editForm->ResultData)) {
				ShowAssemblyView();
				MessageBox::Show("Збірку успішно оновлено.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Не вдалося знайти або оновити збірку.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка редагування: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

	private: System::Void btnEditTesting_Click(System::Object^ sender, System::EventArgs^ e) {
		if (mainDataGridView->SelectedRows->Count != 1) {
			MessageBox::Show("Будь ласка, виділіть один рядок для редагування.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			return;
		}

		try {
			TestingData^ selectedData = safe_cast<TestingData^>(mainDataGridView->SelectedRows[0]->DataBoundItem);

			TestingData^ editData = gcnew TestingData();

			editData->Id = selectedData->Id;
			editData->Duration = selectedData->Duration;
			editData->Workers = selectedData->Workers;
			editData->Location = selectedData->Location;
			editData->TestType = selectedData->TestType;
			editData->Parameters = selectedData->Parameters;
			editData->Status = selectedData->Status;
			editData->MaxLoad = selectedData->MaxLoad;
			editData->MeasuredTolerance = selectedData->MeasuredTolerance;
			editData->TargetTolerance = selectedData->TargetTolerance;
			editData->HasPassedSafety = selectedData->HasPassedSafety;
			AddEditTestingForm^ editForm = gcnew AddEditTestingForm(editData);

			if (editForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				if (wrapper->UpdateTestingStatus(editForm->ResultData->Id, editForm->ResultData->Status)) {
					ShowTestingView();
					MessageBox::Show("Тест успішно оновлено.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else {
					MessageBox::Show("Не вдалося знайти або оновити тест.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Помилка редагування: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
}
private: System::Void btnEditPackaging_Click(System::Object^ sender, System::EventArgs^ e) {
	if (mainDataGridView->SelectedRows->Count != 1) {
		MessageBox::Show("Будь ласка, виділіть один рядок для редагування.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}
	try {
		PackagingData^ selectedData = safe_cast<PackagingData^>(mainDataGridView->SelectedRows[0]->DataBoundItem);
		PackagingData^ editData = gcnew PackagingData();
		editData->Id = selectedData->Id;
		editData->Duration = selectedData->Duration;
		editData->Workers = selectedData->Workers;
		editData->Location = selectedData->Location;
		editData->PackageType = selectedData->PackageType;
		editData->Materials = selectedData->Materials;
		editData->Design = selectedData->Design;
		AddEditPackagingForm^ editForm = gcnew AddEditPackagingForm(editData);
		if (editForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			if (wrapper->UpdatePackagingDesign(editForm->ResultData->Id, editForm->ResultData->Design)) {
				ShowPackingView();
				MessageBox::Show("Дизайн успішно оновлено.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Не вдалося знайти або оновити дизайн.", "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка редагування: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}


private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		wrapper->SaveToFile(L"processes_saved.txt");
		MessageBox::Show("Змінені дані успішно збережено у processes_saved.txt", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка збереження: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

private: System::Void btnLoad_Click(System::Object^ sender, System::EventArgs^ e) {
	try {
		wrapper->LoadFromFile(L"processes_saved.txt");
		if (btnMaxDuration->Visible == true) ShowAssemblyView();
		else if (btnAnalyzeTests->Visible == true) ShowTestingView();
		else if (btnFindPacking->Visible == true) ShowPackingView();

		MessageBox::Show("Дані успішно завантажено.", "Успіх", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (Exception^ ex) {
		MessageBox::Show("Помилка завантаження: " + ex->Message, "Помилка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
	
};
}