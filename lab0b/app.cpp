#include "app.h"
#include <iostream>

int App::process(const std::string& fileIn, const std::string& fileOut){

    Reader reader;
    Counter counter;
    Writer writer;

    if (!reader.openInputFile(fileIn)){
        return 1;
    }

    while (true){
        auto isNullOpt = reader.readStr();
        if (!isNullOpt.has_value()){
            break;
        }
        std::string& str = isNullOpt.value();
        counter.addWords(str);
    }

    reader.closeInputFile();
    
    if(!writer.openOutputFile(fileOut)){
        return 2;
    }

    writer.writeCSV(counter.getFrequency(), counter.getTotalNumberOfWords());

    writer.closeOutputFile();
    
    return 0;
}