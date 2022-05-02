#include "siga.h"


int main(int argc, char *argv[])
{

    Siga siga("dataset.bin");
    siga.SalvarListaOrdendaEstudantesPorNome("output/test4.csv", SELECTIONSORT);

}