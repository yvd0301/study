#include <iostream> // input output stream // cout, cin, endl

#include <cstdio> // printf

int main() {

    using namespace std;

    int x = 1024;

    double pi = 3.141592;

    std::cout << "Hello, World!\n" << std::endl;  // << output operator

    std::cout << "x = " << x << std::endl;

    std::cout << "pi = " << pi << std::endl;

    std::cout << "abc" << "\t" << "def" << std::endl;
    std::cout << "ab" << "\t" << "cdef" << std::endl;

    // 소리 출력
//    cout << "\a";

    // 입력

    int y = 10;

    cout << "Before y is = " << y << endl;

    cin >> y;

    cout << "y = " << y << endl;




    return 0;
}
