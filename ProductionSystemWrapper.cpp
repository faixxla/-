#include "ProductionSystemWrapper.h"
#include <msclr/marshal.h> 

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;

// --- Допоміжні методи конвертації рядків ---
String^ ProductionSystemWrapper::StringToCli(const std::string& s) {
    return gcnew String(s.c_str());
}

std::string ProductionSystemWrapper::StringToCpp(String^ s) {
    return context.marshal_as<std::string>(s);
}

// --- Конструктор / Деструктор ---
ProductionSystemWrapper::ProductionSystemWrapper()
{
    systemPtr = new ProductionSystem();
}

ProductionSystemWrapper::~ProductionSystemWrapper()
{
    this->!ProductionSystemWrapper();
}

ProductionSystemWrapper::!ProductionSystemWrapper()
{
    if (systemPtr) {
        delete systemPtr;
        systemPtr = nullptr;
    }
}

// --- Файли ---
void ProductionSystemWrapper::SaveToFile(String^ filename)
{
    try {
        systemPtr->saveToFile(StringToCpp(filename));
    }
    catch (const std::exception& ex) {
        throw gcnew Exception(StringToCli(ex.what()));
    }
}

void ProductionSystemWrapper::LoadFromFile(String^ filename)
{
    try {
        systemPtr->loadFromFile(StringToCpp(filename));
    }
    catch (const std::exception& ex) {
        throw gcnew Exception(StringToCli(ex.what()));
    }
}

// --- Отримання списків (Get All) ---

List<PhoneData^>^ ProductionSystemWrapper::GetAllPhones()
{
    List<PhoneData^>^ list = gcnew List<PhoneData^>();
    for (const auto& p : systemPtr->getPhones()) {
        PhoneData^ data = gcnew PhoneData();
        data->Type = StringToCli(p.getType());
        data->OS = StringToCli(p.getOs());
        data->Brand = StringToCli(p.getBrand());
        data->Price = p.getPrice();
        data->ScreenSize = p.getScreenSize();
        data->SimType = StringToCli(p.getSimType());
        data->Battery = StringToCli(p.getBattery());
        list->Add(data);
    }
    return list;
}

List<TabletData^>^ ProductionSystemWrapper::GetAllTablets()
{
    List<TabletData^>^ list = gcnew List<TabletData^>();
    for (const auto& t : systemPtr->getTablets()) {
        TabletData^ data = gcnew TabletData();
        data->Type = StringToCli(t.getType());
        data->OS = StringToCli(t.getOs());
        data->Brand = StringToCli(t.getBrand());
        data->Price = t.getPrice();
        data->Memory = StringToCli(t.getMemory());
        data->Material = StringToCli(t.getMaterial());
        data->HasStylus = t.getHasStylus();
        list->Add(data);
    }
    return list;
}

List<LaptopData^>^ ProductionSystemWrapper::GetAllLaptops()
{
    List<LaptopData^>^ list = gcnew List<LaptopData^>();
    for (const auto& l : systemPtr->getLaptops()) {
        LaptopData^ data = gcnew LaptopData();
        data->Type = StringToCli(l.getType());
        data->OS = StringToCli(l.getOs());
        data->Brand = StringToCli(l.getBrand());
        data->Price = l.getPrice();
        data->KeyboardType = StringToCli(l.getKeyboardType());
        data->AudioInfo = StringToCli(l.getAudioInfo());
        data->Wireless = StringToCli(l.getWireless());
        list->Add(data);
    }
    return list;
}

// --- Додавання (Add) ---

void ProductionSystemWrapper::AddPhone(PhoneData^ data)
{
    Phone p(
        StringToCpp(data->Type), StringToCpp(data->OS), StringToCpp(data->Brand), data->Price,
        data->ScreenSize, StringToCpp(data->SimType), StringToCpp(data->Battery)
    );
    systemPtr->addPhone(p);
}

