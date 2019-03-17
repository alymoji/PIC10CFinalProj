#ifndef Dictionary_h
#define Dictionary_h

#include <vector>
#include <string>

class Dictionary
{
public:
    std::vector<std::string>entries;
    
    void addWord();
    void editWord();
    void viewSpecific() const;
    void showPhone();
    bool loadDict(const char * filename);
    
private:
    std::string word;
    std::string def;
    std::string part_of_speech;
    std::string phon;
};


#endif /* Dictionary_h */
