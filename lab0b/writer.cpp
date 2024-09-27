#include <algorithm>
#include <iomanip> 
#include <iostream>
#include <vector>
#include "writer.h"

bool Writer::openOutputFile(const std::string& fileName){
    fout.open(fileName);
    if (fout.is_open()) return true;

    else{
        std::cerr << "cant open output file" << std::endl;
        return false;
    }
}

void Writer::closeOutputFile(){
    fout.close();
}

void Writer::writeCSV(std::map<std::string, int> wordFrequency, int totalNumberOfWords){

    fout << "Слово, Частота, Частота (%)\n";
    std::vector<std::pair<std::string, int>> listOfWordsToSort(wordFrequency.begin(), wordFrequency.end());

    std::sort(listOfWordsToSort.begin(), listOfWordsToSort.end(), [](auto& a, auto& b){return a.second > b.second;});

    for (std::pair<std::string, int> word : listOfWordsToSort){
        fout << word.first << "," << word.second << "," << std::fixed << std::setprecision(3) <<  (double)word.second/totalNumberOfWords * PERCENT << "\n";
    }

    std::cout << "writing ends complitelly";
    return;
}