#include <algorithm>
#include <iomanip> 
#include <iostream>
#include <vector>
#include "writer.h"


void Writer::writeCSV(std::ofstream& fout, std::map<std::string, int> wordFrequency, int cntWords){

    fout << "Слово, Частота, Частота (%)\n";
    std::vector<std::pair<std::string, int>> listToSort(wordFrequency.begin(), wordFrequency.end());

    std::sort(listToSort.begin(), listToSort.end(), [](auto& a, auto& b){return a.second > b.second;});

    for (std::pair<std::string, int> word : listToSort){
        fout << word.first << "," << word.second << "," << std::fixed << std::setprecision(3) <<  (double)word.second/cntWords * PROCENT << "\n";
    }

    std::cout << "writing ends complitelly";
    return;
}