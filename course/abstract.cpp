#include <iostream>
using namespace std;

// abstract functions
// pure virtual functions

class Animal // it does not make sense to instantiate from Animal
             // as there is no abstract animal in the world
             // but it does make sense to let all animals derive from abstract animal
             // for that purpose, abstract classes exist
             // abstract classes only have pure pure virtual functions,
             // that is method with no implementation
{
public:
    virtual void speak() = 0; // pure virtual function
    virtual void run() = 0;
};

class Dog: public Animal // derived class has to provide implementation
                         // of all virtual functions existing in super class
                         // to be instantiatable, otherwise it's still abstract
{
public:
    virtual void speak() //virtual can be repeated, doesn't have to
    {
        cout << "Woof!" << endl;
    }
};

class Labrador: public Dog
{
public:
    virtual void run()
    {
        cout << "Labrador running!" << endl;
    }
};

// design Function for abstract class
void test(Animal &a)
{
    a.run();
}

int main()
{
    //Animal animal; //we can't instantiate Animal, as it has pure virtual functions
    //Dog dog; // dog has not implemented all pure functions!

    Labrador labrador; //labdrador works, all pure functions implemented
    labrador.speak();
    labrador.run();

    // we can't create array of Animals,
    // as creating would need their constructor
    // and would have to instantiate them

    Labrador labs[5]; //Array of Labradors works

    // We can create pointers to animals:
    Animal *animals[5];
    // we can add addresses of concrete (non-abstract) classes in there:
    animals[0] = &labrador;
    // and we can call now with this array
    (*animals[0]).speak();

    // we can create and use functions designed for the abstract class
    test(labrador);

    return 0;
}
