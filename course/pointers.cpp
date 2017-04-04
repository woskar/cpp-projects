#include <iostream>
#include <string>
using namespace std;

void manipulate(double value)
{
    value = 10.1;
    cout << "Value of double in manipulate: " << value << endl;
}

void pointer_manipulate(double *pValue)
{
    *pValue = 10.1;
    cout << "Value of double in pointer_manipulate: " << *pValue << endl;
}


int main()
{
    std::cout << "Starting program" << std::endl;

    int nValue = 8;
    int* pnValue = &nValue;


    std::cout << "Int value: "<< nValue <<std::endl;
    std::cout << "Pointer to int adress: "<< pnValue <<std::endl;
    std::cout << "Value of Pointer: "<< *pnValue <<std::endl;

    double dValue = 123.456;
    cout << "1.dValue: " << dValue << endl;
    manipulate(dValue);
    cout << "2.dValue: " << dValue << endl;
    pointer_manipulate(&dValue);
    cout << "3.dValue: " << dValue << endl;


    std::string texts[] = {"one", "two", "three"};
    std::cout << sizeof(texts)/sizeof(string) << std::endl;

    for(int i=0; i<3; ++i)
    {
        cout << texts[i] << " " << flush;
    }
    std::cout << std::endl;

    // create Pointer
    std::string * pTexts = texts;

    // iterate with a pointer, array element reference syntax
    for(int i=0; i<3; ++i)
    {
        cout << pTexts[i] << " " << flush;
    }
    std::cout << std::endl;

    // iterate with a pointer second version, incrementing pointer
    for(int i=0; i<3; ++i)
    {
        cout << *pTexts << " " << flush;
        pTexts++;
    }
    std::cout << std::endl;


    // iterate with a pointer third version, increment pointer
    std::string * pTexts2 = texts;
    for(int i=0; i<3; ++i, pTexts2++) // more things can be incremented
    {
        cout << *pTexts2 << " " << flush;
    }
    std::cout << std::endl;

    // iterate with a pointer forth version
    string *pElement = texts; //texts is identical to &texts[0]
    string *pEnd = &(texts[2]); //works without brackets as well, because of precedence

    while(true)
    {
        cout << *pElement << " " << flush;
        if(pElement == pEnd)
        {
            break;
            cout << "after break" << std::endl; //does not get printed
        }
        pElement++;
    }
    std::cout << std::endl;


    std::cout << "Ending program" << std::endl;

        const int ELEMENTS = 5;
    string words[ELEMENTS] = {"a", "b", "c", "d", "e"};
    string *pWords = words;
    cout << *pWords << endl;
    pWords += 3;
    cout << *pWords << endl;
    pWords -= 2;
    cout << *pWords << endl;

    string *pEndWords = &words[ELEMENTS];
    pWords = &words[0];


    while(pWords != pEndWords)
    {
        cout << *pWords << endl;
        pWords++;
    }

    //set pointer back to Start
    pWords = &words[0];

    int elements = pEndWords - pWords;
    cout << elements << endl;

    //set pointer again back to Start
    pWords = &words[0];
    pWords += ELEMENTS/2;
    //get to middle of array
    cout << *pWords << endl;

    // char arrays:
    char text[] = {'h', 'e', 'l', 'l', 'o'};
    cout << text << endl;
    // this is really the same as:
    char text2[] = "hello";
    cout << text2 << endl;

    for(int i=0; i<sizeof(text); i++)
    {
        cout << i << ": " << text[i] << " " << (int)(text[i]) << endl;
    }

    for(int i=0; i<sizeof(text2); i++)
    {
        cout << i << ": " << text2[i] << " " << (int)(text2[i])<< endl;
        // note: the string has the Null-String-Terminator!
        // the "" append the \0!
    }

    string text3 = "hello";
    cout << text3 << endl;
    int i = 0;
    int j = text3.length()-1;
    while(i < j)
    {
        char temp;
        temp = text3[i];
        text3[i] = text3[j];
        text3[j] = temp;
        i++;
        j--;
    }
    cout << text3 << endl;

    char text4[] = "hello";
    int nChars = sizeof(text4)-1;
    char* pStart = text4;
    char* pEndHere = text4 + nChars -1;
    cout << *pEndHere << endl;

    while(pStart < pEndHere)
    {
        char save = *pStart;
        *pStart = *pEndHere;
        *pEndHere = save;

        pStart++;
        pEndHere--;
    }
    cout << text4 << endl;

    int value3 = 3;
    int value4 = 4;

    cout << value3 << endl;
    cout << value4 << endl;
    cout << &value3 << endl;
    cout << &value4 << endl;

    int* pointer = &value3;
    cout << pointer << endl;
    cout << *pointer << endl;

    pointer = &value4;
    cout << pointer << endl;
    cout << *pointer << endl;

    *pointer = 42;
    cout << pointer << endl;
    cout << *pointer << endl;

    cout << value3 << endl;
    cout << value4 << endl;

    const int value5 = 5;

    const int * pointer5 = &value5;
    // value of pointee cant be changed
    // *pointer5 = 1;

    int * const pointer6 = &value4;
    // now we have constant pointer
    // so pointer cant point to something else
    //pointer6 = &value3;


    return 0;
}
