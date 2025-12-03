#include "ProductionSystemWrapper.h"
#include <msclr/marshal.h> 

using namespace System;
using namespace System::Collections::Generic;
using namespace msclr::interop;


String^ ProductionSystemWrapper::StringToCli(const std::string& s) {
    return gcnew String(s.c_str());
}

std::string ProductionSystemWrapper::StringToCpp(String^ s) {
    return context.marshal_as<std::string>(s);
}


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


List<AssemblyData^>^ ProductionSystemWrapper::GetAllAssemblies()
{
    List<AssemblyData^>^ list = gcnew List<AssemblyData^>();
    for (const auto& a : systemPtr->getAssemblies()) {
        AssemblyData^ data = gcnew AssemblyData();
        data->Id = StringToCli(a.getId());
        data->Duration = a.getDuration();
        data->Workers = a.getWorkers();
        data->Location = StringToCli(a.getLocation());
        data->PartsCount = a.getPartsCount();
        data->AssemblyTime = a.getAssemblyTime();
        data->Tool = StringToCli(a.getTool());
        list->Add(data);
    }
    return list;
}

List<TestingData^>^ ProductionSystemWrapper::GetAllTests()
{
    List<TestingData^>^ list = gcnew List<TestingData^>();
    for (const auto& t : systemPtr->getTests()) {
        TestingData^ data = gcnew TestingData();
        data->Id = StringToCli(t.getId());
        data->Duration = t.getDuration();
        data->Workers = t.getWorkers();
        data->Location = StringToCli(t.getLocation());
        data->TestType = StringToCli(t.getTestType());
        data->Parameters = StringToCli(t.getParameters());
        data->Status = StringToCli(t.getStatus());
        data->MaxLoad = t.getMaxLoad();
        data->MeasuredTolerance = t.getMeasuredTolerance();
        data->TargetTolerance = t.getTargetTolerance();
        data->HasPassedSafety = t.getHasPassedSafety();

        list->Add(data);
    }
    return list;
}

List<PackagingData^>^ ProductionSystemWrapper::GetAllPackagings()
{
    List<PackagingData^>^ list = gcnew List<PackagingData^>();
    for (const auto& p : systemPtr->getPackages()) {
        PackagingData^ data = gcnew PackagingData();
        data->Id = StringToCli(p.getId());
        data->Duration = p.getDuration();
        data->Workers = p.getWorkers();
        data->Location = StringToCli(p.getLocation());
        data->PackageType = StringToCli(p.getPackageType());
        data->Materials = StringToCli(p.getMaterials());
        data->Design = StringToCli(p.getDesign());
        list->Add(data);
    }
    return list;
}

void ProductionSystemWrapper::AddAssembly(AssemblyData^ data)
{
    try {
        AssemblyProcess a(
            StringToCpp(data->Id), data->Duration, data->Workers, StringToCpp(data->Location),
            data->PartsCount, data->AssemblyTime, StringToCpp(data->Tool)
        );
        systemPtr->addAssembly(a);
    }
    catch (const std::exception& ex) {
        throw gcnew Exception(StringToCli(ex.what()));
    }
}
void ProductionSystemWrapper::AddTesting(TestingData^ data)
{
    try {
        std::string location = StringToCpp(data->Location);
        std::string testType = StringToCpp(data->TestType);
        std::string parameters = StringToCpp(data->Parameters);
        std::string status = StringToCpp(data->Status);

        TestingProcess t(
            StringToCpp(data->Id),
            data->Duration,
            data->Workers,
            location,
            testType,
            parameters,
            status,
            data->MaxLoad,
            data->MeasuredTolerance,
            data->TargetTolerance,
            data->HasPassedSafety
        );

        systemPtr->addTesting(t);
    }
    catch (const std::exception& ex) {
        throw gcnew Exception("Помилка при додаванні випробування: " + StringToCli(ex.what()));
    }
}
void ProductionSystemWrapper::AddPackaging(PackagingData^ data)
{
    try {
        PackagingProcess a(
            StringToCpp(data->Id), data->Duration, data->Workers, StringToCpp(data->Location),
            StringToCpp(data->PackageType), StringToCpp(data->Materials), StringToCpp(data->Design)
        );
        systemPtr->addPackaging(a);
    }
    catch (const std::exception& ex) {
        throw gcnew Exception(StringToCli(ex.what()));
    }
}

