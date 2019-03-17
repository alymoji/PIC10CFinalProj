#ifndef Dictionary_h
#define Dictionary_h

#include <vector>
#include <string>

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
    }
    
    std::vector<std::string>entries;
    
    void addWord();
    void editWord();
    void viewSpecific() const;
    void showPhone();
    bool loadDict(const char * filename);
    
private:
    
};


#endif /* Dictionary_h */