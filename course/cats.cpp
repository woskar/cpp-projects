#include <iostream>
#include "Cat.h"

using namespace std;

int Cat::number_of_lives = 7;


int main()
{
    std::cout << "Starting program" << std::endl;

    {
        Cat garfield;
        garfield.speak();
        garfield.jump();
        std::cout << garfield.to_string() << std::endl;
        garfield.setName("Garfield");
        garfield.setAge(42);
        std::cout << garfield.to_string() << std::endl;
        std::cout << &garfield << std::endl;

        Cat frodo("Frodo", 12, true);
        std::cout << &frodo << std::endl;
        std::cout << frodo.to_string() << std::endl;

        // Copy constructor is invoked here
        Cat freddy = frodo;
        freddy.setName("Freddy");

        // Other way to invoke Copy constructor:
        Cat fridolin(garfield);
        fridolin.setName("Fridolin");

        frodo.speak();
        freddy.speak();
        fridolin.speak();


    }

    // new allocates new Memory wich must be freed.
    Cat *pCat = new Cat();
    (*pCat).setName("Pointer Cat");
    pCat->speak(); //*. is same as ->
    delete pCat; //this will call the Destructor

    //Cat *Cat2 = NULL; // For NULL, we could use 0 as well

    // Store pointers in long, as both have 8 Bytes
    //cout << sizeof(pCat) << endl;

    Cat * pCat2 = createCat(); // there is new called in the method!
    pCat2->speak();
    delete pCat2;
    // we need to delete the pointer Cat which we got from the Method


    // new can even be called with primitive Types:
    int * pInt = new int;
    *pInt = 8;
    cout << *pInt << endl;
    delete pInt;


    // Allocate Memory for multiple cats:
    Cat * pCats = new Cat[3];
    pCats[2].setName("I'm the third cat");
    pCats[1].speak();
    pCats[2].speak();
    delete [] pCats; //call delete with [] to delete all!

/*
    // Exercise: Initialize the abcCats
    Cat * abcCats = new Cat[26];
    char letter = 'a';
    for(int i = 0; i<26; ++i)
    {
        string name(1, letter);
        abcCats[i].setName(name);
        abcCats[i].speak();
        letter++;
    }
    delete [] abcCats;

    // Allocate Memory for Array of Chars:
    char * pMem = new char[1000];
    delete [] pMem;
*/

    WildCat wildcat;
    wildcat.speak();
    wildcat.run();

    WildCat tiger("Tiger", 3, false);
    tiger.speak();

    Cat::showLives();



    std::cout << "Ending program" << std::endl;
    return 0;
}
