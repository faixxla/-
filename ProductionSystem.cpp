#include "ProductionSystem.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

// --- Додавання ---
void ProductionSystem::addPhone(const Phone& p) {
    phones.push_back(p);
}

void ProductionSystem::addTablet(const Tablet& t) {
    tablets.push_back(t);
}

void ProductionSystem::addLaptop(const Laptop& l) {
    laptops.push_back(l);
}

// --- Оновлення (шукаємо за полем Type, який виступає як назва моделі) ---

bool ProductionSystem::updatePhone(const std::string& originalType, double price, double screenSize, const std::string& simType, const std::string& battery) {
    for (auto& p : phones) {
        if (p.getType() == originalType) {
            p.setPrice(price);
            p.setScreenSize(screenSize);
            p.setSimType(simType);
            p.setBattery(battery);
            return true;
        }
    }
    return false;
}

bool ProductionSystem::updateTablet(const std::string& originalType, double price, const std::string& memory, const std::string& material, bool hasStylus) {
    for (auto& t : tablets) {
        if (t.getType() == originalType) {
            t.setPrice(price);
            t.setMemory(memory);
            t.setMaterial(material);
            t.setHasStylus(hasStylus);
            return true;
        }
    }
    return false;
}

bool ProductionSystem::updateLaptop(const std::string& originalType, double price, const std::string& keyboard, const std::string& audio, const std::string& wireless) {
    for (auto& l : laptops) {
        if (l.getType() == originalType) {
            l.setPrice(price);
            l.setKeyboardType(keyboard);
            l.setAudioInfo(audio);
            l.setWireless(wireless);
            return true;
        }
    }
    return false;
}

// --- Спеціальні методи пошуку ---

std::vector<Phone> ProductionSystem::findSingleSimPhones() const {
    std::vector<Phone> result;
    for (const auto& p : phones) {
        if (p.isSingleSim()) {
            result.push_back(p);
        }
    }
    return result;
}

std::vector<Tablet> ProductionSystem::findTabletsWithStylus() const {
    std::vector<Tablet> result;
    for (const auto& t : tablets) {
        if (t.checkStylusSupport()) {
            result.push_back(t);
        }
    }
    return result;
}

std::vector<Laptop> ProductionSystem::findLaptopsWithWifi() const {
    std::vector<Laptop> result;
    for (const auto& l : laptops) {
        if (l.hasWifiSupport()) {
            result.push_back(l);
        }
    }
    return result;
}

// --- Робота з файлами ---

void ProductionSystem::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Не вдалося відкрити файл для запису.");

    // Формат: P;Type;OS;Brand;Price;Screen;Sim;Battery
    for (const auto& p : phones) {
        out << "P;" << p.getType() << ";" << p.getOs() << ";" << p.getBrand() << ";"
            << p.getPrice() << ";" << p.getScreenSize() << ";" << p.getSimType() << ";" << p.getBattery() << "\n";
    }
    // Формат: T;Type;OS;Brand;Price;Memory;Material;HasStylus(0/1)
    for (const auto& t : tablets) {
        out << "T;" << t.getType() << ";" << t.getOs() << ";" << t.getBrand() << ";"
            << t.getPrice() << ";" << t.getMemory() << ";" << t.getMaterial() << ";" << (t.getHasStylus() ? 1 : 0) << "\n";
    }
    // Формат: L;Type;OS;Brand;Price;Keyboard;Audio;Wireless
    for (const auto& l : laptops) {
        out << "L;" << l.getType() << ";" << l.getOs() << ";" << l.getBrand() << ";"
            << l.getPrice() << ";" << l.getKeyboardType() << ";" << l.getAudioInfo() << ";" << l.getWireless() << "\n";
    }
}

void ProductionSystem::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        // Якщо файлу немає, просто очищуємо списки, це не критична помилка для першого запуску
        phones.clear(); tablets.clear(); laptops.clear();
        return;
    }

    phones.clear();
    tablets.clear();
    laptops.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string tag;
        std::getline(ss, tag, ';');

        try {
            std::string type, os, brand, tmp;
            double price;

            // Спільні поля
            std::getline(ss, type, ';');
            std::getline(ss, os, ';');
            std::getline(ss, brand, ';');
            std::getline(ss, tmp, ';'); price = std::stod(tmp);

            if (tag == "P") {
                double screen;
                std::string sim, bat;
                std::getline(ss, tmp, ';'); screen = std::stod(tmp);
                std::getline(ss, sim, ';');
                std::getline(ss, bat, ';');
                phones.emplace_back(type, os, brand, price, screen, sim, bat);
            }
            else if (tag == "T") {
                std::string mem, mat;
                bool stylus;
                std::getline(ss, mem, ';');
                std::getline(ss, mat, ';');
                std::getline(ss, tmp, ';'); stylus = (std::stoi(tmp) != 0);
                tablets.emplace_back(type, os, brand, price, mem, mat, stylus);
            }
            else if (tag == "L") {
                std::string keyb, aud, wire;
                std::getline(ss, keyb, ';');
                std::getline(ss, aud, ';');
                std::getline(ss, wire, ';');
                laptops.emplace_back(type, os, brand, price, keyb, aud, wire);
            }
        }
        catch (...) {
            // Ігноруємо пошкоджені рядки
        }
    }
}