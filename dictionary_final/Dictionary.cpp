#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include "Dictionary.h"
using namespace std;


//Each line has to be in format
//output: word, part of speech, "definition"
bool Dictionary::loadDict(const char * filename)
{
    entries.clear(); //in case vector has entries beforehand
    ifstream fin(filename);
    if(!fin.is_open()) //check if file is open
    {
        cout << "File failed to open\n";
        return false;
    }
    
    string entry_line;
    while(getline(fin, entry_line, '\n')) //reading a line to add to vector
    {
        if(entry_line.empty())
            continue; //skip blank lines
        
        Entry next_entry;
        size_t position1 = entry_line.find_first_of(',', 0); //check word
        if(position1 == string::npos)
        {
            cout << "Bad file format\n";
            entries.clear();
            return false;
        }
        next_entry.word = entry_line.substr(0, position1);
        
        if(!is_valid_word(next_entry.word)) //check if the input is an actual word
        {
            cout << "Bad file format\n";
            entries.clear();
            return false;
        }
        to_Lower(next_entry.word);
        
        size_t position2 = entry_line.find_first_of(',', position1 + 1); //check part of speech
        if(position2 == string::npos)
        {
            cout << "Bad file format\n";
            entries.clear();
            return false;
        }
        string POSstr = entry_line.substr(position1 + 1, position2 - position1 - 1);
        to_Lower(POSstr);
        if(POSstr == "noun")
            next_entry.pos = NOUN;
        else if(POSstr == "adjective")
            next_entry.pos = ADJECIVE;
        else if(POSstr == "verb")
            next_entry.pos = VERB;
        else if(POSstr == "adverb")
            next_entry.pos = ADVERB;
        else if(POSstr == "preposition")
            next_entry.pos = PREPOSITION;
        else if(POSstr == "conjunction")
            next_entry.pos = CONJUNCTION;
        else if(POSstr == "interjection")
            next_entry.pos = INTERJECTION;
        else
        {
            cout << "Unrecognized part of speech\n";
            return false;
        }
        
        position1 = entry_line.find_first_of('"', position2 + 1); //check definiton
        if(position1 == string::npos)
        {
            cout << "Bad file format\n";
            entries.clear();
            return false;
        }
        position2 = entry_line.find_first_of('"', position1 + 1);
        if(position2 == string::npos)
        {
            cout << "Bad file format\n";
            entries.clear();
            return false;
        }
        next_entry.def = entry_line.substr(position1 + 1, position2 - position1 - 1);
        entries.push_back(next_entry); //why error
    }
    fin.close();
    sort(entries.begin(), entries.end()); //sort file
    return true;
}

void Dictionary::to_Lower(std::string &s) //make string lowercase
{
    for(size_t i =0; i < s.length(); ++i)
    {
        s[i] = tolower(s[i]);
    }
}

bool Dictionary::is_valid_word(std::string &word) //make sure word has no weird symbols 
{
    return string::npos == word.find_first_of(":;<>,.?/\"{}[]|\\=+_)(*&^%$#@!~`", 0);
}

//returns iterator into entries vector of first entry that comes after specified word
//returns iterator to end of entries vector if specified word comes after all words
vector<Dictionary::Entry>::const_iterator Dictionary::lookup_word(const std::string word) const
{
    Entry temp; //create temp to convert to lowercase so search isn't case sensitive
    temp.word = word;
    to_Lower(temp.word);
    return lower_bound(entries.begin(), entries.end(), temp);//binary search
}

//if entry has a word not in dict, entry is inserted into vector of Entry
void Dictionary::insertEntry(const Entry& entry)
{
    vector<Entry>::const_iterator it = lookup_word(entry.word);
    
    if(it->word == entry.word) //see if word is unique
    {
        cout << "Entry already exists\n";
        return; //if not, leave fn
    }
    entries.insert(it, entry);
}

