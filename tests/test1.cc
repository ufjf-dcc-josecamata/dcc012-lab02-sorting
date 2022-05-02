
#include <string>
#include <iostream>
using namespace std;

#include "siga.h"


int main(int argc, char *argv[])
{
    Siga siga("dataset.bin");
    siga.ImportCSVData("input/siga1000.csv");
    return 0;

}





