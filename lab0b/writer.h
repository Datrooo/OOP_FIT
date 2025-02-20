#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <map>
#include <string>


#define PERCENT 100

class Writer{
    private:
        std::ofstream fout{nullptr};

    public:
        bool openOutputFile(const std::string& fileName);
        void closeOutputFile();
        void writeCSV(std::map<std::string, int> wordFrequency, int totalNumberOfWords);

};

#endif