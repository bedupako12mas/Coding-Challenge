#pragma once

#include <string>
#include <vector>

class Shape
{
public:
    virtual ~Shape() = default;

    void describe() const;
    bool calculate(const std::vector<std::string>& params);
    bool queryProperty(const std::vector<std::string>& params,
                      const std::string& property_name);

    virtual bool hasProperty(const std::string& property_name) const = 0;

protected:
    virtual std::string getShapeName_() const = 0;
    virtual std::string getShapeDescription_() const = 0;
    virtual std::vector<std::string> getParameterNames_() const = 0;
    virtual std::string getUsageExample_() const = 0;
    virtual std::vector<std::string> getCalculableProperties_() const = 0;

    virtual bool validateAndStoreParameters_(
        const std::vector<std::string>& params) = 0;
    virtual void performCalculations_() = 0;
    virtual std::string getResults_() const = 0;

    virtual std::vector<std::string> getAvailableProperties_() const = 0;
    virtual double calculateProperty_(const std::string& property_name) = 0;
    virtual std::string getPropertyUnit_(
        const std::string& property_name) const = 0;
};
