#include "siga.h"


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    Siga siga("dataset.bin");
    siga.ImportCSVData(argv[1]);
    return 0;

}
