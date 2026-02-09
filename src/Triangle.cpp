#include "Triangle.hpp"
#include "ShapeFactory.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

// Self-registration
inline bool triangle_registered = registerShape<Triangle>("triangle");

std::string Triangle::getShapeName_() const
{
    return "triangle";
}

std::string Triangle::getShapeDescription_() const
{
    return "has three sides.";
}

std::vector<std::string> Triangle::getParameterNames_() const
{
    return {"side1", "side2", "side3"};
}

std::string Triangle::getUsageExample_() const
{
    return "describe_object triangle <side1> <side2> <side3>";
}

std::vector<std::string> Triangle::getCalculableProperties_() const
{
    return {"perimeter", "area"};
}

bool Triangle::validateAndStoreParameters_(const std::vector<std::string>& params)
{
    if (params.size() != 3) {
        std::cerr << "Error: Triangle requires exactly 3 parameters\n";
        return false;
    }

    try {
        side1_ = std::stod(params[0]);
        side2_ = std::stod(params[1]);
        side3_ = std::stod(params[2]);

        if (side1_ <= 0 || side2_ <= 0 || side3_ <= 0) {
            std::cerr << "Error: All sides must be positive\n";
            return false;
        }

        // Validate triangle inequality: sum of any two sides > third side
        if (side1_ + side2_ <= side3_ ||
            side1_ + side3_ <= side2_ ||
            side2_ + side3_ <= side1_) {
            std::cerr << "Error: Invalid triangle (triangle inequality violated)\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Invalid side values\n";
        return false;
    }

    return true;
}

void Triangle::performCalculations_()
{
    perimeter_ = side1_ + side2_ + side3_;

    // Use Heron's formula to calculate area
    // Area = sqrt(s * (s - a) * (s - b) * (s - c))
    // where s = semi-perimeter = (a + b + c) / 2
    double s = perimeter_ / 2.0;
    area_ = std::sqrt(s * (s - side1_) * (s - side2_) * (s - side3_));
}

std::string Triangle::getResults_() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "\nTriangle with sides " << side1_ << ", "
        << side2_ << ", " << side3_ << ":\n";
    oss << "  Perimeter: " << perimeter_ << "\n";
    oss << "  Area: " << area_ << "\n";
    return oss.str();
}

std::vector<std::string> Triangle::getAvailableProperties_() const
{
    return {"side1", "side2", "side3", "perimeter", "area"};
}

bool Triangle::hasProperty(const std::string& property_name) const
{
    auto props = getAvailableProperties_();
    return std::find(props.begin(), props.end(), property_name) != props.end();
}

double Triangle::calculateProperty_(const std::string& property_name)
{
    if (property_name == "side1") {
        return side1_;
    }
    else if (property_name == "side2") {
        return side2_;
    }
    else if (property_name == "side3") {
        return side3_;
    }
    else if (property_name == "perimeter") {
        return side1_ + side2_ + side3_;
    }
    else if (property_name == "area") {
        double s = (side1_ + side2_ + side3_) / 2.0;
        return std::sqrt(s * (s - side1_) * (s - side2_) * (s - side3_));
    }
    return 0.0;
}

std::string Triangle::getPropertyUnit_(const std::string& property_name) const
{
    if (property_name == "area") {
        return "square units";
    }
    else if (property_name == "side1" || property_name == "side2" ||
             property_name == "side3" || property_name == "perimeter") {
        return "units";
    }
    return "";
}
