#include <string>
#include <iostream>
using namespace std;

#include "siga.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    Siga siga("dataset.bin");
    siga.ImportCSVData(argv[1]);
    siga.SalvarListaOrdenadaEstudantes(argv[2]);

    return 0;

}
