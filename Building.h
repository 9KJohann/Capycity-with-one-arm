#ifndef CAPYCITY_BUILDING_H
#define CAPYCITY_BUILDING_H
#include <vector>
#include "Material.h"

class Building
{
protected:
    int _basePrice;
    char _label;
    char *_name;
    std::vector<Material *> _materials;

protected:
    Building(int basePrice, char label, char *name, std::vector<Material *> materials);

public:
    char *getName() const;

    char getLabel() const;

    int getBasePrice() const;

    std::vector<Material *> getMaterials() const;

    int getTotalCosts() const;
};

class WaterEnergyPlant : public Building
{
private:
    static WaterEnergyPlant *_waterEnergyPlant;

    WaterEnergyPlant();

public:
    static WaterEnergyPlant *getInstance();
};

class SolarEnergyPlant : public Building
{
private:
    static SolarEnergyPlant *_solarEnergyPlant;
    SolarEnergyPlant();

public:
    static SolarEnergyPlant *getInstance();
};

class WindEnergyPlant : public Building
{
private:
    static WindEnergyPlant *_windEnergyPlant;
    WindEnergyPlant();

public:
    static WindEnergyPlant *getInstance();
};

#endif // CAPYCITY_BUILDING_H
