#include "app.h"
#include <iostream>

int main(int argc, char * argv[]){

    if (argc != 3){
        std::cerr << "bad input" << std::endl;
    }


    std::ifstream fin(argv[1]);    
    if (!fin.is_open()){
        std::cerr << "cant open input file" << std::endl;
        return 0;
    }
    std::ofstream fout(argv[2]);
    if (!fout.is_open()){
        std::cerr << "cant open output file" << std::endl;
        fin.close();
        return 0;
    }
    
    App proc;
    proc.process(fin, fout);
    fin.close();
    fout.close();
    return 0;
}