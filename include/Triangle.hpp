#pragma once

#include "Shape.hpp"

class Triangle : public Shape
{
public:
    // Check if this shape has a given property
    bool hasProperty(const std::string& property_name) const override;

protected:
    // These methods define the shape's behavior
    std::string getShapeName_() const override;
    std::string getShapeDescription_() const override;
    std::vector<std::string> getParameterNames_() const override;
    std::string getUsageExample_() const override;
    std::vector<std::string> getCalculableProperties_() const override;

    // These methods handle input validation and calculations
    bool validateAndStoreParameters_(
        const std::vector<std::string>& params) override;
    void performCalculations_() override;
    std::string getResults_() const override;

    // These methods support property queries
    std::vector<std::string> getAvailableProperties_() const override;
    double calculateProperty_(const std::string& property_name) override;
    std::string getPropertyUnit_(const std::string& property_name) const override;

private:
    // Store the triangle's data
    double side1_ = 0.0;
    double side2_ = 0.0;
    double side3_ = 0.0;
    double perimeter_ = 0.0;
    double area_ = 0.0;
};
