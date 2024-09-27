#ifndef APP_H
#define APP_H


#include "writer.h"
#include "reader.h"
#include "counter.h"

class App{
    public:
        int process(const std::string& fileIn, const std::string& fileOut);

};

#endif