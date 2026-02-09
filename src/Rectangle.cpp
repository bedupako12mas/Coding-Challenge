#include "Rectangle.hpp"
#include "ShapeFactory.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cmath>

// Self-registration
inline bool rectangle_registered = registerShape<Rectangle>("rect");

std::string Rectangle::getShapeName_() const
{
    return "rectangle";
}

std::string Rectangle::getShapeDescription_() const
{
    return "has 4 sides broken into 2 side pairs of equal length and are parallel.";
}

std::vector<std::string> Rectangle::getParameterNames_() const
{
    return {"length side 1", "length side 2"};
}

std::string Rectangle::getUsageExample_() const
{
    return "describe_object rect <length side 1> <length side 2>";
}

std::vector<std::string> Rectangle::getCalculableProperties_() const
{
    return {"perimeter", "area"};
}

bool Rectangle::validateAndStoreParameters_(const std::vector<std::string>& params)
{
    if (params.size() != 2) {
        std::cerr << "Error: Rectangle requires exactly 2 parameters "
                  << "(length side 1, length side 2)\n";
        return false;
    }

    try {
        length1_ = std::stod(params[0]);
        length2_ = std::stod(params[1]);

        if (length1_ <= 0 || length2_ <= 0) {
            std::cerr << "Error: All lengths must be positive\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Invalid length values\n";
        return false;
    }

    return true;
}

void Rectangle::performCalculations_()
{
    perimeter_ = 2 * (length1_ + length2_);
    area_ = length1_ * length2_;
}

std::string Rectangle::getResults_() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "\nRectangle with sides " << length1_ << " and " << length2_ << ":\n";
    oss << "  Perimeter: " << perimeter_ << "\n";
    oss << "  Area: " << area_ << "\n";
    return oss.str();
}

std::vector<std::string> Rectangle::getAvailableProperties_() const
{
    return {"length", "width", "length1", "length2",
            "perimeter", "area", "diagonal"};
}

bool Rectangle::hasProperty(const std::string& property_name) const
{
    auto props = getAvailableProperties_();
    return std::find(props.begin(), props.end(), property_name) != props.end();
}

double Rectangle::calculateProperty_(const std::string& property_name)
{
    if (property_name == "length" || property_name == "length1") {
        return length1_;
    }
    else if (property_name == "width" || property_name == "length2") {
        return length2_;
    }
    else if (property_name == "perimeter") {
        return 2 * (length1_ + length2_);
    }
    else if (property_name == "area") {
        return length1_ * length2_;
    }
    else if (property_name == "diagonal") {
        return std::sqrt(length1_ * length1_ + length2_ * length2_);
    }
    return 0.0;
}

std::string Rectangle::getPropertyUnit_(const std::string& property_name) const
{
    if (property_name == "area") {
        return "square units";
    }
    else if (property_name == "length" || property_name == "width" ||
             property_name == "length1" || property_name == "length2" ||
             property_name == "perimeter" || property_name == "diagonal") {
        return "units";
    }
    return "";
}
