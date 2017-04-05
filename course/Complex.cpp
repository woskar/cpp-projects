#include <iostream>
#include "Complex.h"
using namespace std;

namespace oskar
{
// Free Functions
ostream & operator<<(ostream & out, const Complex & complex)
{
    out << "(" << complex.getReal() << ", " << complex.getImaginary() << ")";
    return out;
}

Complex operator+(const Complex & c1, const Complex & c2)
{
    return Complex(c1.getReal() + c2.getReal(),
                   c1.getImaginary() + c2.getImaginary());
}

Complex operator+(const Complex & c1, double d)
{
    return Complex(c1.getReal()+d, c1.getImaginary());
}

Complex operator+(double d, const Complex & c1)
{
    return Complex(c1.getReal()+d, c1.getImaginary());
}

// Member Functions
Complex::Complex(): real_(0), imaginary_(0){}

Complex::Complex(double real, double imag)
: real_(real), imaginary_(imag){}

Complex::Complex(const Complex &other)
: real_(other.real_), imaginary_(other.imaginary_){}

const Complex & Complex::operator=(const Complex & other)
{
    real_ = other.real_;
    imaginary_ = other.imaginary_;
    return *this;
}

bool Complex::operator==(const Complex & other) const
{
    return real_==other.real_ && imaginary_==other.imaginary_;
}

bool Complex::operator!=(const Complex & other) const
{
    //return real_!=other.real_ || imaginary_!=other.imaginary_;
    return !(*this == other);
}

Complex Complex::operator*() const
{
    return Complex(real_, -imaginary_);
}

} //namespace
