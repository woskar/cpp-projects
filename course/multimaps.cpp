#include <iostream>
#include <map>
using namespace std;

// mulitmaps are maps with duplicate keys
// consider alternatives: maps of vecotors or custom types

int main()
{
    multimap<int, string> lookup;

    // create elements with insert, so like normal map
    // only difference: we can have key-duplicates (e.g. 30)
    lookup.insert(make_pair(30, "Mike"));
    lookup.insert(make_pair(10, "Mike"));
    lookup.insert(make_pair(30, "Raj"));
    lookup.insert(make_pair(20, "Sue"));

    for(multimap<int, string>::iterator it = lookup.begin();
        it != lookup.end(); it++)
    {
        cout << it->first << ": " << it->second << endl;
    }
    cout << endl;

    // find element in map:
    // problem here: when first element found,
    // outputs also all elements thereafter.
    for(multimap<int, string>::iterator it = lookup.find(20);
        it != lookup.end(); ++it)
    {
        cout << it->first << ": " << it->second << endl;
    }
    cout << endl;

    // so we want only to output the range where our key is found.
    // we create a pair of iterators (it's huge, but with c++11 we can just have auto there :D)
    // and we use equal_range() function, which we pass the key(s) we want to find
    pair<multimap<int, string>::iterator, multimap<int, string>::iterator> its = lookup.equal_range(30);
    // first element in pair: iterator pointing to first element with key
    // second element in pair: iterator pointing after the last element with key

    // now we can iterate from one iterator to the other in our pair its
    for(multimap<int, string>::iterator it = its.first; it != its.second; ++it)
    {
        cout << it->first << ": " << it->second << endl;
    }
    cout << endl;

    return 0;
}
