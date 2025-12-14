#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

// Базовий клас: Електроніка
class Electronics {
protected:
    std::string type;   // Тип пристрою
    std::string os;     // Операційна система
    std::string brand;  // Бренд
    double price;       // Ціна

public:
    Electronics();
    Electronics(const std::string& type, const std::string& os, const std::string& brand, double price);

    virtual ~Electronics() = default;
    virtual void printInfo() const = 0; // Метод відображення інформації

    // Гетери
    std::string getType() const;
    std::string getOs() const;
    std::string getBrand() const;
    double getPrice() const;

    // Сетери
    void setType(const std::string& t);
    void setOs(const std::string& o);
    void setBrand(const std::string& b);
    void setPrice(double p);
};

// Клас: Телефон
class Phone : public Electronics {
private:
    double screenSize;      // Діагональ
    std::string simType;    // Тип SIM (одна SIM, дві SIM, nano...)
    std::string battery;    // Інформація про батарею

public:
    Phone();
    Phone(const std::string& type, const std::string& os, const std::string& brand, double price,
        double screenSize, const std::string& simType, const std::string& battery);

    double getScreenSize() const;
    std::string getSimType() const;
    std::string getBattery() const;

    void setScreenSize(double s);
    void setSimType(const std::string& s);
    void setBattery(const std::string& b);

    void printInfo() const override;

    // Спеціальний метод: перевірка на одну SIM-карту
    bool isSingleSim() const;
};

// Клас: Планшет
class Tablet : public Electronics {
private:
    std::string memory;     // Пам'ять
    std::string material;   // Матеріали корпусу
    bool hasStylus;         // Підтримка стілусу

public:
    Tablet();
    Tablet(const std::string& type, const std::string& os, const std::string& brand, double price,
        const std::string& memory, const std::string& material, bool hasStylus);

    std::string getMemory() const;
    std::string getMaterial() const;
    bool getHasStylus() const;

    void setMemory(const std::string& m);
    void setMaterial(const std::string& m);
    void setHasStylus(bool s);

    void printInfo() const override;

    // Спеціальний метод: перевірка наявності стілуса
    bool checkStylusSupport() const;
};

// Клас: Ноутбук
class Laptop : public Electronics {
private:
    std::string keyboardType; // Тип клавіатури
    std::string audioInfo;    // Аудіо
    std::string wireless;     // Бездротові засоби (Wi-Fi, Bluetooth...)

public:
    Laptop();
    Laptop(const std::string& type, const std::string& os, const std::string& brand, double price,
        const std::string& keyboardType, const std::string& audioInfo, const std::string& wireless);

    std::string getKeyboardType() const;
    std::string getAudioInfo() const;
    std::string getWireless() const;

    void setKeyboardType(const std::string& k);
    void setAudioInfo(const std::string& a);
    void setWireless(const std::string& w);

    void printInfo() const override;

    // Спеціальний метод: перевірка наявності Wi-Fi
    bool hasWifiSupport() const;
};

// Допоміжна структура для сортування (наприклад, за ціною)
struct CompareByPrice {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a.getPrice() < b.getPrice();
    }
};