bool ProductionSystemWrapper::UpdateAssembly(AssemblyData^ data)
{
    std::string id = StringToCpp(data->Id);
    std::string location = StringToCpp(data->Location);
    std::string tool = StringToCpp(data->Tool);

    return systemPtr->updateAssembly(
        id,
        data->Duration,
        data->Workers,
        data->PartsCount,
        data->AssemblyTime,
        tool
    );
}

bool ProductionSystemWrapper::UpdateTestingStatus(String^ id, String^ newStatus)
{
    std::string cppId = StringToCpp(id);
    std::string cppStatus = StringToCpp(newStatus);
    return systemPtr->updateTesting(cppId, cppStatus);
}

bool ProductionSystemWrapper::UpdatePackagingDesign(String^ id, String^ newDesign)
{
    std::string cppId = StringToCpp(id);
    std::string cppDesign = StringToCpp(newDesign);
    return systemPtr->updatePackaging(cppId, cppDesign);
}


AssemblyData^ ProductionSystemWrapper::GetAssemblyWithMaxDuration()
{
    const AssemblyProcess* maxA = systemPtr->findAssemblyWithMaxDuration();
    if (!maxA) return nullptr;

    AssemblyData^ data = gcnew AssemblyData();
    data->Id = StringToCli(maxA->getId());
    data->Duration = maxA->getDuration();
    data->Workers = maxA->getWorkers();
    data->Location = StringToCli(maxA->getLocation());
    data->PartsCount = maxA->getPartsCount();
    data->AssemblyTime = maxA->getAssemblyTime();
    data->Tool = StringToCli(maxA->getTool());
    return data;
}

List<TestingData^>^ ProductionSystemWrapper::GetAnalyzedTests()
{
    List<TestingData^>^ list = gcnew List<TestingData^>();

    for (const auto& t : systemPtr->getTests()) {
        TestingData^ data = gcnew TestingData();
        data->Id = StringToCli(t.getId());
        data->Duration = t.getDuration();
        data->Workers = t.getWorkers();
        data->Location = StringToCli(t.getLocation());
        data->TestType = StringToCli(t.getTestType());
        data->Parameters = StringToCli(t.getParameters());
        data->Status = StringToCli(t.getStatus());
		data->MaxLoad = t.getMaxLoad();
		data->MeasuredTolerance = t.getMeasuredTolerance();
		data->TargetTolerance = t.getTargetTolerance();
		data->HasPassedSafety = t.getHasPassedSafety();
        data->AnalysisResult = StringToCli(t.analyzeResults());
        list->Add(data);
    }
    return list;
}

List<PackagingData^>^ ProductionSystemWrapper::FindPackagingByCriteria(String^ type, String^ materialSubstring)
{
    std::string cppType = StringToCpp(type);
    std::string cppMaterial = StringToCpp(materialSubstring);

    std::vector<PackagingProcess> foundCpp = systemPtr->findPackagingByCriteriaReturn(cppType, cppMaterial);

    List<PackagingData^>^ foundCli = gcnew List<PackagingData^>();

    for (const auto& p : foundCpp) {
        PackagingData^ data = gcnew PackagingData();
        data->Id = StringToCli(p.getId());
        data->Duration = p.getDuration();
        data->Workers = p.getWorkers();
        data->Location = StringToCli(p.getLocation());
        data->PackageType = StringToCli(p.getPackageType());
        data->Materials = StringToCli(p.getMaterials());
        data->Design = StringToCli(p.getDesign());
        foundCli->Add(data);
    }

    return foundCli;
}