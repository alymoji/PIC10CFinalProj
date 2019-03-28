#ifndef Dictionary_h
#define Dictionary_h

#include <vector>
#include <string>
#include <cstddef>

class Dictionary
{
public:
    
    enum PART_OF_SPEECH {NOUN = 1, ADJECTIVE, VERB, ADVERB, PREPOSITION, CONJUNCTION, INTERJECTION};
    
    struct Entry
    {
        std::string word;
        std::string def;
        PART_OF_SPEECH pos;
        std::string phon;
        
        bool operator < (const Entry&) const;
    };
    
    void addEntry();
    void editEntry();
    void viewSpecific() const;
    void showPhon();
    bool loadDict(const char * filename); // see if file successfully opened
    
private:
    std::vector<Entry>                 entries;
    
    static void                        to_Lower(std::string& s); // auto lowercase for lookup function
    static bool                        is_valid_word(std::string& word); //check if it's a word
    
    std::vector<Entry>::const_iterator lookup_word(const std::string word) const; // look ups word in vector
    std::vector<Entry>::iterator       lookup_word(const std::string word);
    void                               insertEntry(const Entry& entry);
};


#endif /* Dictionary_h */
