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
    _blueprint = new Blueprint(length, width);
}

CapycitySim::~CapycitySim()
{
    delete _blueprint;
}

void CapycitySim::menu()
{
    while (true)
    {
        std::cout << "1) Gebaeude plazieren" << std::endl;
        std::cout << "2) Gebaeude loeschen" << std::endl;
        std::cout << "3) Aktuellen Plan anzeigen" << std::endl;
        std::cout << "4) Neuen Plan anlegen" << std::endl;
        std::cout << "5) Gespeicherte Pläne anzeigen" << std::endl;
        std::cout << "6) Beenden" << std::endl;
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
        std::cout << "Aktueller Plan:" << std::endl;
            print(_blueprint);
            break;
        case '4':
            addBlueprint();
            break;
        case '5':
            std::sort(_blueprints.begin(), _blueprints.end(), [](Blueprint* a, Blueprint* b){
                return a->getMetric() > b->getMetric();
            });
            std::cout << "Gespeicherte Plaene:" << std::endl;
            std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            for(Blueprint* blueprint: _blueprints) {
                print(blueprint);
                std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
            }
            break;
        case '6':
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

    try
    {
        _blueprint->setBuilding(building, x, y, length, width);
    }
    catch (const char *msg)
    {
        std::cout << msg;
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

    try
    {
        _blueprint->deleteBuildings(x, y, length, width);
    }
    catch (const char *msg)
    {
        std::cout << msg;
    }
}

void CapycitySim::print(Blueprint* blueprint)
{
    std::map<Building *, int> buildingsCounter;
    Building** buildings = blueprint->getBuildings();
    int i = 0;
    for (int col = 0; col < _length + 4; col++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    for (int row = 0; row < blueprint->getWidth(); row++)
    {
        std::cout << "| ";
        for (int col = 0; col < blueprint->getLength(); col++)
        {
            Building *building = buildings[i++];
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
        for (auto materialCount : building->getMaterials())
        {
            auto material = materialCount.first;
            int count = materialCount.second;
            std::cout << "\t- " << count << "x " << material->getName() << " $" << material->getCost() << std::endl;
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
    std::cout << "Metrik: " << blueprint->getMetric() << std::endl; 

    system("pause");
}

void CapycitySim::addBlueprint()
{
    for (Blueprint *blueprint : _blueprints)
    {
        if (_blueprint->operator()(blueprint))
        {
            std::cout << "Plan ist bereits vorhanden. Soll der aktuelle verworfen werden? (j/N): ";
            char input;
            std::cin >> input;
            if (tolower(input) == 'j')
            {

                _blueprint = new Blueprint(_length, _width);
            }
            else
            {
                std::cout << "Abbruch..." << std::endl;
            }
            return;
        }
    }
    _blueprints.push_back(_blueprint);
    _blueprint = new Blueprint(_length, _width);
}