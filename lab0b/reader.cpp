#include "reader.h"

std::optional<std::string> Reader::readStr(std::ifstream& fin){
    std::string str;
    if(std::getline(fin, str)){
        return str;
    }
    return std::nullopt; 
}