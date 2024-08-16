#include "Monster.h"
//#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    Monster mon1("Sanson", Position2D(0, 0));

    std::cout << "mon1 = " << mon1 << std::endl;

    Position2D pos2(1,1);
    mon1.moveTo(pos2);
    std::cout << mon1 << std::endl;

    {
        Monster mon2("Parsival", Position2D(0,0) );
        std::cout << "mon 2 = " << mon2 << std::endl;
    }

    return 0;
}
