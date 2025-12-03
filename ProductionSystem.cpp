#include "ProductionSystem.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

void ProductionSystem::addAssembly(const AssemblyProcess& a) {
    assemblies.push_back(a);
}

void ProductionSystem::addTesting(const TestingProcess& t) {
    tests.push_back(t);
}

void ProductionSystem::addPackaging(const PackagingProcess& p) {
    packages.push_back(p);
}

template<typename T>
T* findById(std::vector<T>& vec, const std::string& id);

bool ProductionSystem::updateAssembly(const std::string& id, double duration, int workers, int partsCount, double assemblyTime, const std::string& tool) {
    AssemblyProcess* a = findById(assemblies, id);
    if (!a) return false;

    try {
        a->setDuration(duration);
        a->setWorkers(workers);
        a->setPartsCount(partsCount);
        a->setAssemblyTime(assemblyTime);
        a->setTool(tool);
        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "Помилка при оновленні збірки: " << ex.what() << "\n";
        return false;
    }
}

bool ProductionSystem::updateTesting(const std::string& id, const std::string& status) {
    TestingProcess* t = findById(tests, id);
    if (!t) return false;

    try {
        t->setStatus(status);
        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "Помилка при оновленні випробування: " << ex.what() << "\n";
        return false;
    }
}

bool ProductionSystem::updatePackaging(const std::string& id, const std::string& design) {
    PackagingProcess* p = findById(packages, id);
    if (!p) return false;

    try {
        p->setDesign(design);
        return true;
    }
    catch (const std::exception& ex) {
        std::cerr << "Помилка при оновленні упаковки: " << ex.what() << "\n";
        return false;
    }
}

std::vector<PackagingProcess> ProductionSystem::findPackagingByCriteriaReturn(
    const std::string& type,
    const std::string& materialSubstring
) const
{
    std::vector<PackagingProcess> found;
    std::copy_if(
        packages.begin(),
        packages.end(),
        std::back_inserter(found),
        [&](const PackagingProcess& p) {
            return p.matchesCriteria(type, materialSubstring);
        }
    );

    return found;
}

const AssemblyProcess* ProductionSystem::findAssemblyWithMaxDuration() const {
    if (assemblies.empty()) {
        return nullptr;
    }
    auto it = std::max_element(assemblies.begin(), assemblies.end(), CompareByDuration());
    return &(*it);
}

void ProductionSystem::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Не вдалося відкрити файл для запису.");
    }

    try {
        for (const auto& a : assemblies) {
            out << "A;" << a.getId() << ";" << a.getDuration() << ";"
                << a.getWorkers() << ";" << a.getLocation() << ";"
                << a.getPartsCount() << ";" << a.getAssemblyTime() << ";"
                << a.getTool() << "\n";
        }
        for (const auto& t : tests) {
            out << "T;" << t.getId() << ";" << t.getDuration() << ";"
                << t.getWorkers() << ";" << t.getLocation() << ";"
                << t.getTestType() << ";" << t.getParameters() << ";"
                << t.getStatus() << ";" << t.getMaxLoad() << ";" << t.getMeasuredTolerance() << ";" << t.getTargetTolerance() << ";" << t.getHasPassedSafety() << "\n";
        }
        for (const auto& p : packages) {
            out << "P;" << p.getId() << ";" << p.getDuration() << ";"
                << p.getWorkers() << ";" << p.getLocation() << ";"
                << p.getPackageType() << ";" << p.getMaterials() << ";"
                << p.getDesign() << "\n";
        }
    }
    catch (...) {
        throw std::runtime_error("Помилка під час запису у файл.");
    }
}

void ProductionSystem::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Не вдалося відкрити файл для читання.");
    }

    assemblies.clear();
    tests.clear();
    packages.clear();

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, ';');

        try {
            if (type == "A") {
                std::string id, location, tool;
                double duration, assemblyTime;
                int workers, partsCount;

                std::string tmp;
                std::getline(ss, id, ';');
                std::getline(ss, tmp, ';');   duration = std::stod(tmp);
                std::getline(ss, tmp, ';');   workers = std::stoi(tmp);
                std::getline(ss, location, ';');
                std::getline(ss, tmp, ';');   partsCount = std::stoi(tmp);
                std::getline(ss, tmp, ';');   assemblyTime = std::stod(tmp);
                std::getline(ss, tool, ';');

                AssemblyProcess a(id, duration, workers, location,
                    partsCount, assemblyTime, tool);
                assemblies.push_back(a);
            }
            else if (type == "T") {
                std::string id, location, testType, parameters, status;
                double duration, maxLoad, measuredTolerance, targetTolerance;
                int workers;
                bool hasPassedSafety;
                std::string tmp;

                std::getline(ss, id, ';');
                std::getline(ss, tmp, ';'); duration = std::stod(tmp);
                std::getline(ss, tmp, ';'); workers = std::stoi(tmp);
                std::getline(ss, location, ';');
                std::getline(ss, testType, ';');
                std::getline(ss, parameters, ';');
                std::getline(ss, status, ';');

                std::getline(ss, tmp, ';'); maxLoad = std::stod(tmp);
                std::getline(ss, tmp, ';'); measuredTolerance = std::stod(tmp);
                std::getline(ss, tmp, ';'); targetTolerance = std::stod(tmp);
                std::getline(ss, tmp, ';'); hasPassedSafety = (std::stoi(tmp) != 0);


                TestingProcess t(id, duration, workers,
                    location, testType, parameters, status,
                    maxLoad, measuredTolerance, targetTolerance, hasPassedSafety);
                tests.push_back(t);
            }
            else if (type == "P") {
                std::string id, location, packageType, materials, design;
                double duration;
                int workers;
                std::string tmp;

                std::getline(ss, id, ';');
                std::getline(ss, tmp, ';'); duration = std::stod(tmp);
                std::getline(ss, tmp, ';'); workers = std::stoi(tmp);
                std::getline(ss, location, ';');
                std::getline(ss, packageType, ';');
                std::getline(ss, materials, ';');
                std::getline(ss, design, ';');

                PackagingProcess p(id, duration, workers, location,
                    packageType, materials, design);
                packages.push_back(p);
            }
            else {
                throw std::runtime_error("Невідомий тип запису у файлі.");
            }
        }
        catch (const std::exception& ex) {
            std::cerr << "Помилка при читанні рядка: " << ex.what()
                << "\nРядок: " << line << "\n";
        }
    }
}