void ProductionSystemWrapper::AddTablet(TabletData^ data)
{
    Tablet t(
        StringToCpp(data->Type), StringToCpp(data->OS), StringToCpp(data->Brand), data->Price,
        StringToCpp(data->Memory), StringToCpp(data->Material), data->HasStylus
    );
    systemPtr->addTablet(t);
}

void ProductionSystemWrapper::AddLaptop(LaptopData^ data)
{
    Laptop l(
        StringToCpp(data->Type), StringToCpp(data->OS), StringToCpp(data->Brand), data->Price,
        StringToCpp(data->KeyboardType), StringToCpp(data->AudioInfo), StringToCpp(data->Wireless)
    );
    systemPtr->addLaptop(l);
}

// --- Оновлення (Update) ---

bool ProductionSystemWrapper::UpdatePhone(String^ originalType, double price, double screen, String^ sim, String^ bat)
{
    return systemPtr->updatePhone(StringToCpp(originalType), price, screen, StringToCpp(sim), StringToCpp(bat));
}

bool ProductionSystemWrapper::UpdateTablet(String^ originalType, double price, String^ mem, String^ mat, bool stylus)
{
    return systemPtr->updateTablet(StringToCpp(originalType), price, StringToCpp(mem), StringToCpp(mat), stylus);
}

bool ProductionSystemWrapper::UpdateLaptop(String^ originalType, double price, String^ keyb, String^ aud, String^ wire)
{
    return systemPtr->updateLaptop(StringToCpp(originalType), price, StringToCpp(keyb), StringToCpp(aud), StringToCpp(wire));
}

// --- Спеціальні запити (Specific Queries) ---

List<PhoneData^>^ ProductionSystemWrapper::GetSingleSimPhones()
{
    List<PhoneData^>^ list = gcnew List<PhoneData^>();
    // Отримуємо вектор знайдених телефонів
    std::vector<Phone> found = systemPtr->findSingleSimPhones();

    for (const auto& p : found) {
        PhoneData^ data = gcnew PhoneData();
        data->Type = StringToCli(p.getType());
        data->OS = StringToCli(p.getOs());
        data->Brand = StringToCli(p.getBrand());
        data->Price = p.getPrice();
        data->ScreenSize = p.getScreenSize();
        data->SimType = StringToCli(p.getSimType());
        data->Battery = StringToCli(p.getBattery());
        list->Add(data);
    }
    return list;
}

List<TabletData^>^ ProductionSystemWrapper::GetTabletsWithStylus()
{
    List<TabletData^>^ list = gcnew List<TabletData^>();
    std::vector<Tablet> found = systemPtr->findTabletsWithStylus();

    for (const auto& t : found) {
        TabletData^ data = gcnew TabletData();
        data->Type = StringToCli(t.getType());
        data->OS = StringToCli(t.getOs());
        data->Brand = StringToCli(t.getBrand());
        data->Price = t.getPrice();
        data->Memory = StringToCli(t.getMemory());
        data->Material = StringToCli(t.getMaterial());
        data->HasStylus = t.getHasStylus();
        list->Add(data);
    }
    return list;
}

List<LaptopData^>^ ProductionSystemWrapper::GetLaptopsWithWifi()
{
    List<LaptopData^>^ list = gcnew List<LaptopData^>();
    std::vector<Laptop> found = systemPtr->findLaptopsWithWifi();

    for (const auto& l : found) {
        LaptopData^ data = gcnew LaptopData();
        data->Type = StringToCli(l.getType());
        data->OS = StringToCli(l.getOs());
        data->Brand = StringToCli(l.getBrand());
        data->Price = l.getPrice();
        data->KeyboardType = StringToCli(l.getKeyboardType());
        data->AudioInfo = StringToCli(l.getAudioInfo());
        data->Wireless = StringToCli(l.getWireless());
        list->Add(data);
    }
    return list;
}