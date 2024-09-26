#include <algorithm>
#include <iomanip> 
#include <iostream>
#include <vector>
#include "writer.h"


void Writer::writeCSV(std::ofstream& fout, std::map<std::string, int> wordFrequency, int cntWords){

    fout << "Слово, Частота, Частота (%)\n";
    std::vector<std::pair<std::string, int>> listOfWordsToSort(wordFrequency.begin(), wordFrequency.end());

    std::sort(listOfWordsToSort.begin(), listOfWordsToSort.end(), [](auto& a, auto& b){return a.second > b.second;});

    for (std::pair<std::string, int> word : listOfWordsToSort){
        fout << word.first << "," << word.second << "," << std::fixed << std::setprecision(3) <<  (double)word.second/cntWords * PERCENT << "\n";
    }

    std::cout << "writing ends complitelly";
    return;
}