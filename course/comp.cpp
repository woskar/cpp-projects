#include <iostream>
#include "Complex.h"
using namespace oskar;

int main()
{
    Complex number;
    Complex c1(2,3);
    Complex c2 = c1;
    Complex c3;
    c3 = c2;
    Complex c4(4,7);

    cout << c1 << endl;
    cout << c2 << endl;
    cout << c3 << endl;
    cout << c4 << endl;
    cout << c1+c4 << endl;
    cout << *c4 << endl;
    cout << c2 + *Complex(2,1) << endl;
    return 0;
}
