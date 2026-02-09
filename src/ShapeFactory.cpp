#include "ShapeFactory.hpp"

ShapeFactory& ShapeFactory::getInstance()
{
    static ShapeFactory instance;
    return instance;
}

bool ShapeFactory::registerShape(const std::string& name, ShapeCreator creator)
{
    if (registry_.find(name) != registry_.end()) {
        return false;
    }

    registry_[name] = creator;
    return true;
}

std::unique_ptr<Shape> ShapeFactory::createShape(const std::string& name) const
{
    auto it = registry_.find(name);
    if (it == registry_.end()) {
        return nullptr;
    }

    return it->second();
}

bool ShapeFactory::hasShape(const std::string& name) const
{
    return registry_.find(name) != registry_.end();
}
