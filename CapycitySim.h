#ifndef CAPYCITY_CAPYCITYSIM_H
#define CAPYCITY_CAPYCITYSIM_H
#include "Building.h"
#include "Blueprint.h"
#include "Material.h"
#include <map>
#include <vector>

class CapycitySim {
private:
    int _length;
    int _width;
    std::vector<Blueprint*> _blueprints;
    Blueprint * _blueprint;

    public:
    CapycitySim(int length, int width);
    ~CapycitySim();
    void placeBuilding();
    void deleteArea();
    void print(Blueprint* blueprint);
    void menu();
    void addBlueprint();
};

#endif //CAPYCITY_CAPYCITYSIM_H
