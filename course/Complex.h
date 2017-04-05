#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

namespace oskar{

class Complex
{
private:
    double real_;
    double imaginary_;

public:
    Complex();
    Complex(double real, double imag);
    Complex(const Complex &other);

    const Complex & operator=(const Complex & other);
    double getReal() const {return real_;}
    double getImaginary() const {return imaginary_;}
    bool operator==(const Complex & other) const;
    bool operator!=(const Complex & other) const;
    Complex operator*() const; //we want star to give conjugate
};

ostream & operator<<(ostream & out, const Complex & complex);
Complex operator+(const Complex & c1, const Complex & c2);
Complex operator+(const Complex & c1, double d);
Complex operator+(double d, const Complex & c1);

} // namespace oskar
#endif
