#ifndef CAPYCITY_BLUEPRINT_H
#define CAPYCITY_BLUEPRINT_H
#include "Building.h"

class Blueprint
{
private:
    Building **_buildings;
    int _length;
    int _width;
    bool isInBounds(int x, int y, int length, int width);

public:
    Blueprint(int length, int width);
    ~Blueprint();
    float getMetric() const;
    void setBuilding(Building *building, int x, int y, int length, int width);
    void deleteBuildings(int x, int y, int length, int width);
    bool operator()(Blueprint* blueprint);
    int getWidth() const;
    int getLength() const;
    Building ** getBuildings();
};

#endif // CAPYCITY_BLUEPRINT_H