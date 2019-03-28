#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <algorithm>
#include "Dictionary.h"
using namespace std;

bool Dictionary::Entry::operator<(const Entry & E) const
{
    return this->word < E.word;
}

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
            next_entry.pos = ADJECTIVE;
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
            entries.clear();
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
        entries.push_back(next_entry);
    }
    fin.close();
    sort(entries.begin(), entries.end()); //sort file
    return true;
}

//Enters vector entries in text file accordingly
//Rewrites the file
bool Dictionary::writeDictToFile() const
{
    string filename;
    //it will override the file so best to show a message
    cout << "Warning: Writing a dictionary to a file will overwrite anything in the current file.\n";
    cout << "Input file name (or '\\' to cancel): ";
    getline(cin, filename, '\n');
    if(filename == "\\")
        return false;
    
    ofstream fout;
    fout.open(filename);
    
    if(!fout.is_open())
    {
        cout << "File failed to open\n";
        return false;
    }
    
    for(size_t i = 0; i < entries.size(); i++) //use size_t as it relates to the file, not the vector
    {
        fout << entries[i].word;
        switch(entries[i].pos)
        {
            case NOUN:         fout << ",NOUN,";         break;
            case VERB:         fout << ",VERB,";         break;
            case ADJECTIVE:    fout << ",ADJECTIVE,";    break;
            case ADVERB:       fout << ",ADVERB,";       break;
            case PREPOSITION:  fout << ",PREPOSITION,";  break;
            case CONJUNCTION:  fout << ",CONJUNCTION,";  break;
            case INTERJECTION: fout << ",INTERJECTION,"; break;
        }
        fout << '"' << entries[i].def << '"' << "\n";
    }
    fout.close();
    return true;
}



