#include <iostream>
#include <map>
/*
void square(int &i){
    i = i*i;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::vector<int> myVec{1,2,3,4,5,6,7,8,9,10};

    std::for_each(myVec.begin(), myVec.end(), square);

    for(auto v:myVec){
        std::cout << v << " " ;
    }


    std::cout << "end of program" << std::endl;
    return 0;
}
*/

// 함수 오브젝트
/*
class Square {
public:
    void operator()(int & i) {
        i = i*i;
    }
};


int main(){
    std::vector<int> myVec{1,2,3,4,5,6,7,8,9,10};

    std::for_each(myVec.begin(), myVec.end(), Square());

    for(auto v:myVec){
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "end of program" << std::endl;

}
*/

int main(){
    std::map<int, std::string> myDefaultMap = {{1,"One"}, {2,"Two"}};

    // Insert values into the map
    myDefaultMap[1] = "One";
    myDefaultMap[2] = "Two";

    // Accessing values
    std::cout << "Key 1: " << myDefaultMap[1] << std::endl;
    std::cout << "Key 2: " << myDefaultMap[2] << std::endl;

    std::vector<int> myVec {1,2,3,4,5,6,7,8,9,10};
    std::for_each(myVec.begin(), myVec.end(), [](int& i){i=i*i;});
    for(auto v:myVec){
        std::cout << v << " ";
    }
    std::cout << std::endl;


    std::cout << "end of program" << std::endl;
}

