#include <iostream>
#include "Dictionary.h"
using namespace std;

int main()
{
    Dictionary dic;
    dic.loadDictFromFile();
    dic.addEntry();
    dic.editEntry();
    dic.viewSpecific();
    dic.showPhon();
    dic.writeDictToFile();
    return 0;
}
