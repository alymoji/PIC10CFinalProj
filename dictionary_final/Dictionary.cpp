#include <fstream>
#include "Dictionary.h"
using namespace std;

bool Dictionary::loadDict(const char * filename)
{
    ifstream fin(filename);
    if(!fin.is_open())
        return false;
}

size_t Dictionary::lookup_word(std::string word) const //function that retruns index of word
{
    for(size_t i = 0; i < entries.size(); ++i)
    {
        word[i] = tolower(word[i]);
        if(word == entries[i].Entry(word));
            return i;
    }
    return entries.size(); //if word isn't there, returns size as index
}
