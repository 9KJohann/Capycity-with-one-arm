#include <iostream>
#include "CapycitySim.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: " << std::endl;
        std::cout << "\tcapycity <length> <width>" << std::endl;
        return 1;
    }

    try
    {
        int length = std::stoi(argv[1]);
        int width = std::stoi(argv[2]);
        CapycitySim sim(length, width);
        std::cout << "Welcome to Capycity, please select an option: " << std::endl;
        sim.menu();
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
}
