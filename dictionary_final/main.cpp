#include <iostream>
#include "Dictionary.h"
using namespace std;

int main()
{
    Dictionary dic;
    dic.loadDict("dictionary.txt");
    dic.addWord();
    dic.viewSpecific();
    dic.showPhon();
    dic.loadDict("dictionary.txt");
    return 0;
}
