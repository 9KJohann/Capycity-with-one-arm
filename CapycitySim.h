#ifndef CAPYCITY_CAPYCITYSIM_H
#define CAPYCITY_CAPYCITYSIM_H
#include "Building.h"
#include "Material.h"

class CapycitySim {
private:
    Building **_buildings;
    int _length;
    int _width;
    bool isInBounds(int x, int y, int length, int width);

    public:
    CapycitySim(int length, int width);
    ~CapycitySim();
    void placeBuilding();
    void deleteArea();
    void print();
    void menu();
};

#endif //CAPYCITY_CAPYCITYSIM_H
