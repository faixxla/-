#pragma once
#include <string>
#include <iostream>
#include <stdexcept>

class ProductionProcess {
protected:
    std::string processId;
    double duration;
    int workers;
    std::string location;

public:
    ProductionProcess();
    ProductionProcess(const std::string& id,
        double duration,
        int workers,
        const std::string& location);

    virtual ~ProductionProcess() = default;
    virtual void printInfo() const = 0;

    std::string getId() const;
    double getDuration() const;
    int getWorkers() const;
    std::string getLocation() const;

    void setId(const std::string& id);
    void setDuration(double d);
    void setWorkers(int w);
    void setLocation(const std::string& loc);
};


class AssemblyProcess : public ProductionProcess {
private:
    int partsCount;
    double assemblyTime;
    std::string tool;

public:
    AssemblyProcess();
    AssemblyProcess(const std::string& id,
        double duration,
        int workers,
        const std::string& location,
        int partsCount,
        double assemblyTime,
        const std::string& tool);

    int getPartsCount() const;
    double getAssemblyTime() const;
    std::string getTool() const;

    void setPartsCount(int count);
    void setAssemblyTime(double time);
    void setTool(const std::string& tool);

    void printInfo() const override;
};


class TestingProcess : public ProductionProcess {
private:
    std::string testType;
    std::string parameters;
    std::string status;
    double maxLoad;
    double measuredTolerance;
    double targetTolerance;
    bool hasPassedSafety;
public:
    TestingProcess();
    TestingProcess(const std::string& id,
        double duration,
        int workers,
        const std::string& location,
        const std::string& testType,
        const std::string& parameters,
        const std::string& status,
        double maxLoad, double measuredTolerance, double targetTolerance,
        bool hasPassedSafety);

    std::string getTestType() const;
    std::string getParameters() const;
    std::string getStatus() const;
    double getMaxLoad() const;
    double getMeasuredTolerance() const;
    double getTargetTolerance() const;
    bool getHasPassedSafety() const;

    void setTestType(const std::string& t);
    void setParameters(const std::string& p);
    void setStatus(const std::string& s);


    void printInfo() const override;

    std::string analyzeResults() const;
};


class PackagingProcess : public ProductionProcess {
private:
    std::string packageType;
    std::string materials;
    std::string design;

public:
    PackagingProcess();
    PackagingProcess(const std::string& id,
        double duration,
        int workers,
        const std::string& location,
        const std::string& packageType,
        const std::string& materials,
        const std::string& design);

    std::string getPackageType() const;
    std::string getMaterials() const;
    std::string getDesign() const;

    void setPackageType(const std::string& t);
    void setMaterials(const std::string& m);
    void setDesign(const std::string& d);

    void printInfo() const override;

    bool matchesCriteria(const std::string& type,
        const std::string& materialSubstring) const;
};

#include <vector>

template<typename T>
void printVector(const std::vector<T>& vec) {
    if (vec.empty()) {
        std::cout << "Список порожній.\n";
        return;
    }
    for (const auto& item : vec) {
        item.printInfo();
    }
}

template<typename T>
T* findById(std::vector<T>& vec, const std::string& id) {
    for (auto& item : vec) {
        if (item.getId() == id) {
            return &item;
        }
    }
    return nullptr;
}


struct CompareByDuration {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a.getDuration() < b.getDuration();
    }
};
