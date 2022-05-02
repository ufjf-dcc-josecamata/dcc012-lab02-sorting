#include "siga.h"


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <output_file>" << endl;
        return 1;
    }
    Siga siga("dataset.bin");
    siga.SalvarListaOrdendaEstudantesPorNome(argv[1], INSERTIONSORT);
    return 0;

}