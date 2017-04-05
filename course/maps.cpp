#include <iostream>
#include <map>
#include <vector>
using namespace std;

// maps allow storing key-value-pairs
// like a lookup-table

int main()
{
    map<string, int> ages;
    ages["Mike"] = 40;
    ages["Raj"] = 20;
    ages["Vicky"] = 30;

    // Keys in the map are always unique.
    // Setting one again will overwrite old value
    ages["Mike"] = 42;

    // Using e.g. ages["Sue"] in cout when she's not in the map,
    // will add Sue with value 0 to the map

    cout << ages["Raj"] << endl;

    // check if some key in map: .find() method (without adding, as we like it)
    // .find returns iterator...
    // ...tp element if found
    // ...after last element if not found
    if(ages.find("Vicky")!=ages.end())
    {
        cout << "Found Vicky" << endl;
    }
    else
    {
        cout << "Key not found" << endl;
    }

    // looping again with iterators:
    for(map<string, int>::iterator it = ages.begin(); it!=ages.end(); ++it)
    {
        // access via (*it).first like key=first value=second in a struct
        cout << it->first << ": "<< it->second << endl;
    }

    // things in map are stored as pair, we now loop with it
    for(map<string, int>::iterator it = ages.begin(); it!=ages.end(); ++it)
    {
        pair<string, int> age = *it;
        cout << age.first << ": "<< age.second << endl;
    }
    cout << endl;

    // using pair we can also insert into the map:
    pair<string, int> addToMap("Peter", 100);
    ages.insert(addToMap);

    // Loop to check
    for(map<string, int>::iterator it = ages.begin(); it!=ages.end(); ++it)
        cout << it->first << ": "<< it->second << endl;
    cout << endl;

    // inserting also works this way
    ages.insert(pair<string, int>("Rob",22));

    // shortcut for this is make_pair function, that returns pair of right type
    ages.insert(make_pair("Monika", 33));

    // Loop to check
    for(map<string, int>::iterator it = ages.begin(); it!=ages.end(); ++it)
        cout << it->first << ": "<< it->second << endl;
    cout << endl;

// A map of vectors:
    map<string, vector<int> > scores;

    scores["Mike"].push_back(10); // first Score of mike is 10
    scores["Mike"].push_back(20); // second score of mike is 20
    scores["Vicky"].push_back(15); // first score of vicky is 15

    for(map<string, vector<int> >::iterator it = scores.begin(); it!=scores.end(); ++it)
    {
        cout << (*it).first << ": " << flush;
        for(vector<int>::iterator it2 = (*it).second.begin(); it2!=(*it).second.end(); ++it2)
        {
            cout << *it2 << " " << flush;
        }
        cout << endl;
    }

    return 0;
}
