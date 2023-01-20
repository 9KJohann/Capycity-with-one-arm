#include <iostream>
#include "BuildingType.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: " << std::endl;
        std::cout << "\tcapycity <length> <width>" << std::endl;
        return 1;
    }

    int length, width;
    try
    {
        length = std::stoi(argv[1]);
        width = std::stoi(argv[2]);
    }
    catch (std::invalid_argument const &ex)
    {
        std::cout << "Input must be of 2 integer numbers." << std::endl;
        return 2;
    }
    catch (std::out_of_range const &ex)
    {
        std::cout << "The number is too big." << std::endl;
        return 3;
    }

    BuildingType *blueprint = new BuildingType[length * width];
    int i = 0;
    for (int row = 0; row < width; row++)
    {
        for (int col = 0; col < length; col++)
        {
            blueprint[i++] = BuildingType::EMPTY;
        }
    }

    auto isInBounds = [length, width](int x, int y, int l, int w)
    {
        return 0 <= x && 0 <= x + l && x + l <= length && 0 <= y && 0 <= y + w && y + w <= width;
    };

    auto getInteger = []()
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

    auto placeBuilding = [length, width, blueprint, &getInteger, &isInBounds]()
    {
        BuildingType selectedFieldType = EMPTY;
        do
        {
            std::cout << "w) Wasserkraftwerk" << std::endl;
            std::cout << "s) Solarpanele" << std::endl;
            std::cout << "i) Windkraftwerk" << std::endl;
            std::cout << "b) Zuruek" << std::endl;

            std::cout << "Waehle Gebaeudetyp: ";

            char buildingSelected;
            std::cin >> buildingSelected;

            switch (tolower(buildingSelected))
            {
            case 'w':
                selectedFieldType = WATER_ENERGY_PLANT;
                break;
            case 's':
                selectedFieldType = SOLAR_ENERGY_PLANT;
                break;
            case 'i':
                selectedFieldType = WIND_ENERGY_PLANT;
                break;
            case 'b':
                return;
            default:
                std::cout << "Eingabe ungueltig" << std::endl;
            }
        } while (selectedFieldType == EMPTY);

        std::cout << "Startposition X eingeben (0 - " << length - 1 << "): ";
        int x = getInteger();

        std::cout << "Startposition Y eingeben (0 - " << width - 1 << "): ";
        int y = getInteger();

        std::cout << "Laenge des Gebaeudes eingeben: ";
        int buildingLength = getInteger();

        std::cout << "Breite des Gebaeudes eingeben: ";
        int buildingWidth = getInteger();

        if (!isInBounds(x, y, buildingLength, buildingWidth))
        {
            std::cout << "Eingabe liegt außerhalb des Baubereichs." << std::endl;
            return;
        }
        for (int row = y; row < y + buildingWidth; row++)
        {
            for (int col = x; col < x + buildingLength; col++)
            {
                if (blueprint[row * length + col] != EMPTY)
                {
                    std::cout << "Feld ist schon besetzt." << std::endl;
                    return;
                }
            }
        }
        for (int row = y; row < y + buildingWidth; row++)
        {
            for (int col = x; col < x + buildingLength; col++)
            {
                blueprint[row * length + col] = selectedFieldType;
            }
        }
    };

    auto deleteArea = [length, width, blueprint, &getInteger, &isInBounds]()
    {
        std::cout << "Startposition X eingeben (0 - " << length - 1 << "): ";
        int x = getInteger();

        std::cout << "Startposition Y eingeben (0 - " << width - 1 << "): ";
        int y = getInteger();

        std::cout << "Laenge fuer den zu loeschenden Bereich eingeben: ";
        int buildingLength = getInteger();

        std::cout << "Breite fuer den zu loeschenden Bereich eingeben: ";
        int buildingWidth = getInteger();

        if (!isInBounds(x, y, buildingLength, buildingWidth))
        {
            std::cout << "Eingabe liegt außerhalb des Baubereichs." << std::endl;
            return;
        }
        for (int row = y; row < y + buildingWidth; row++)
        {
            for (int col = x; col < x + buildingLength; col++)
            {
                blueprint[row * length + col] = EMPTY;
            }
        }
    };
    
    auto showConstructionPlan = [blueprint, length, width]()
    {
        int i = 0;
        for (int row = 0; row < width; row++)
        {
            for (int col = 0; col < length; col++)
            {
                std::cout << blueprint[i++];
            }
            std::cout << std::endl;
        }
        system("pause");
    };

    std::cout << "Welcome to Capycity, please select an option: " << std::endl;

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
            showConstructionPlan();
            break;
        case '4':
            return 0;
        default:
            std::cout << "Keine gueltige Eingabe." << std::endl;
        }
    }
}
