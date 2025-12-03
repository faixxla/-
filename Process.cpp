#include "Process.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <locale>

static inline std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(start, end - start);
}

static inline std::string toLowerStr(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return r;
}


ProductionProcess::ProductionProcess()
    : processId("unknown"), duration(0.0), workers(0), location("unknown") {
}

ProductionProcess::ProductionProcess(const std::string& id,
    double duration,
    int workers,
    const std::string& location)
{
    setId(id);
    setDuration(duration);
    setWorkers(workers);
    setLocation(location);
}

std::string ProductionProcess::getId() const { return processId; }
double ProductionProcess::getDuration() const { return duration; }
int ProductionProcess::getWorkers() const { return workers; }
std::string ProductionProcess::getLocation() const { return location; }

void ProductionProcess::setId(const std::string& id) {
    if (id.empty())
        throw std::invalid_argument("Ідентифікатор процесу не може бути порожнім.");
    processId = id;
}

void ProductionProcess::setDuration(double d) {
    if (d <= 0)
        throw std::invalid_argument("Тривалість повинна бути більшою за 0.");
    duration = d;
}

void ProductionProcess::setWorkers(int w) {
    if (w <= 0)
        throw std::invalid_argument("Кількість працівників повинна бути більшою за 0.");
    workers = w;
}

void ProductionProcess::setLocation(const std::string& loc) {
    if (loc.empty())
        throw std::invalid_argument("Місцезнаходження не може бути порожнім.");
    location = loc;
}


AssemblyProcess::AssemblyProcess()
    : ProductionProcess(), partsCount(0), assemblyTime(0.0), tool("unknown") {
}

AssemblyProcess::AssemblyProcess(const std::string& id,
    double duration,
    int workers,
    const std::string& location,
    int partsCount,
    double assemblyTime,
    const std::string& tool)
    : ProductionProcess(id, duration, workers, location)
{
    setPartsCount(partsCount);
    setAssemblyTime(assemblyTime);
    setTool(tool);
}

int AssemblyProcess::getPartsCount() const { return partsCount; }
double AssemblyProcess::getAssemblyTime() const { return assemblyTime; }
std::string AssemblyProcess::getTool() const { return tool; }

void AssemblyProcess::setPartsCount(int count) {
    if (count <= 0)
        throw std::invalid_argument("Кількість деталей повинна бути більшою за 0.");
    partsCount = count;
}

void AssemblyProcess::setAssemblyTime(double time) {
    if (time <= 0)
        throw std::invalid_argument("Час збирання повинен бути більшим за 0.");
    assemblyTime = time;
}

void AssemblyProcess::setTool(const std::string& t) {
    if (t.empty())
        throw std::invalid_argument("Інструмент не може бути порожнім.");
    tool = t;
}

void AssemblyProcess::printInfo() const {
}


TestingProcess::TestingProcess()
    : ProductionProcess(), testType("unknown"), parameters("none"), status("pending"), maxLoad(0.0), measuredTolerance(0.0), targetTolerance(0.0), hasPassedSafety(false) {
}

TestingProcess::TestingProcess(const std::string& id,
    double duration,
    int workers,
    const std::string& location,
    const std::string& testType,
    const std::string& parameters,
    const std::string& status,
    double maxLoad,
    double measuredTolerance,
    double targetTolerance,
    bool hasPassedSafety)
    : ProductionProcess(id, duration, workers, location),
    maxLoad(maxLoad),
    measuredTolerance(measuredTolerance),
    targetTolerance(targetTolerance),
    hasPassedSafety(hasPassedSafety)
{
    setTestType(testType);
    setParameters(parameters);
    setStatus(status);

}

std::string TestingProcess::getTestType() const { return testType; }
std::string TestingProcess::getParameters() const { return parameters; }
std::string TestingProcess::getStatus() const { return status; }
double TestingProcess::getMaxLoad() const { return maxLoad; }
double TestingProcess::getMeasuredTolerance() const { return measuredTolerance; }
double TestingProcess::getTargetTolerance() const { return targetTolerance; }
bool TestingProcess::getHasPassedSafety() const { return hasPassedSafety; }

void TestingProcess::setTestType(const std::string& t) {
    if (t.empty())
        throw std::invalid_argument("Тип випробування не може бути порожнім.");
    testType = t;
}

void TestingProcess::setParameters(const std::string& p) {
    if (p.empty())
        throw std::invalid_argument("Параметри тестування не можуть бути порожніми.");
    parameters = p;
}

void TestingProcess::setStatus(const std::string& s) {
    if (s.empty())
        throw std::invalid_argument("Статус не може бути порожнім.");
    status = s;
}

void TestingProcess::printInfo() const {
}

std::string TestingProcess::analyzeResults() const {
    if (status != "completed") {
        return "Результати не можуть бути проаналізовані: випробування ще не закінчено.";
    }

    if (!hasPassedSafety) {
        return "АНАЛІЗ: НЕ ПРОЙДЕНО. Провал критичного тесту на безпеку.";
    }

    if (measuredTolerance <= targetTolerance) {
        return "АНАЛІЗ: ПРОЙДЕНО УСПІШНО. Точність (" + std::to_string(measuredTolerance) + ") в межах норми (" + std::to_string(targetTolerance) + ").";
    } else {
        return "АНАЛІЗ: НЕ ПРОЙДЕНО. Похибка перевищує допустиму норму!";
    }
}


PackagingProcess::PackagingProcess()
    : ProductionProcess(), packageType("unknown"), materials("none"), design("none") {
}

PackagingProcess::PackagingProcess(const std::string& id,
    double duration,
    int workers,
    const std::string& location,
    const std::string& packageType,
    const std::string& materials,
    const std::string& design)
    : ProductionProcess(id, duration, workers, location)
{
    setPackageType(packageType);
    setMaterials(materials);
    setDesign(design);
}

std::string PackagingProcess::getPackageType() const { return packageType; }
std::string PackagingProcess::getMaterials() const { return materials; }
std::string PackagingProcess::getDesign() const { return design; }

void PackagingProcess::setPackageType(const std::string& t) {
    if (t.empty())
        throw std::invalid_argument("Тип упаковки не може бути порожнім.");
    packageType = t;
}

void PackagingProcess::setMaterials(const std::string& m) {
    if (m.empty())
        throw std::invalid_argument("Матеріали не можуть бути порожніми.");
    materials = m;
}

void PackagingProcess::setDesign(const std::string& d) {
    if (d.empty())
        throw std::invalid_argument("Дизайн не може бути порожнім.");
    design = d;
}

void PackagingProcess::printInfo() const {

}

bool PackagingProcess::matchesCriteria(const std::string& type,
    const std::string& materialSubstring) const
{
    bool typeOk = (trim(type).empty() || toLowerStr(trim(packageType)) == toLowerStr(trim(type)));

    std::string matField = toLowerStr(trim(materials));
    std::string query = toLowerStr(trim(materialSubstring));

    bool materialOk = query.empty() || (matField.find(query) != std::string::npos);

    return typeOk && materialOk;
}

