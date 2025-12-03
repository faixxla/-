#pragma once
#include "Process.h"
#include <vector>
#include <string>

class ProductionSystem {
private:
    std::vector<AssemblyProcess> assemblies;
    std::vector<TestingProcess> tests;
    std::vector<PackagingProcess> packages;

public:
    void addAssembly(const AssemblyProcess& a);
    void addTesting(const TestingProcess& t);
    void addPackaging(const PackagingProcess& p);

    bool updateAssembly(const std::string& id, double duration, int workers, int partsCount, double assemblyTime, const std::string& tool);
    bool updateTesting(const std::string& id, const std::string& status);
    bool updatePackaging(const std::string& id, const std::string& design);

    const std::vector<AssemblyProcess>& getAssemblies() const { return assemblies; }
    const std::vector<TestingProcess>& getTests() const { return tests; }
    const std::vector<PackagingProcess>& getPackages() const { return packages; }

    const AssemblyProcess* findAssemblyWithMaxDuration() const;

    std::vector<PackagingProcess> findPackagingByCriteriaReturn(const std::string& type,
        const std::string& materialSubstring) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};