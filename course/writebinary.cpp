#include <iostream>
#include <fstream>
using namespace std;

// Description:
// First struct Person is defined and set
// the struct gets written to binary File
// the we read again from binary File
// and write Information into new Person
// lastly output the information of the Person to screen

// use preprocessor directive to prevent padding, see in struct.cpp
#pragma pack(push, 1)

struct Person
{
    char name[50];
    int age;
    double height;
};

#pragma pack(pop)

int main()
{
    Person someone = {"Frodo", 42, 0.8};

    string fileName = "test.bin";

//////// Write binary file /////////////////

    ofstream outputFile; // create outputFile object
    outputFile.open(fileName, ios::binary);

    if(outputFile.is_open())
    {
        // we have a pointer to our data: &someone
        // first argument of .write() has to be char pointer
        // option A, old: (char*)&someone
        // option B, new: reinterpret_cast<char *>(&someone)
        outputFile.write(reinterpret_cast<char *>(&someone), sizeof(Person));
        outputFile.close();
    }
    else
    {
        cout << "Could not create file " + fileName;
    }

//////// Read binary file /////////////////

    Person someoneElse = {};
    ifstream inputFile; // create outputFile object
    inputFile.open(fileName, ios::binary);

    if(inputFile.is_open())
    {
        inputFile.read(reinterpret_cast<char *>(&someoneElse), sizeof(Person));
        inputFile.close();
    }
    else
    {
        cout << "Could not read file " + fileName;
    }

    cout << someoneElse.name << ", " << someoneElse.age << ", " << someoneElse.height << endl;

    return 0;
}
