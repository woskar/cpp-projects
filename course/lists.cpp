#include <iostream>
#include <list>
using namespace std;

// list items can be inserted in middle
// contains of nodes linked by pointers

int main()
{
    list<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    // additionally we've got push_front for lists
    numbers.push_front(0);

    // add items in the middle via an iterator
    list<int>::iterator it = numbers.begin();
    it++;
    cout << "Iterator on: " << *it << endl; //iterator is on the 1
    numbers.insert(it, 100);
    // insert goes at position of iterator,
    // rest of list gets "shifted" by one
    cout << "Element: " << *it << endl; // iterator again at 1, so got incremented

    // for looping we have to use an iterator
    for(list<int>::iterator it=numbers.begin(); it!=numbers.end(); ++it)
    {
        cout << *it << endl;
    }

    // delete element with iterator as well
    list<int>::iterator eraseIt = numbers.begin();
    eraseIt++;
    cout << "Erase Iterator on: " << *eraseIt << endl;
    eraseIt = numbers.erase(eraseIt);
    cout << "Erase Iterator now on: " << *eraseIt << endl;
    // output loop
    for(list<int>::iterator it=numbers.begin(); it!=numbers.end(); ++it)
        cout << *it << endl;
    cout << endl;

    // iterate over list and delete elements at the same time:
    for(list<int>::iterator it = numbers.begin(); it!=numbers.end(); )//no incrementation here, se below
    {
        // inserting elements is no problem
        if(*it == 2)
        {
            numbers.insert(it, 1234);
        }

        // deleting
        if(*it == 1)
        {
            // as erasing invalidates the iterator,
            // we have to set it again via =
            it = numbers.erase(it);
            // this will increment the iterator
            // therefore the loop should increment only if there is no erase
        }
        else // when no element erased during one loop, increment iterator
        {
            ++it;
        }

    }

    // output loop
    for(list<int>::iterator it=numbers.begin(); it!=numbers.end(); ++it)
        cout << *it << endl;

    return 0;
}
