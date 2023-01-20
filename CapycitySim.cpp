#include "CapycitySim.h"
#include <iostream>
#include <map>

int getInteger()
{
    int result;
    do
    {
        std::cin >> result;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cerr << "Bitte eine Zahl eingeben: " << std::endl;
        }
        else
        {
            return result;
        }
    } while (true);
};

CapycitySim::CapycitySim(int length, int width) : _length(length), _width(width)
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

CapycitySim::~CapycitySim()
{
    delete[] _buildings;
}

bool CapycitySim::isInBounds(int x, int y, int length, int width)
{
    return 0 <= x && 0 <= x + length && x + length <= _length && 0 <= y && 0 <= y + width && y + width <= _width;
}

void CapycitySim::menu()
{
    while (true)
    {
        std::cout << "1) Gebaeude plazieren" << std::endl;
        std::cout << "2) Gebaeude loeschen" << std::endl;
        std::cout << "3) Aktuellen Plan anzeigen" << std::endl;
        std::cout << "4) Beenden" << std::endl;
        std::cout << std::endl;

        std::cout << "Bitte eine Zahl auswaehlen: ";
        char option;
        std::cin >> option;

        switch (option)
        {
        case '1':
            placeBuilding();
            break;
        case '2':
            deleteArea();
            break;
        case '3':
            print();
            break;
        case '4':
            return;
        default:
            std::cout << "Keine gueltige Eingabe." << std::endl;
        }
    }
}

void CapycitySim::placeBuilding()
{
    Building *building = nullptr;
    do
    {
        std::cout << "w) Wasserkraftwerk" << std::endl;
        std::cout << "s) Solarpanele" << std::endl;
        std::cout << "a) Windkraftwerk" << std::endl;
        std::cout << "b) Zuruek" << std::endl;

        std::cout << "Waehle Gebaeudetyp: ";

        char buildingSelected;
        std::cin >> buildingSelected;

        switch (tolower(buildingSelected))
        {
        case 'w':
            building = WaterEnergyPlant::getInstance();
            break;
        case 's':
            building = SolarEnergyPlant::getInstance();
            break;
        case 'a':
            building = WindEnergyPlant::getInstance();
            break;
        case 'b':
            return;
        default:
            std::cout << "Eingabe ungueltig" << std::endl;
        }
    } while (building == nullptr);

    std::cout << "Startposition X eingeben (0 - " << _length - 1 << "): ";
    int x = getInteger();

    std::cout << "Startposition Y eingeben (0 - " << _width - 1 << "): ";
    int y = getInteger();

    std::cout << "Laenge des Gebaeudes eingeben: ";
    int length = getInteger();

    std::cout << "Breite des Gebaeudes eingeben: ";
    int width = getInteger();

    if (!isInBounds(x, y, length, width))
    {
        std::cout << "Eingabe liegt außerhalb des Baubereichs." << std::endl;
        return;
    }
    for (int row = y; row < y + width; row++)
    {
        for (int col = x; col < x + length; col++)
        {
            if (_buildings[row * _length + col] != nullptr)
            {
                std::cout << "Feld ist schon besetzt." << std::endl;
                return;
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

void CapycitySim::deleteArea()
{
    std::cout << "Startposition X eingeben (0 - " << _length - 1 << "): ";
    int x = getInteger();

    std::cout << "Startposition Y eingeben (0 - " << _width - 1 << "): ";
    int y = getInteger();

    std::cout << "Laenge fuer den zu loeschenden Bereich eingeben: ";
    int length = getInteger();

    std::cout << "Breite fuer den zu loeschenden Bereich eingeben: ";
    int width = getInteger();

    if (!isInBounds(x, y, length, width))
    {
        std::cout << "Eingabe liegt außerhalb des Baubereichs." << std::endl;
        return;
    }

    for (int row = y; row < y + width; row++)
    {
        for (int col = x; col < x + length; col++)
        {
            _buildings[row * _length + col] = nullptr;
        }
    }
}

void CapycitySim::print()
{
    std::map<Building *, int> buildingsCounter;
    int i = 0;
    for (int col = 0; col < _length + 4; col++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int row = 0; row < _width; row++)
    {
        std::cout << "| ";
        for (int col = 0; col < _length; col++)
        {
            Building *building = _buildings[i++];
            if (building == nullptr)
            {
                std::cout << "#";
                continue;
            }
            if (buildingsCounter.contains(building))
            {
                buildingsCounter[building] += 1;
            }
            else
            {
                buildingsCounter.insert({building, 1});
            }
            std::cout << building->getLabel();
        }
        std::cout << " |" << std::endl;
    }
    for (int col = 0; col < _length + 4; col++)
    {
        std::cout << "-";
    }

    int totalCosts = 0;
    for (auto count : buildingsCounter)
    {
        std::cout << std::endl;
        Building *building = count.first;
        int counter = count.second;
        totalCosts += building->getTotalCosts() * counter;
        std::cout << building->getName() << " kostet $" << building->getTotalCosts() << ":" << std::endl;
        std::cout << "\t- Grundpreis $" << building->getBasePrice() << std::endl;
        for (auto material : building->getMaterials())
        {
            std::cout << "\t- " << material->getName() << " $" << material->getCost() << std::endl;
        }
    }
    std::cout << std::endl;

    for (auto count : buildingsCounter)
    {
        Building *building = count.first;
        int counter = count.second;
        std::cout << counter << "x " << building->getName() << " kostet $" << (counter * building->getTotalCosts()) << std::endl;
    }

    std::cout << "Gesammtkosten $" << totalCosts << std::endl;

    system("pause");
}