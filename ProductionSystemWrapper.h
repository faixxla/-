#pragma once
#include "ProductionSystem.h" 
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Collections::Generic;

public ref class ProcessData
{
public:
    property String^ Id;
    property double Duration;
    property int Workers;
    property String^ Location;
};

public ref class AssemblyData : public ProcessData
{
public:
    property int PartsCount;
    property double AssemblyTime;
    property String^ Tool;
};

public ref class TestingData : public ProcessData
{
public:
    property String^ TestType;
    property String^ Parameters;
    property String^ Status;
    property String^ AnalysisResult;
    property double MaxLoad;
    property double MeasuredTolerance;
    property double TargetTolerance;
    property bool HasPassedSafety;
};

public ref class PackagingData : public ProcessData
{
public:
    property String^ PackageType;
    property String^ Materials;
    property String^ Design;
};

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

    void SaveToFile(String^ filename);
    void LoadFromFile(String^ filename);

    List<AssemblyData^>^ GetAllAssemblies();
    List<TestingData^>^ GetAllTests();
    List<PackagingData^>^ GetAllPackagings();

    bool UpdateAssembly(AssemblyData^ data);
    bool UpdateTestingStatus(String^ id, String^ newStatus);
    bool UpdatePackagingDesign(String^ id, String^ newDesign);

    void AddAssembly(AssemblyData^ data);
    void AddTesting(TestingData^ data);
    void AddPackaging(PackagingData^ data);

    AssemblyData^ GetAssemblyWithMaxDuration();
    List<TestingData^>^ GetAnalyzedTests();
    List<PackagingData^>^ FindPackagingByCriteria(String^ type, String^ materialSubstring);
};