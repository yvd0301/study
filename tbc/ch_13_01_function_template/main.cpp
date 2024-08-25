#include <iostream>
#include "Cents.h"

//int getMax(int x, int y)
//{
//    return (x>y)?x:y;
//}
//
//double getMax(double x, double y)
//{
//    return (x>y)?x:y;
//}

//template<class T>
template<typename T>
T getMax(T x, T y)
{
    return (x>y) ? x : y;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::cout << getMax(1,2)<< std::endl;
    std::cout << getMax(3.14, 1.592) << std::endl;
    std::cout << getMax(1.0f, 3.4f) << std::endl;
    std::cout << getMax('a', 'c' ) << std::endl;

    std::cout << getMax(Cents(5), Cents(9) ) << std::endl;

    return 0;
}
