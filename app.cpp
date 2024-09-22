#include "app.h"

void App::process(std::ifstream& fin, std::ofstream& fout){
    readerNcounter.readNcountFrequency(fin);
    writer.writeCSV(fout, readerNcounter.getFrequency(), readerNcounter.getCntWords());
}