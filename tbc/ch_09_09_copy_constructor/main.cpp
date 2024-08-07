#include <iostream>
#include <cassert>

using namespace std;

class Fraction
{
private:
    int m_numerator;
    int m_denominator;

    // copy constructor 외부에서 사용하고 싶지 않을 경우
//    Fraction(const Fraction &fraction) : m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)// copy constructor
//    {
//        cout << "Copy constructor called" << endl;
//    }

public:
    Fraction(int num = 0, int den= 1) : m_numerator(num), m_denominator(den)
    {
        assert(den!=0);
    }

    Fraction(const Fraction &fraction) : m_numerator(fraction.m_numerator), m_denominator(fraction.m_denominator)// copy constructor
    {
        cout << "Copy constructor called" << endl;
    }

    // 출력 연산자 오버로딩
    friend std::ostream & operator << (std::ostream & out, const Fraction &f)
    {
        //cout << f.m_numerator << " / " << f.m_denominator << endl;
        out << f.m_numerator << " / " << f.m_denominator << endl;
        return out;
    }

};

Fraction doSomething()
{
    Fraction temp(1,2);
    cout << "&temp = " << &temp << endl;
    return temp;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    Fraction frac(3,5);
    cout << "frac = " << frac << endl;

    Fraction fr_copy(frac);
    cout << "fr_copy = " << fr_copy << endl;

    // copy initialization -> copy constructor 호출됨
    Fraction fr_copy2 = frac;
    cout << "fr_copy2 = " << fr_copy2 << endl;


    Fraction fr_copy3(Fraction(3,10));
    cout << "fr_copy3  = " << fr_copy3 << endl;

    // 이 경우에는 copy constructor 호출 안됨
    Fraction fr_test(Fraction(3,10));
    // 컴파일러가 최적화 -> Fraction fr_test(3,10);
    cout << "fr_test = " << fr_test << endl;


    // copy constructor 호출 안됨, 반환값 최적화 , 컴파일러가 해줌
    Fraction result = doSomething();

    cout << "result = " << result << endl;

    // result와 temp 주소가 같음
    cout << "&result = " << &result << endl;

    return 0;
}
