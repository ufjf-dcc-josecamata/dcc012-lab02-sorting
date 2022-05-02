#include "siga.h"


int main(int argc, char *argv[])
{

    Siga siga("dataset.bin");
    siga.ImportCSVData("input/siga2000.csv");

}
