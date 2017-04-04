#include <iostream>
#include <string>

using namespace std;

void changeSomething(double & value)
{
    value = 123.4;
}

void show1(const int nElements, string texts[])
{
    // we loose the size-information, because only pointer gets passed.
    // cout << sizeof(texts) << endl; //returns size of pointer
    for(int i=0; i<nElements; ++i)
    {
        cout << texts[i] << endl;
    }
}

// here we just pass the pointer, this is equivalent to shwo1!
void show2(const int nElements, string *texts)
{
    for(int i=0; i<nElements; ++i)
    {
        cout << texts[i] << endl;
    }
}

// pass reference to array of strings
void show3(string (&texts)[3])
{
    for(int i=0; i<sizeof(texts)/sizeof(string); ++i)
    {
        cout << texts[i] << endl;
    }
}


int main()
{
    int value1 = 8;
    int & value2 = value1;
    value2 = 10;
    cout << "Value1: " << value1 << endl;
    cout << "Value2: " << value2 << endl;

    double value = 5.432;
    changeSomething(value);
    cout << value << endl;

    string texts[] = {"apple", "orange", "banana"};
    cout << sizeof(texts) << endl;
    show1(3, texts);
    show2(3, texts);
    show3(texts);


    return 0;
}
