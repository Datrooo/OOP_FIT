#ifndef READNCOUNTER_H
#define READNCOUNTER_H

#include <map>
#include <string>

class ReaderNCounter{
    private:
        std::map<std::string, int> wordFrequency;
        std::string fixWord(std::string str);
        int cntWords = 0;
    public:
        void readNcountFrequency(std::ifstream& fin);
        std::map<std::string, int> getFrequency();
        int getCntWords();
};



#endif