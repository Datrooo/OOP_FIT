#ifndef READER_H
#define READER_H

#include <fstream>
#include <optional>
#include <string>

class Reader{
    private:
        std::ifstream fin{nullptr};

    public:
        bool openInputFile(const std::string& fileName);
        void closeInputFile();
        std::optional<std::string> readStr();
};

#endif