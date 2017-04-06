#include <iostream>
using namespace std;

// Casting

class Parent
{
public:
    virtual void speak(){cout << "parent!"<< endl;}
};

class Brother: public Parent
{};

class Sister: public Parent
{};

int main()
{
// Casting:
    float value = 3.23;
    cout << value << endl; // now we want to cast to integer:
    cout << (int)value << endl; // this notation comes from C
    cout << int(value) << endl; // this can be done in C++

// Static Cast:
    // more precisely defined types of casting:
    cout << static_cast<int>(value) << endl; //static cast

    Parent parent;
    Brother brother;

    //Thanks to polymorphism we can use a pointer or reference to a subclass
    //in any situation where we expect a pointer/ref to the superclass
    Parent *pp = &brother; //we expect to go to parent, but do go to brother

    //the other way around does not work out of the box
    //if you want to, you have to do a static_cast
    Brother *pb = static_cast<Brother *>(&parent);
    cout << pb << endl; //this works, is not safe though
                        //problems if brother has methods parent doesn't have
                        //there is no runtime-check on static_cast
                        //will just get your code to compile
                        //see dynamic cast for further info

    //Application for static_cast
    Parent *ppb = &brother;
    //Brother *pbb = ppb; // Brother points to a Brother but via a parent Pointer
    //as the above will not compile, we have to now have a static cast:
    Brother *pbb = static_cast<Brother *>(ppb);
    cout << pbb << endl;

    //Another use:
    Parent &&p = Parent(); //setting r-value-ref to r-value (need c++11)
    //Parent &&p = parent; //now r-value-ref to l-value does not work without cast
    Parent &&p2 = static_cast<Parent &&>(parent);
    p2.speak(); //this does now work with an r-value reference

// Dynamic Cast - is better to use than static cast
    // is a type of cast that checks at runtime if cast makes sense
    // will only work with runtime type information RTTI turned on in compiler
    Parent *ppb2 = &parent; //change it to &brother and dyn.c. will work
    Brother *pbb2 = dynamic_cast<Brother *>(ppb2);
    if(pbb2 == nullptr){cout << "Invalid cast" << endl;} //with &parent, downcast
    else cout << pbb2 <<endl; //valid when &brother, so upcast

// Reinterpret Cast - crazy type of cast ;)
    //parent is superclass of brother and sister, the latter being on same level
    Parent *parPoint = &brother;
    Sister *sisPoint = dynamic_cast<Sister *>(parPoint);
    //this returns a nullpointer by dynamic cast, because it's a stupid thing to do
    cout << sisPoint << endl;

    Sister *sisPoint2 = static_cast<Sister *>(parPoint); // does give valid address
    cout << sisPoint2 << endl; // does work, but is silly in most circumstances

    // Reinterpret cast does even less checking than static_cast
    Sister *sisPoint3 = reinterpret_cast<Sister *>(parPoint);
    cout << sisPoint3 << endl; //so here we get address, but doesn't make sense

    return 0;
}
