#include "Square.hpp"
#include "ShapeFactory.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cmath>

// Self-registration
inline bool square_registered = registerShape<Square>("square");

std::string Square::getShapeName_() const
{
    return "square";
}

std::string Square::getShapeDescription_() const
{
    return "has four sides that are of equal length.";
}

std::vector<std::string> Square::getParameterNames_() const
{
    return {"length"};
}

std::string Square::getUsageExample_() const
{
    return "describe_object square <length>";
}

std::vector<std::string> Square::getCalculableProperties_() const
{
    return {"perimeter", "area"};
}

bool Square::validateAndStoreParameters_(const std::vector<std::string>& params)
{
    if (params.size() != 1) {
        std::cerr << "Error: Square requires exactly 1 parameter (length)\n";
        return false;
    }

    try {
        length_ = std::stod(params[0]);
        if (length_ <= 0) {
            std::cerr << "Error: Length must be positive\n";
            return false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: Invalid length value '" << params[0] << "'\n";
        return false;
    }

    return true;
}

void Square::performCalculations_()
{
    perimeter_ = 4 * length_;
    area_ = length_ * length_;
}

std::string Square::getResults_() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "\nSquare with side length " << length_ << ":\n";
    oss << "  Perimeter: " << perimeter_ << "\n";
    oss << "  Area: " << area_ << "\n";
    return oss.str();
}

std::vector<std::string> Square::getAvailableProperties_() const
{
    return {"side", "length", "perimeter", "area", "diagonal"};
}

bool Square::hasProperty(const std::string& property_name) const
{
    auto props = getAvailableProperties_();
    return std::find(props.begin(), props.end(), property_name) != props.end();
}

double Square::calculateProperty_(const std::string& property_name)
{
    if (property_name == "side" || property_name == "length") {
        return length_;
    }
    else if (property_name == "perimeter") {
        return 4 * length_;
    }
    else if (property_name == "area") {
        return length_ * length_;
    }
    else if (property_name == "diagonal") {
        return length_ * std::sqrt(2);
    }
    return 0.0;
}

std::string Square::getPropertyUnit_(const std::string& property_name) const
{
    if (property_name == "area") {
        return "square units";
    }
    else if (property_name == "side" || property_name == "length" ||
             property_name == "perimeter" || property_name == "diagonal") {
        return "units";
    }
    return "";
}
