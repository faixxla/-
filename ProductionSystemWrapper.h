#pragma once
#include "ProductionSystem.h" 
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;

// Базовий клас для передачі даних у форми
public ref class ElectronicsData
{
public:
    property String^ Type;   // Тип (наприклад, "iPhone 13")
    property String^ OS;     // iOS, Android
    property String^ Brand;  // Apple, Samsung
    property double Price;   // Ціна
};

// Клас даних для Телефону
public ref class PhoneData : public ElectronicsData
{
public:
    property double ScreenSize;
    property String^ SimType;
    property String^ Battery;
};

// Клас даних для Планшету
public ref class TabletData : public ElectronicsData
{
public:
    property String^ Memory;
    property String^ Material;
    property bool HasStylus;
};

// Клас даних для Ноутбука
public ref class LaptopData : public ElectronicsData
{
public:
    property String^ KeyboardType;
    property String^ AudioInfo;
    property String^ Wireless;
};

// Головний клас-обгортка (Wrapper)
public ref class ProductionSystemWrapper
{
private:
    ProductionSystem* systemPtr;
    msclr::interop::marshal_context context;

    String^ StringToCli(const std::string& s);
    std::string StringToCpp(String^ s);

public:
    ProductionSystemWrapper();
    ~ProductionSystemWrapper();
    !ProductionSystemWrapper();

    // Файлові операції
    void SaveToFile(String^ filename);
    void LoadFromFile(String^ filename);

    // Отримання списків (для таблиць)
    List<PhoneData^>^ GetAllPhones();
    List<TabletData^>^ GetAllTablets();
    List<LaptopData^>^ GetAllLaptops();

    // Методи оновлення
    bool UpdatePhone(String^ originalType, double price, double screen, String^ sim, String^ bat);
    bool UpdateTablet(String^ originalType, double price, String^ mem, String^ mat, bool stylus);
    bool UpdateLaptop(String^ originalType, double price, String^ keyb, String^ aud, String^ wire);

    // Методи додавання
    void AddPhone(PhoneData^ data);
    void AddTablet(TabletData^ data);
    void AddLaptop(LaptopData^ data);

    // Спеціальні запити (твої обов'язкові методи)
    List<PhoneData^>^ GetSingleSimPhones();     // Знайти телефони з 1 SIM
    List<TabletData^>^ GetTabletsWithStylus();  // Знайти планшети зі стілусом
    List<LaptopData^>^ GetLaptopsWithWifi();    // Знайти ноутбуки з Wi-Fi
};