#include "Logic.h"
#include <vector>
#include <iostream>
#include "Logic.h"

int main(int argc, char* argv[])
{
    int size_w;
    int size_h;
    int size_pxl = 5;
    int init_length = 15;

    // User input
    std::cout << "Please define the height of the field: \n";
    std::cout << "H = ";
    std::cin >> size_h;
    std::cout << std::endl;

    std::cout << "Please define the width of the field: \n";
    std::cout << "W = ";
    std::cin >> size_w;
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Game started...\n";

    Logic game = Logic(size_h, size_w, init_length);
    int status = game.start();

    if (status == 1)
        std::cout << "GAME OVER..!\n";
}
