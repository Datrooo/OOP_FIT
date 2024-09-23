#ifndef APP_H
#define APP_H

#include "readNcount.h"
#include "writer.h"

class App{
    private:
        ReaderNCounter readerNcounter;
        Writer writer;

    public:
        void process(std::ifstream& fin, std::ofstream& fout);
};

#endif