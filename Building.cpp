#include "Building.h"

Building::Building(int basePrice, char label, char *name, std::vector<Material *> materials) : _basePrice(basePrice),
                                                                                               _label(label), _name(name),
                                                                                               _materials(materials) {}

char *Building::getName() const { return _name; }

char Building::getLabel() const { return _label; }

int Building::getBasePrice() const { return _basePrice; }

std::vector<Material *> Building::getMaterials() const
{
    return _materials;
}

int Building::getTotalCosts() const
{
    int materialCosts = 0;
    for (auto material : _materials)
    {
        materialCosts += material->getCost();
    }
    return _basePrice + materialCosts;
}

WaterEnergyPlant *WaterEnergyPlant::_waterEnergyPlant{nullptr};

WaterEnergyPlant::WaterEnergyPlant() : Building(1, 'W', "Wasserkraftwerk",
                                                {Wood::getInstance(), Wood::getInstance(), Plastic::getInstance(), Plastic::getInstance(),
                                                 Metal::getInstance()}) {}

WaterEnergyPlant *WaterEnergyPlant::getInstance()
{
    if (_waterEnergyPlant == nullptr)
    {
        _waterEnergyPlant = new WaterEnergyPlant();
    }
    return _waterEnergyPlant;
}

SolarEnergyPlant *SolarEnergyPlant::_solarEnergyPlant{nullptr};

SolarEnergyPlant::SolarEnergyPlant() : Building(1, 'S', "Solarpanele",
                                                {Plastic::getInstance(), Plastic::getInstance(), Plastic::getInstance(), Metal::getInstance(),
                                                 Metal::getInstance()}) {}

SolarEnergyPlant *SolarEnergyPlant::getInstance()
{
    if (_solarEnergyPlant == nullptr)
    {
        _solarEnergyPlant = new SolarEnergyPlant();
    }
    return _solarEnergyPlant;
}

WindEnergyPlant *WindEnergyPlant::_windEnergyPlant{nullptr};

WindEnergyPlant::WindEnergyPlant() : Building(1, 'A', "Windkraftwerk",
                                              {Wood::getInstance(), Wood::getInstance(), Plastic::getInstance(), Metal::getInstance(),
                                               Metal::getInstance()}) {}

WindEnergyPlant *WindEnergyPlant::getInstance()
{
    if (_windEnergyPlant == nullptr)
    {
        _windEnergyPlant = new WindEnergyPlant();
    }
    return _windEnergyPlant;
}