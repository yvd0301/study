#include <iostream>
#include "Resource.h"

using namespace std;

void soSomething(std::unique_ptr<Resource> res)
{

}

// ptr2가 ptr1으로 부터 만들어지는 예제
/*
int main() {
    std::cout << "Hello, World!" << std::endl;

    Resource *res = new Resource(3); // delete 호출안하고 있음
    res->setAll(1);

    {
        std::shared_ptr<Resource> ptr1(res);
        ptr1->print();

        {
            // ptr2가 ptr1으로 부터 만들어지는 예제
            std::shared_ptr<Resource> ptr2(ptr1);

            // make shared 선호
            // auto ptr1 = std::make_shared<Resource>(3);
            // ptr1->setAll(1);

            ptr2->setAll(3);
            ptr2->print();
            std::cout << "Going out of the inner block " << endl;
        }

        ptr1->print();

        std::cout << "Going out of the outer block " << endl;
    }
    // 여기를 벗어나면 ptr1이 삭제되면서 res 도 삭제

    std::getchar();
    cout << "end of program" << endl;

    return 0;
}
*/

// ptr1, ptr2 직접 res로 부터 만들어짐
// ptr2가 res에 대한 소유권을가지고있는지 다른곳에서 알수가 없음
// inner block 나가면서 메모리 해제 하므로 -> outer block 나가면서 이중으로 해제되어 문제 발생
/*
int main() {
    std::cout << "Hello, World!" << std::endl;

    Resource *res = new Resource(3); // delete 호출안하고 있음
    res->setAll(1);

    {
        std::shared_ptr<Resource> ptr1(res);
        ptr1->print();

        {
            // ptr2가 res에 대한 소유권을가지고있는지 다른곳에서 알수가 없음
            // inner block 나가면서 메모리 해제 하므로 -> outer block 나가면서 이중으로 해제되어 문제 발생
            std::shared_ptr<Resource> ptr2(res);

            // make shared 선호
            // auto ptr1 = std::make_shared<Resource>(3);
            // ptr1->setAll(1);

            ptr2->setAll(3);
            ptr2->print();
            std::cout << "Going out of the inner block " << endl;
        }

        ptr1->print();

        std::cout << "Going out of the outer block " << endl;
    }
    // 여기를 벗어나면 ptr1이 삭제되면서 res 도 삭제

    std::getchar();
    cout << "end of program" << endl;

    return 0;
}
*/


// 마지막 shared ptr 가 소멸이 될때 Resource를 지운다.
// 어딘가에서는 지워질것이다.
int main() {
    std::cout << "Hello, World!" << std::endl;

    // 위험함, new 가 완전히 생생되어 넘어가는게 아님, 끼어듬 -> make_unique가 나음
    //soSomething(std::unique_ptr<Resource>(new Resource(1000000)) );

    //soSomething(std::make_unique<Resource>(1000000));

    // Resource *res = new Resource(3); // delete 호출안하고 있음
    // res->setAll(1);

    {
        // std::shared_ptr<Resource> ptr1(res);
        // ptr1->print();

        auto ptr1 = std::make_shared<Resource>(3);

        {
            auto ptr2 = ptr1;

            ptr2->setAll(3);
            ptr2->print();
            std::cout << "Going out of the inner block " << endl;
        }

        ptr1->print();

        std::cout << "Going out of the outer block " << endl;
    }
    // 여기를 벗어나면 ptr1이 삭제되면서 res 도 삭제

    std::getchar();
    cout << "end of program" << endl;

    return 0;
}
