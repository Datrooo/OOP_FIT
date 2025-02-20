#include "reader.h"
#include <iostream> 

bool Reader::openInputFile(const std::string& fileName){
    fin.open(fileName);
    if (fin.is_open()) return true;

    else{
        std::cerr << "cant open input file" << std::endl;
        return false;
    }
}

void Reader::closeInputFile(){
    fin.close();
}

std::optional<std::string> Reader::readStr(){
    std::string str;
    if(std::getline(fin, str)){
        return str;
    }
    return std::nullopt; 
}