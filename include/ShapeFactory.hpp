#pragma once

#include "Shape.hpp"
#include <memory>
#include <map>
#include <functional>

class ShapeFactory
{
public:
    using ShapeCreator = std::function<std::unique_ptr<Shape>()>;

    static ShapeFactory& getInstance();

    bool registerShape(const std::string& name, ShapeCreator creator);
    std::unique_ptr<Shape> createShape(const std::string& name) const;
    bool hasShape(const std::string& name) const;

private:
    ShapeFactory() = default;
    ShapeFactory(const ShapeFactory&) = delete;
    ShapeFactory& operator=(const ShapeFactory&) = delete;

    std::map<std::string, ShapeCreator> registry_;
};

// Helper function for self-registration pattern
template<typename T>
inline bool registerShape(const std::string& name) {
    return ShapeFactory::getInstance().registerShape(name,
        []() -> std::unique_ptr<Shape> { return std::make_unique<T>(); });
}
