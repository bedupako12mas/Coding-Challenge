#include "ShapeFactory.hpp"
#include <iostream>
#include <vector>
#include <string>

void printUsage(const char* program_name)
{
    std::cout << "Usage:\n";
    std::cout << "  " << program_name << " <shape>                         "
              << "- Describe the shape\n";
    std::cout << "  " << program_name << " <shape> <params...>             "
              << "- Calculate all properties\n";
    std::cout << "  " << program_name << " <shape> <params...> <property>  "
              << "- Query specific property\n";
    std::cout << "\nExamples:\n";
    std::cout << "  " << program_name << " circle\n";
    std::cout << "  " << program_name << " circle 5\n";
    std::cout << "  " << program_name << " circle 5 circumference\n";
    std::cout << "  " << program_name << " square 4 diagonal\n";
    std::cout << "  " << program_name << " rect 3 7 area\n";
}

bool isNumeric(const std::string& str)
{
    try {
        std::stod(str);
        return true;
    }
    catch (...) {
        return false;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string shape_name = argv[1];
    ShapeFactory& factory = ShapeFactory::getInstance();
    std::unique_ptr<Shape> shape = factory.createShape(shape_name);

    if (!shape) {
        std::cerr << "Error: Unknown shape '" << shape_name << "'\n";
        return 1;
    }

    if (argc == 2) {
        shape->describe();
        return 0;
    }

    std::vector<std::string> params;
    std::string property_query;
    bool is_property_query = false;

    if (argc >= 3) {
        std::string last_arg = argv[argc - 1];

        if (!isNumeric(last_arg) && shape->hasProperty(last_arg)) {
            is_property_query = true;
            property_query = last_arg;
            for (int i = 2; i < argc - 1; ++i) {
                params.push_back(argv[i]);
            }
        }
        else {
            for (int i = 2; i < argc; ++i) {
                params.push_back(argv[i]);
            }
        }
    }

    if (is_property_query) {
        if (!shape->queryProperty(params, property_query)) {
            std::cerr << "\nTo see usage, run: " << argv[0] << " "
                      << shape_name << "\n";
            return 1;
        }
    }
    else {
        if (!shape->calculate(params)) {
            std::cerr << "\nTo see usage, run: " << argv[0] << " "
                      << shape_name << "\n";
            return 1;
        }
    }

    return 0;
}
