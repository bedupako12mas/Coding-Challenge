#include "Circle.hpp"
#include "ShapeFactory.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

// Self-registration
inline bool circle_registered = registerShape<Circle>("circle");

namespace {
    constexpr double PI = 3.14159265358979323846;
}

std::string Circle::getShapeName_() const
{
    return "circle";
}

std::string Circle::getShapeDescription_() const
{
    return "has a radius.";
}

std::vector<std::string> Circle::getParameterNames_() const
{
    return {"radius"};
}

std::string Circle::getUsageExample_() const
{
    return "describe_object circle <radius>";
}

std::vector<std::string> Circle::getCalculableProperties_() const
{
    return {"perimeter", "circumference", "area"};
}

bool Circle::validateAndStoreParameters_(const std::vector<std::string>& params)
{
    if (params.size() != 1) {
        std::cerr << "Error: Circle requires exactly 1 parameter (radius)\n";
        return false;
    }

    try {
        radius_ = std::stod(params[0]);
        if (radius_ <= 0) {
            std::cerr << "Error: Radius must be positive\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Invalid radius value '" << params[0] << "'\n";
        return false;
    }

    return true;
}

void Circle::performCalculations_()
{
    circumference_ = 2 * PI * radius_;
    area_ = PI * radius_ * radius_;
}

std::string Circle::getResults_() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "\nCircle with radius " << radius_ << ":\n";
    oss << "  Circumference (Perimeter): " << circumference_ << "\n";
    oss << "  Area: " << area_ << "\n";
    return oss.str();
}

std::vector<std::string> Circle::getAvailableProperties_() const
{
    return {"radius", "diameter", "circumference", "perimeter", "area"};
}

bool Circle::hasProperty(const std::string& property_name) const
{
    auto props = getAvailableProperties_();
    return std::find(props.begin(), props.end(), property_name) != props.end();
}

double Circle::calculateProperty_(const std::string& property_name)
{
    if (property_name == "radius") {
        return radius_;
    }
    else if (property_name == "diameter") {
        return 2 * radius_;
    }
    else if (property_name == "circumference" || property_name == "perimeter") {
        return 2 * PI * radius_;
    }
    else if (property_name == "area") {
        return PI * radius_ * radius_;
    }
    return 0.0;
}

std::string Circle::getPropertyUnit_(const std::string& property_name) const
{
    if (property_name == "area") {
        return "square units";
    }
    else if (property_name == "radius" || property_name == "diameter" ||
             property_name == "circumference" || property_name == "perimeter") {
        return "units";
    }
    return "";
}
