#ifndef APP_H
#define APP_H


#include "writer.h"
#include "reader.h"
#include "counter.h"

class App{
    private:
        std::ifstream fin{nullptr};
        std::ofstream fout{nullptr};
        int openInputFile(const std::string& fileName);
        int openOutputFile(const std::string& fileName);
        void closeStreams();

    public:
        int process(const std::string& fileIn, const std::string& fileOut);

};

#endif