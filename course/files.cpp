#include <iostream>
#include <fstream>
using namespace std;

int main()
{
// Writing to a File:
    // create Object of Type ofstream
    //ofstream outFile; //option A
    fstream outFile; //option B, more general

    // save Filename in variable
    string outputFileName = "text.txt";

    // open a new File
    //outFile.open(outputFileName); //option A
    outFile.open(outputFileName, ios::out); //option B

    if(outFile.is_open())
    {
        outFile << "Hello there" << endl;
        outFile << 1234;
        outFile.close();
    }
    else // file is not open
    {
        cout << "Could not create file: " << endl;
    }

// Reading from a File:
    string inFileName = "readTest.txt";
    ifstream inFile;
    inFile.open(inFileName);

    // alternatively, create general Object
    //fstream inFile;
    //inFile.open(inFileName, ios::in)

    if(inFile.is_open())
    {
        string line;

        //while(!inFile.eof()) //eof is end of file
        while(inFile) //short version of the above (overloaded Bool operator)
        {
            // get Line reads a whole line
            getline(inFile, line);
            cout << line << endl;
        }
        inFile.close();
    }
    else // file is not open
    {
        cout << "Could not create file: " << endl;
    }

// Read special formatted text:
    string inputName = "table.txt";
    ifstream input;
    input.open(inputName);
    if(!input.is_open())
        return 1;
    while(input)
    {
        string line;
        getline(input, line, ':');
        int number;
        input >> number;
        input.get(); //to get rid of the \n character

        cout << "'" << line<< "'" << "--" << number << endl;
    }
    input.close();

    return 0;
}
