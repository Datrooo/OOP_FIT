#include "counter.h"
#include <sstream>
#include <cctype>

std::string Counter::fixWord(std::string word){
    std::string fixed;
    for (char ch : word)
    {
        if (isalnum(ch)){
            fixed += std::tolower(ch);
        }
    }
    return fixed;
}


void Counter::addWords(std::string& str){
    std::istringstream strin(str);
    std::string word;

    while (strin >> word){
        word = fixWord(word);
        if (!word.empty()){
            wordFrequency[word]++;
            cntWords++;
        }
    }
    
}

int Counter::getCntWords(){
    return cntWords;
}

std::map<std::string, int> Counter::getFrequency(){
    return wordFrequency;
}