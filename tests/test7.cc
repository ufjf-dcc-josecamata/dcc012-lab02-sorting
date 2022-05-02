#include "siga.h"


int main(int argc, char *argv[])
{

    Siga siga("dataset.bin");
    siga.SalvarListaOrdenadaEstudantes(argv[1]);

}

