#include <iostream>
#include <string>

using namespace std;

class Animal
{
protected:
    string m_name;
public:
    Animal(std::string name) : m_name(name){}

public:
    string getName() {
        return m_name;
    }

//    void speak() const
//    {
//        cout << m_name << " ??? " << endl;
//    }

    virtual void speak() const
    {
        cout << m_name << " ??? " << endl;
    }
};

// Cat is an animal
class Cat: public Animal
{
public:
    Cat(string name) : Animal (name)
    {
    }

    void speak() const
    {
        cout << m_name << " Meow " << endl;
    }
};

class Dog : public Animal
{
public:
    Dog(string name): Animal(name)
    {
    }

    void speak() const
    {
        cout << m_name << " Woof " << endl;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    {
        Animal animal("my animal");

        Cat cat("my cat");
        Dog dog("my dog");

        cout << "animal.speak() : " << endl;
        animal.speak();

        cout << "cat.speak() : " << endl;
        cat.speak();

        cout << "dog.speak() : " << endl;
        dog.speak();
        cout << endl << endl;

        Animal *ptr_animal1 = &cat;
        Animal *ptr_animal2 = &dog;

        cout << "ptr_animal1->speak() : " << endl;
        ptr_animal1->speak();

        cout << "ptr_animal2->speak() : " << endl;
        ptr_animal2->speak();
    }

    cout << endl << endl;

    Cat cats[] = {Cat("cat1"), Cat("cat2"), Cat("cat3"), Cat("cat4"), Cat("cat5")};
    Dog dogs[] = { Dog("dog1"), Dog("dog2")};

    for(int i = 0 ; i<5; ++i )
    {
        cats[i].speak();
    }
    cout << endl << endl;

    for(int i = 0; i <2 ; ++i)
    {
        dogs[i].speak();
    }
    cout << endl << endl;

    Animal *my_animals[] = {&cats[0], &cats[1], &cats[2], &cats[3], &cats[4], &dogs[0], &dogs[1] };

    for( int i = 0 ; i < 7 ; ++i ){
        my_animals[i]->speak();
    }

    return 0;
}
