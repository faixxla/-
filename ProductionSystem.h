#pragma once
#include "Process.h" // Тут знаходяться наші класи Phone, Tablet, Laptop 
#include <vector>
#include <string>

class ProductionSystem {
private:
    std::vector<Phone> phones;
    std::vector<Tablet> tablets;
    std::vector<Laptop> laptops;

public:
    // --- Додавання товарів ---
    void addPhone(const Phone& p);
    void addTablet(const Tablet& t);
    void addLaptop(const Laptop& l);

    // --- Оновлення товарів (шукаємо за назвою/типом) ---
    // Повертає true, якщо товар знайдено та оновлено
    bool updatePhone(const std::string& originalType, double price, double screenSize, const std::string& simType, const std::string& battery);
    bool updateTablet(const std::string& originalType, double price, const std::string& memory, const std::string& material, bool hasStylus);
    bool updateLaptop(const std::string& originalType, double price, const std::string& keyboard, const std::string& audio, const std::string& wireless);

    // --- Гетери (відображення інформації про сутності) ---
    const std::vector<Phone>& getPhones() const { return phones; }
    const std::vector<Tablet>& getTablets() const { return tablets; }
    const std::vector<Laptop>& getLaptops() const { return laptops; }

    // --- Спеціальні методи пошуку (відповідно до завдання) ---

    // Метод для перевірки наявності телефонів на одну SIM-карту
    std::vector<Phone> findSingleSimPhones() const;

    // Метод для перевірки наявності стілуса (пошук планшетів зі стілусом)
    std::vector<Tablet> findTabletsWithStylus() const;

    // Метод для перевірки можливості використання Wi-Fi (пошук ноутбуків з Wi-Fi)
    std::vector<Laptop> findLaptopsWithWifi() const;

    // --- Файлові операції ---
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};