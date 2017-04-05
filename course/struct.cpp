#include <iostream>

// use preprocessor directive to prevent padding, see in struct
#pragma pack(push, 1) //"allign Data on single byte boundaries"

struct Person
{
    // C++ will make this struct efficient to work with,
    // it has size 64 (a power of 2) instead of the actual 62
    // so there is padding done.
    char name[50];
    int age;
    double weight;
};

#pragma pack(pop) //turn off packing at this point

int main()
{
    std::cout << sizeof(double) << " "<< sizeof(int) << " " << sizeof(char[50])<< std::endl;
    std::cout << sizeof(Person) << std::endl; // only with pragma we get the true value, not 64


    return 0;
}
