#include "app.h"
#include <iostream>

int App::openInputFile(const std::string& fileName){
    fin.open(fileName);
    if (fin.is_open()) return 1;

    else{
        std::cerr << "cant open input file" << std::endl;
        return 0;
    }
    
}

int App::openOutputFile(const std::string& fileName){
    fout.open(fileName);
    if (fout.is_open()) return 1;

    else{
        std::cerr << "cant open output file" << std::endl;
        fin.close();
        return 0;
    }
}

void App::closeStreams(){
    fin.close();
    fout.close();
}

int App::process(const std::string& fileIn, const std::string& fileOut){

    Reader reader;
    Counter counter;
    Writer writer;

    if (!App::openInputFile(fileIn)){
        return 1;
    }

    while (true){
        auto isNullOpt = reader.readStr(fin);
        if (!isNullOpt.has_value()){
            break;
        }
        std::string& str = isNullOpt.value();
        counter.addWords(str);
    }
    
    if(!App::openOutputFile(fileOut)){
        return 2;
    }

    writer.writeCSV(fout, counter.getFrequency(), counter.getCntWords());

    App::closeStreams();
    
    return 0;
}