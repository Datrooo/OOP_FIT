#include "app.h"
#include <iostream>

int main(int argc, char * argv[]){

    if (argc != 3){
        std::cerr << "bad input" << std::endl;
        return 1;
    }

    App proc;
    int result = proc.process(argv[1], argv[2]);

    return result;
}