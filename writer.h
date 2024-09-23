#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <map>
#include <string>


#define PROCENT 100

class Writer{
    public:
        void writeCSV(std::ofstream& fout, std::map<std::string, int> wordFrequency, int cntWords);

};

#endif