//Recieves info from user and then adds the entry to the dictionary alphabetically
void Dictionary::addEntry()
{
    Entry new_entry;
    //Get word
    do
    {
        cout << "Input Word (or '\\' to cancel): ";
        getline(cin, new_entry.word, '\n');
        if(new_entry.word == "\\" || is_valid_word(new_entry.word))
            break;
        cout << "That is not a valid word.\n";
    } while(true);
        
    if(new_entry.word == "\\")
        return;
    
    //Get definition
    cout << "Input meaning (or '\\' to cancel): ";
    getline(cin, new_entry.def, '\n');
    
    if(new_entry.def == "\\")
        return;
    
    //Get part of speech
    do
    {
        cout << "Input part of speech.\n";
        cout << "1: NOUN\n";
        cout << "2: ADJECTIVE\n";
        cout << "3: VERB\n";
        cout << "4: ADVERB\n";
        cout << "5: PREPOSITION\n";
        cout << "6: CONJUNCTION\n";
        cout << "8: INTERJECTION\n";
        
        int pos;
        if(!(cin >> pos)) //cant take a size_t, only int
        {
            cout << "That is not a part of speech. Enter one of the numbers above.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch(pos)
        {
            case 1:    new_entry.pos = NOUN; break;
            case 2:    new_entry.pos = ADJECTIVE; break;
            case 3:    new_entry.pos = VERB; break;
            case 4:    new_entry.pos = ADVERB; break;
            case 5:    new_entry.pos = PREPOSITION; break;
            case 7:    new_entry.pos = CONJUNCTION; break;
            case 8:    new_entry.pos = INTERJECTION; break;
            default: cout << "That is not a part of speech. Enter one of the numbers above." << endl; continue;
        }
        break;
    } while(true);
    
    insertEntry(new_entry);
}

void Dictionary::editEntry()
{
    string word;
    vector<Entry>::iterator entry_to_edit;
    
    do
    {
        cout << "Input Word (or '\\' to cancel): ";
        getline(cin, word, '\n');
        if(word == "\\")
            return;
        
        entry_to_edit = lookup_word(word);
        
        if(entry_to_edit == entries.end() || entry_to_edit->word != word)
        {
            cout << "That word is not in the dictionary.\n";
        }
        else
            break;
    }while(true);
    
    int ans = -1;
    do
    {
        cout << "Would you like to: \n1. Edit spelling of word\n2.Edit definition of word.\n";
        if(!(cin >> ans) || ans < 1 || ans > 2) // goes through the first scenario so it'll read the input
        {
            cout << "That's not a valid choice. Enter one of the numbers above.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
            break;
    }while(true);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if(ans == 1) //edit spelling
    {
        string spell;
        do
        {
            cout << "Input new spelling (or '\\' to cancel): ";
            getline(cin, spell, '\n');
            if(spell == "\\")
                return;
            if(is_valid_word(spell))
                break;
            cout << "That is not a valid word.\n";
        }while(true);
        
        entry_to_edit->word = spell;
    }
    else if(ans == 2) //edit definition
    {
        string definition;
        cout << "Input nre definition (or '\\' to cancel): ";
        getline(cin, definition, '\n');
        if(definition == "\\")
            return;
        entry_to_edit->def = definition;
    }
    sort(entries.begin(), entries.end());
}

void Dictionary::viewSpecific() const
{
    /*
     1. ask user for work to search
     2. search for word in vector
     3. if it's not in vector, say that word doesn't exist
     4. if it's in the vector, output the line
     */
    
    if(entries.empty())
    {
        cout << "There are no entries in the dictionary.\n";
        return;
    }
    
    string user_word;
    
    cout << "Input Word (of '\\' to cancel): ";
    cin >> user_word;
    
    if(user_word == "\\")
        return;
    to_Lower(user_word);
    
    vector<Entry>::const_iterator it = lookup_word(user_word);
    if(it == entries.end() || it->word != user_word)
    {
        cout << "Word does not exist\n";
        return;
    }
    else
    {
        cout << "Word: " << it->word << "\n";
        cout << "Part of Speech: ";
        switch(it->pos)
        {
            case NOUN:         cout << "NOUN";
            case ADJECTIVE:    cout << "ADJECTIVE";
            case VERB:         cout << "VERB";
            case ADVERB:       cout << "ADVERB";
            case PREPOSITION:  cout << "PREPOSITION";
            case CONJUNCTION:  cout << "CONJUNCTION";
            case INTERJECTION: cout << "INTERJECTION";
        }
        cout << "\nDefinition: " << it->def << "\n";
    }
}

//make string lowercase
void Dictionary::to_Lower(std::string &s)
{
    for(size_t i =0; i < s.length(); ++i)
    {
        s[i] = tolower(s[i]);
    }
}

//make sure word has no weird symbols
bool Dictionary::is_valid_word(std::string &word)
{
    return string::npos == word.find_first_of(":;<>,.?/\"{}[]|\\=+_)(*&^%$#@!~`", 0);
}

//returns iterator into entries vector of first entry that comes after specified word
//returns iterator to end of entries vector if specified word comes after all words
vector<Dictionary::Entry>::const_iterator Dictionary::lookup_word(const std::string word) const
{
    //Create a temporary Entry for search to make entry lowercase
    Entry temp;
    temp.word = word;
    to_Lower(temp.word);
    vector<Dictionary::Entry>::const_iterator it = lower_bound(entries.begin(), entries.end(), temp); //binary search
    if(it != entries.begin() && (it - 1)->word == word)
    {
        return it - 1;
    }
    return it;
}

//returns iterator into entries vector of first entry that comes after specified word
//returns iterator to end of entries vector if specified word comes after all words
vector<Dictionary::Entry>::iterator Dictionary::lookup_word(const std::string word)
{
    //Create a temporary Entry for search to make entry lowercase
    Entry temp;
    temp.word = word;
    to_Lower(temp.word);
    vector<Dictionary::Entry>::iterator it = lower_bound(entries.begin(), entries.end(), temp); //binary search
    if(it != entries.begin() && (it - 1)->word == word)
    {
        return it - 1;
    }
    return it;
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

