#ifndef SIGA_H__
#define SIGA_H__

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "config.h"
#include "estudante.h"

class Siga
{
    typedef enum {BUBBLESORT, INSERTIONSORT, SELECTIONSORT } sorting_method;
    public:
        Siga(string arquivo_estudante);
        void CadastraEstudante(Estudante est);
        int  PesquisaPorMatricula(int matricula);
        void ImprimeEstudantePorMatricula(int matricula);
        void AlteraCadastroEstudante(Estudante est);
        void SalvaListaEstudanteEmTexto(string arquivo_txt);
        int  ObterNumeroEstudantesArmazenados();

        // TODO: Ordenação de Dados
        void ImportCSVData(string arquivo_csv);
        void SalvarListaOrdendaEstudantesPorNome(std::string arquivo_txt, sorting_method method);
        void SalvarListaOrdenadaEstudantesPorIRAPorCurso(std::string arquivo_txt, sorting_method method);
        ~Siga();
    private:
        // atributos
        string   arquivo_nome;
        fstream  file_stream;
        int      n_estudantes;
};


#endif /* SIGA_H__ */
