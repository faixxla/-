#include "Process.h" // Файл називається Process.h, хоча всередині класи Electronics
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>

// --- ELECTRONICS (BASE) ---

Electronics::Electronics()
    : type("Unknown"), os("None"), brand("Unknown"), price(0.0) {
}

Electronics::Electronics(const std::string& type, const std::string& os, const std::string& brand, double price) {
    setType(type);
    setOs(os);
    setBrand(brand);
    setPrice(price);
}

// Гетери
std::string Electronics::getType() const { return type; }
std::string Electronics::getOs() const { return os; }
std::string Electronics::getBrand() const { return brand; }
double Electronics::getPrice() const { return price; }

// Сетери з перевірками
void Electronics::setType(const std::string& t) {
    if (t.empty()) throw std::invalid_argument("Тип не може бути порожнім.");
    type = t;
}
void Electronics::setOs(const std::string& o) {
    if (o.empty()) throw std::invalid_argument("ОС не може бути порожньою.");
    os = o;
}
void Electronics::setBrand(const std::string& b) {
    if (b.empty()) throw std::invalid_argument("Бренд не може бути порожнім.");
    brand = b;
}
void Electronics::setPrice(double p) {
    if (p < 0) throw std::invalid_argument("Ціна не може бути від'ємною.");
    price = p;
}

// --- PHONE ---

Phone::Phone() : Electronics(), screenSize(0.0), simType("Unknown"), battery("Unknown") {}

Phone::Phone(const std::string& type, const std::string& os, const std::string& brand, double price,
    double screenSize, const std::string& simType, const std::string& battery)
    : Electronics(type, os, brand, price) {
    setScreenSize(screenSize);
    setSimType(simType);
    setBattery(battery);
}

double Phone::getScreenSize() const { return screenSize; }
std::string Phone::getSimType() const { return simType; }
std::string Phone::getBattery() const { return battery; }

void Phone::setScreenSize(double s) {
    if (s <= 0) throw std::invalid_argument("Діагональ має бути більше 0.");
    screenSize = s;
}
void Phone::setSimType(const std::string& s) { simType = s; }
void Phone::setBattery(const std::string& b) { battery = b; }

void Phone::printInfo() const {
    std::cout << "Phone: " << brand << " " << type << ", Price: " << price << "\n";
}

bool Phone::isSingleSim() const {
    // Проста логіка: якщо в тексті є "one" або "одна" або "single"
    std::string s = simType;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    if (s.find("one") != std::string::npos ||
        s.find("одна") != std::string::npos ||
        s.find("single") != std::string::npos) {
        return true;
    }
    return false;
}

// --- TABLET ---

Tablet::Tablet() : Electronics(), memory("Unknown"), material("Plastic"), hasStylus(false) {}

Tablet::Tablet(const std::string& type, const std::string& os, const std::string& brand, double price,
    const std::string& memory, const std::string& material, bool hasStylus)
    : Electronics(type, os, brand, price) {
    setMemory(memory);
    setMaterial(material);
    setHasStylus(hasStylus);
}

std::string Tablet::getMemory() const { return memory; }
std::string Tablet::getMaterial() const { return material; }
bool Tablet::getHasStylus() const { return hasStylus; }

void Tablet::setMemory(const std::string& m) { memory = m; }
void Tablet::setMaterial(const std::string& m) { material = m; }
void Tablet::setHasStylus(bool s) { hasStylus = s; }

void Tablet::printInfo() const {
    std::cout << "Tablet: " << brand << ", Stylus: " << (hasStylus ? "Yes" : "No") << "\n";
}

bool Tablet::checkStylusSupport() const {
    return hasStylus;
}

// --- LAPTOP ---

Laptop::Laptop() : Electronics(), keyboardType("Standard"), audioInfo("Stereo"), wireless("Wi-Fi") {}

Laptop::Laptop(const std::string& type, const std::string& os, const std::string& brand, double price,
    const std::string& keyboardType, const std::string& audioInfo, const std::string& wireless)
    : Electronics(type, os, brand, price) {
    setKeyboardType(keyboardType);
    setAudioInfo(audioInfo);
    setWireless(wireless);
}

std::string Laptop::getKeyboardType() const { return keyboardType; }
std::string Laptop::getAudioInfo() const { return audioInfo; }
std::string Laptop::getWireless() const { return wireless; }

void Laptop::setKeyboardType(const std::string& k) { keyboardType = k; }
void Laptop::setAudioInfo(const std::string& a) { audioInfo = a; }
void Laptop::setWireless(const std::string& w) { wireless = w; }

void Laptop::printInfo() const {
    std::cout << "Laptop: " << brand << ", OS: " << os << "\n";
}

bool Laptop::hasWifiSupport() const {
    // Шукаємо слово "wifi" або "wi-fi"
    std::string w = wireless;
    std::transform(w.begin(), w.end(), w.begin(), ::tolower);
    return (w.find("fi") != std::string::npos);
}