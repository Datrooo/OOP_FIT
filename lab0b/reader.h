#ifndef READER_H
#define READER_H

#include <fstream>
#include <optional>
#include <string>

class Reader{
    public:
        std::optional<std::string> readStr(std::ifstream& fin);
};

#endif