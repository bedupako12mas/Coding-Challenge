#pragma once

#include "Shape.hpp"

class Circle : public Shape
{
public:
    bool hasProperty(const std::string& property_name) const override;

protected:
    std::string getShapeName_() const override;
    std::string getShapeDescription_() const override;
    std::vector<std::string> getParameterNames_() const override;
    std::string getUsageExample_() const override;
    std::vector<std::string> getCalculableProperties_() const override;
    bool validateAndStoreParameters_(
        const std::vector<std::string>& params) override;
    void performCalculations_() override;
    std::string getResults_() const override;

    std::vector<std::string> getAvailableProperties_() const override;
    double calculateProperty_(const std::string& property_name) override;
    std::string getPropertyUnit_(const std::string& property_name) const override;

private:
    double radius_ = 0.0;
    double circumference_ = 0.0;
    double area_ = 0.0;
};
