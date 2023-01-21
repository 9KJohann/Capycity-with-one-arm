#include "Blueprint.h"

Blueprint::Blueprint(int length, int width) : _length(length), _width(width)
{
    _buildings = new Building *[length, width];
    int i = 0;
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < length; col++)
        {
            _buildings[i++] = nullptr;
        }
    }
}

Blueprint::~Blueprint()
{
    delete[] _buildings;
}

float Blueprint::getMetric() const
{
    int capacity = 0;
    int totalCost = 0;
    int area = _length * _width;

    int i = 0;
    for (int row = 0; row < _width; row++)
    {
        for (int col = 0; col < _length; col++)
        {
            Building *building = _buildings[i++];
            if (building == nullptr)
            {
                continue;
            }
            capacity += building->getCapacity();
            totalCost += building->getTotalCosts();
        }
    }

    if (area * totalCost == 0)
    {
        return 0;
    }

    return (float)capacity / (float)(area * totalCost);
}

bool Blueprint::isInBounds(int x, int y, int length, int width)
{
    return 0 <= x && 0 <= x + length && x + length <= _length && 0 <= y && 0 <= y + width && y + width <= _width;
}

void Blueprint::setBuilding(Building *building, int x, int y, int length, int width)
{
    if (!isInBounds(x, y, length, width))
    {
        throw "Eingabe liegt außerhalb des Baubereichs.";
    }
    for (int row = y; row < y + width; row++)
    {
        for (int col = x; col < x + length; col++)
        {
            if (_buildings[row * _length + col] != nullptr)
            {
                throw "Feld ist schon besetzt.";
            }
        }
    }
    for (int row = y; row < y + width; row++)
    {
        for (int col = x; col < x + length; col++)
        {
            _buildings[row * _length + col] = building;
        }
    }
}

void Blueprint::deleteBuildings(int x, int y, int length, int width)
{
    if (!isInBounds(x, y, length, width))
    {
        throw "Eingabe liegt außerhalb des Baubereichs.";
    }

    for (int row = y; row < y + width; row++)
    {
        for (int col = x; col < x + length; col++)
        {
            _buildings[row * _length + col] = nullptr;
        }
    }
}

bool Blueprint::operator()(Blueprint* blueprint) {
    if (_length != blueprint->_length || _width != blueprint->_width) {
        return false;
    }
    int i = 0;
    for(int row = 0; row < _width; row ++) {
        for(int col = 0; col < _length; col++) {
            if (_buildings[i] != blueprint->_buildings[i]) {
                return false;
            }
            i++;
        }
    }
    return true;
}

int Blueprint::getWidth() const
{
    return _width;
}

int Blueprint::getLength() const
{
    return _length;
}

Building **Blueprint::getBuildings()
{
    return _buildings;
}
