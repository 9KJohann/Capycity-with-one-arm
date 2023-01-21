#ifndef CAPYCITY_BUILDING_H
#define CAPYCITY_BUILDING_H
#include <map>
#include "Material.h"

class Building
{
protected:
    int _basePrice;
    char _label;
    char *_name;
    int _capacity;
    std::map<Material *, int> _materials;

protected:
    Building(int basePrice, char label, char *name, std::map<Material *, int> materials, int capacity);

public:
    char *getName() const;

    char getLabel() const;

    int getBasePrice() const;

    std::map<Material *, int> getMaterials() const;

    int getTotalCosts() const;

    int getCapacity() const;
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
