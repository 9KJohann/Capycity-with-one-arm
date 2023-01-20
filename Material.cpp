#include "Material.h"

Material::Material(int cost, char *name) : _cost(cost), _name(name) {}

char *Material::getName() const
{
    return _name;
}

int Material::getCost() const
{
    return _cost;
}

Wood *Wood::_wood{nullptr};

Wood::Wood() : Material(25, "Holz") {}

Wood *Wood::getInstance()
{
    if (_wood == nullptr)
    {
        _wood = new Wood();
    }
    return _wood;
}

Plastic *Plastic::_plastic{nullptr};

Plastic::Plastic() : Material(8, "Kunststoff") {}

Plastic *Plastic::getInstance()
{
    if (_plastic == nullptr)
    {
        _plastic = new Plastic();
    }
    return _plastic;
}

Metal *Metal::_metal{nullptr};

Metal::Metal() : Material(37, "Metall") {}

Metal *Metal::getInstance()
{
    if (_metal == nullptr)
    {
        _metal = new Metal();
    }
    return _metal;
}