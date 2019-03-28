#include <iostream>
#include <fstream>
#include "Dictionary.h"
using namespace std;

int main()
{
    Dictionary dic;
    while(true)
    {
        int i;
        cout << "\nPress 1 to view specific word\n";
        cout << "Press 2 to add word manually\n";
        cout << "Press 3 to edit definiton of word\n";
        cout << "Press 4 to show phonetic transcription of word in dictionary\n";
        cout << "Press 5 to load words from a file\n";
        cout << "Press 6 to export the dictionary to a file\n";
        cout << "Press 7 to exit\n";
        cout << "Input: ";
        if (!(cin >> i))
        {
            cout << "Invalid entry. Enter one of the numbers above." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(i)
        {
            case 1:    dic.viewSpecific();       break;
            case 2:    dic.addEntry();           break;
            case 3:    dic.editEntry();          break;
            case 4:    /*dic.showPhon();*/       break;
            case 5:    dic.loadDictFromFile();   break;
            case 6:    dic.writeDictToFile();    break;
            case 7:    return 0;
            default: cout << "Invalid entry. Enter one of the numbers above." << endl;
        }
        cout << "\n";
    }
    return 0;
}
