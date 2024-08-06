#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::cout << "main start" << std::endl;

    {
        std::vector<int> array;

        std::vector<int> array2 = {1, 2, 3, 4, 5};

        cout << "array2.size() : " << array2.size() << endl;

        std::vector<int> array3 = {1, 2, 3};
        cout << "array3.size() : " << array3.size() << endl;

        std::vector<int> array4 {1, 2, 3};  // uniform initialization
        cout << "array4.size() : " << array4.size() << endl;
    }

    {
        vector<int> arr = {1, 2, 3, 4, 5};

        // size 늘리기
        arr.resize(10);

        // size 줄이기 , 뒤에껀 날아감
        arr.resize(2);

        for (auto &itr: arr)
            cout << "itr = " << itr << endl;

        cout << endl;

        cout << "arr[0] = " << arr[0] << endl;
        cout << "arr.at(1) = " << arr.at(1) << endl;

        cout << "arr.size() = " << arr.size() << endl;
    }

    int *my_arr = new int[5];  // 직접적인 포인터는 직접 메모리 해제를 해줘야 하는데 vector는 scopㄷ를 벗어나면 자동으로 해제해줌

    delete[] my_arr;

    cout << "end of program" << endl;

    return 0;
}
