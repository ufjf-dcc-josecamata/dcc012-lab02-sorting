#include <string>
#include <iostream>
using namespace std;

#include "siga.h"

int main(int argc, char *argv[])
{

    Siga siga("dataset.bin");
    siga.ImportCSVData("input/siga3000.csv");
    siga.SalvarListaOrdenadaEstudantes("output/test8.csv");

    return 0;

}
