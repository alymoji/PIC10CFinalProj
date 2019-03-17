#ifndef Dictionary_h
#define Dictionary_h

#include <vector>
#include <string>
#include <cstddef>

class Dictionary
{
public:
    
    enum PART_OF_SPEECH {NOUN, ADJECIVE, VERB, ADVERB, PREPOSITION, CONJUNCTION, INTERJECTION};
    
    struct Entry
    {
        std::string word;
        std::string def;
        std::string pos;
        std::string phon;
    };
    
    std::vector<std::string>entries;
    
    void addWord();
    void editWord();
    void viewSpecific() const;
    void showPhone();
    bool loadDict(const char * filename); // see if file successfully opened
    
private:
    static void to_Lower(std::string& s); // auto lowercase for lookup function
    size_t lookup_word(std::string word) const; // look ups word in vector
};


#endif /* Dictionary_h */
