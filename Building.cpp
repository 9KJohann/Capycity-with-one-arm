#include "Building.h"

Building::Building(int basePrice, char label, char *name, std::map<Material *,int> materials) : _basePrice(basePrice),
                                                                                               _label(label), _name(name),
                                                                                               _materials(materials) {}

char *Building::getName() const { return _name; }

char Building::getLabel() const { return _label; }

int Building::getBasePrice() const { return _basePrice; }

std::map<Material *, int> Building::getMaterials() const
{
    return _materials;
}

int Building::getTotalCosts() const
{
    int materialCosts = 0;
    for (auto materialCount : _materials)
    {
        Material* material = materialCount.first;
        int count = materialCount.second;
        materialCosts += material->getCost();
    }
    return _basePrice + materialCosts;
}

WaterEnergyPlant *WaterEnergyPlant::_waterEnergyPlant{nullptr};

WaterEnergyPlant::WaterEnergyPlant() : Building(1, 'W', "Wasserkraftwerk",
                                                {{Wood::getInstance(), 4}, {Plastic::getInstance(), 3}, {Metal::getInstance(), 4}}) {}

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
                                                {{Wood::getInstance(), 1}, {Plastic::getInstance(), 9}, {Metal::getInstance(), 3}}) {}

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
                                              {{Wood::getInstance(), 7}, {Plastic::getInstance(), 3}, {Metal::getInstance(), 2}}) {}

WindEnergyPlant *WindEnergyPlant::getInstance()
{
    if (_windEnergyPlant == nullptr)
    {
        _windEnergyPlant = new WindEnergyPlant();
    }
    return _windEnergyPlant;
}