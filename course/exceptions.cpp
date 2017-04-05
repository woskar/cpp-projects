#include <iostream>
#include <exception>
using namespace std;

// Create custom error Class that inherits from exception
class MyException: public exception
{
public:
    // overwrite the what method
    virtual const char * what() const throw()
    {
        return "Something bad happened! MyException class what()";
    }
};

class Test
{
public:
    void goesWrong()
    {
        throw MyException();
    }
};

// Create Class that should throw bad_alloc error
class CanGoWrong
{
public:
    // Constructor
    CanGoWrong()
    {
        char * pMemory = new char[99999999999999999];
        delete[] pMemory;
    }
};


void mightGoWrong()
{
    bool error0 = false;
    bool error1 = false;
    bool error2 = false;
    bool error3 = true;
    bool error4 = true;

    if(error0)
        throw 8;

    if(error1)
        throw "Something 1 went wrong."; //throw string (char *)

    if(error2)
        throw string("Something 2 went wrong");

    if(error3)
        throw bad_alloc();

    if(error4)
        throw exception();
}

void usesMightGoWrong()
{
    mightGoWrong();
}

int main()
{
    //Test test;

    try
    {
        mightGoWrong();
        //usesMightGoWrong();
        //CanGoWrong wrong;
        //test.goesWrong();
    }

    // Subclasses of exceptions have to be caught before parent classes
    // otherwise separation is useless

    catch(bad_alloc &e)
    {
        cout << "Caught bad_alloc: " << e.what() << endl;
    }

    catch(MyException &e)
    {
        cout << e.what() << endl;
    }

    catch(exception &e)
    {
        cout << "Caught exception: " << e.what() << endl;
    }

    catch(int e)
    {
        cout << "Error code: " << e << endl;
    }

    catch(char const * e)
    {
        cout << "Error message: " << e << endl;
    }

    catch(string &e) //catching a (object) reference needed, because string() creates object
    {
        cout << "Error message: " << e << endl;
    }

    cout << "Still running." << endl;
    return 0;
}
