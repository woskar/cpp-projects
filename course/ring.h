// Ring buffer:

// this buffer is used in the templates.cpp file.

/*
We want to have a circular buffer that overwrites itself after some iteration
possible application in multimedia program.

It should behave like this:
ring<string> textring(3);

textring.add("one");
textring.add("two");
textring.add("three");
textring.add("four"); //this should overwrite one in the ring

for(int i=0; i<textring.size(); i++)
    cout << textring.get(i) << endl;
// that should output four, two, three because one is overwritten

// we want to enable a range based for loop in our class
for(string value: textring)
    cout << value << endl;

// the range-based for-loop will work when iterator loop works:
for(ring<string>::iterator it=textring.begin(); it!=textring.end(); ++it)
    cout << *it << endl;

*/

#ifndef RING_H
#define RING_H

#include <iostream>
using namespace std;

template <class T>
class ring
{
private:
    int m_size;
    int m_position;
    T *m_values;
public:
    class iterator; // nesting it in here is to say that iterator is subtype of Ring
                    // we could implement here, but that's harder to read.
                    // the iterator class can't get the private ring variables
public:
    // Constructor
    ring(int size): m_size(size), m_position(0), m_values(NULL)
    {
        m_values = new T[size]; //we allocate memory here!
    }

    // Destructor to deallocate memory
    ~ring()
    {
        delete[] m_values;
    }

    // Implement size method to make it easier to loop through
    int size()
    {
        return m_size;
    }

    // add method to put elements in buffer
    void add(T element)
    {
        m_values[m_position++] = element; //increments position after storing element

        // Set position back to zero if it goes off the array
        if(m_position == m_size)
            m_position = 0;
    }

    // get method
    T & get(int index) // all STL classes return references
    {                  // note that the reference is invalid after removing the element
    // it's the users' responsiblity to check that index is not off the buffer
        return m_values[index];
    }

    // we need begin method to return an iterator on the first element for for-loop
    iterator begin()
    { // we pass the iterator an index and the object (reference),
      // because iterator itself can't touch the private member variables
        return iterator(0, *this); //start_index, object
    }

    // end method has to return iterator pointing after end of our ring
    iterator end()
    {
        return iterator(m_size, *this);
    }
};

template <class T>
class ring<T>::iterator //this is not a free-standing class, but belongs to Ring
{
private:
    int m_position;
    ring & m_ring; // make it a reference, we don't want to copy it

public:
    // Constructor that takes index and object reference as argument
    iterator(int pos, ring & aRing): m_position(pos), m_ring(aRing)
    {

    }

    // iterator has to be able to be incremented in loop
    // operator++() is the prefix type
    // operator++(int) is the postfix type, with useless first argument just to differentiate
    iterator & operator++(int) // postfix version
    {
        m_position++; // we increment the position count of our iterator object
        return *this; // and return the actual object
    }

    iterator & operator++() // prefix version
    {
        m_position++;
        return *this;
    }

    // we need to get the value the iterator refers to
    T & operator*()
    {   // get via get method, we don't have other access
        return m_ring.get(m_position);
    }

    // in loop there is also != on iterator
    bool operator==(const iterator & other) const
    {
        return (m_position == other.m_position);
    }

    bool operator!=(const iterator & other) const
    {
        return !(*this).operator==(other);
    }

    void print() //just a useless function for demonstration
    {
    cout << "Hello from iterator: " << T() << endl;
    }
};

/*
// we could even separate out functions
void ring::iterator::print()
{
cout << "Hello from iterator" << endl;
}
*/

#endif
