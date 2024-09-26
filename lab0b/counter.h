#ifndef COUNTER_H
#define COUNTER_H

#include <map>
#include <string>

class Counter{
    private:
        std::map<std::string, int> wordFrequency;
        std::string fixWord(std::string str);
        int cntWords = 0;
        
    public:
        void addWords(std::string& str);
        int getCntWords();
        std::map<std::string, int> getFrequency();
    
};

#endif