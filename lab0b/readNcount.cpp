#include <cctype>
#include <fstream>
#include "readNcount.h"
#include <sstream>


std::string ReaderNCounter::fixWord(std::string word){
    std::string fixed;
    for (char ch : word)
    {
        if (isalnum(ch)) {fixed += std::tolower(ch);}
    }
    return fixed;
}


void ReaderNCounter::readNcountFrequency(std::ifstream& fin){
    std::string str;
    while(std::getline(fin, str)){
        std::istringstream strin(str);
        std::string word;

        while(strin >> word){
            word = fixWord(word);
            if(!word.empty()){
                wordFrequency[word]++;
                cntWords++;
            }
        }
    }
}

std::map<std::string, int> ReaderNCounter::getFrequency(){
    return wordFrequency;
}

int ReaderNCounter::getCntWords(){
    return cntWords;
}