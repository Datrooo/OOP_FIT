#ifndef COUNTER_H
#define COUNTER_H

#include <map>
#include <string>

class Counter{
    private:
        std::map<std::string, int> wordFrequency;
        std::string fixWord(std::string str);
        int totalNumberOfWords = 0;
        
    public:
        void addWords(std::string& str);
        int getTotalNumberOfWords();
        std::map<std::string, int> getFrequency();
    
};

#endif