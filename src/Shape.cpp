#include "Shape.hpp"
#include <iostream>
#include <iomanip>

void Shape::describe() const
{
    std::cout << "A " << getShapeName_() << " " << getShapeDescription_()
              << "  If the user provides ";

    std::vector<std::string> param_names = getParameterNames_();
    if (param_names.size() == 1) {
        std::cout << "the " << param_names[0] << ": \n\n";
    }
    else {
        std::cout << "the ";
        for (size_t i = 0; i < param_names.size(); ++i) {
            if (i > 0 && i == param_names.size() - 1) {
                std::cout << " and ";
            }
            else if (i > 0) {
                std::cout << ", ";
            }
            std::cout << param_names[i];
        }
        std::cout << ": \n\n";
    }

    std::cout << "    \"" << getUsageExample_() << "\"\n\n";
    std::cout << "The program can calculate: ";

    std::vector<std::string> properties = getCalculableProperties_();
    for (size_t i = 0; i < properties.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << properties[i];
    }
    std::cout << "\n\nAvailable properties for queries: ";

    std::vector<std::string> available_props = getAvailableProperties_();
    for (size_t i = 0; i < available_props.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << available_props[i];
    }
    std::cout << "\n";
}

bool Shape::calculate(const std::vector<std::string>& params)
{
    if (!validateAndStoreParameters_(params)) {
        return false;
    }

    performCalculations_();
    std::cout << getResults_();
    return true;
}

bool Shape::queryProperty(const std::vector<std::string>& params,
                          const std::string& property_name)
{
    if (!validateAndStoreParameters_(params)) {
        return false;
    }

    if (!hasProperty(property_name)) {
        std::cerr << "Error: Property '" << property_name
                  << "' is not available for " << getShapeName_() << "\n";
        std::cerr << "Available properties: ";
        std::vector<std::string> props = getAvailableProperties_();
        for (size_t i = 0; i < props.size(); ++i) {
            if (i > 0) {
                std::cerr << ", ";
            }
            std::cerr << props[i];
        }
        std::cerr << "\n";
        return false;
    }

    double value = calculateProperty_(property_name);
    std::string unit = getPropertyUnit_(property_name);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << property_name << ": " << value;
    if (!unit.empty()) {
        std::cout << " " << unit;
    }
    std::cout << "\n";

    return true;
}
