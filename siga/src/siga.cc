#include <string>

using namespace std;

#include "siga.h"
#include "sort.h"


Siga::Siga(string arquivo_dados_estudante)
{

    this->arquivo_nome = arquivo_dados_estudante;
    this->file_stream.open(this->arquivo_nome, ios::in | ios::out | ios::binary );

    if(this->file_stream.is_open())
    {
        cout << "SIGA: Inicializado com sucesso" << endl;
    }
    else
    {
        cout << "SIGA: Erro ao abrir arquivo" << endl;
        return; 
    }

    cout << this->ObterNumeroEstudantesArmazenados() << " registros de estudantes" << endl;
}


int  Siga::PesquisaPorMatricula(int matricula)
{
    //Posicionando o cursor no inicio do arquivo
    this->file_stream.seekg(0, this->file_stream.beg);

    //Declarando Estudante
    Estudante est = Estudante();

    for ( int i = 0; i < this->n_estudantes; i++){
        //Ler do arquivo binário
        est.LerDoArquivoBinario(this->file_stream);
        //Verifica se a matricula é a mesma
        if ( est.ObterMatricula() == matricula )
            return i;
    }

    //Retornando o cursor pro fim de leitura
    this->file_stream.seekg(0, this->file_stream.end);

    //Caso não encontrar a matrícula retorna -1
    return -1;
}
        
void Siga::CadastraEstudante(Estudante est)
{
    //Verifica se est já está cadastrado
    if( PesquisaPorMatricula(est.ObterMatricula() ) != -1 )
        return;

    //Colocando o Cursor no Fim
    this->file_stream.seekp(0, this->file_stream.end);

    //Adicionando o aluno
    est.EscreverNoArquivoBinario(this->file_stream);

    //Incrementando o número de estudantes
    this->n_estudantes = this->n_estudantes + 1;

}
        
void Siga::ImprimeEstudantePorMatricula(int matricula)
{
    int index = PesquisaPorMatricula(matricula);
    if( index == -1){
        cout << "Estudante não cadastrado" << endl;
    } else {
        this->file_stream.seekg((index * ESTUDANTE_SIZE), this->file_stream.beg );
        Estudante est = Estudante();

        est.LerDoArquivoBinario(this->file_stream);

        est.Imprimir();
    }
}
        
void Siga::SalvaListaEstudanteEmTexto(string arquivo_txt)
{
    //Cursor no inicio
    this->file_stream.seekg(0, this->file_stream.beg);

    //Verifica se o arquivo está vazio
    if(this->n_estudantes == 0)
        return;

    //Abre o arquivo
    fstream arq;
    arq.open(arquivo_txt, ios::in | ios::out | ios::trunc);
    if(!arq.is_open()){
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    //Cria um vetor de alunos
    Estudante estudante;
        
    //Salva a primeira linha
    arq << "Matricula;Nome;Ano de Ingresso;Curso;IRA" << endl;

    //Le o vetor de Estudantes
    for( int i = 0; i < this->n_estudantes; i++){
        estudante.LerDoArquivoBinario(this->file_stream);
        arq << estudante.ObterMatricula() << ";";
        arq << estudante.ObterNome() << ";";
        arq << estudante.ObterAnoIngresso() << ";";
        arq << estudante.ObterCurso() << ";";
        arq << estudante.ObterIRA() << endl;

    }

    //Fechando o arquivo
    arq.close();


}
        
        
void Siga::AlteraCadastroEstudante(Estudante est)
{
    //Pesquisa o aluno
    int index = PesquisaPorMatricula( est.ObterMatricula() );

    //Caso nao encontrado imprime e retorna
    if ( index == -1 ){
        cout << "Estudante não cadastrado" << endl;
        return;
    }

    //Coloca o cursor no estudante que será reescrito
    this->file_stream.seekp(index * ESTUDANTE_SIZE, this->file_stream.beg);

    //Reescreve os dados dele
    est.EscreverNoArquivoBinario(this->file_stream);

    cout << "Dados Alterados" << endl;
}
        
Siga::~Siga()
{
    this->file_stream.close();
}

int Siga::ObterNumeroEstudantesArmazenados()
{
    if ( this->file_stream.is_open() ){
        this->file_stream.seekg(0, this->file_stream.end);
        int length = this->file_stream.tellg();
        this->file_stream.seekg(0, this->file_stream.beg);

        this->n_estudantes = length / ESTUDANTE_SIZE;

        return this->n_estudantes;
    }else {
        return 0;
    }
}


void Siga::ImportCSVData(string file)
{
    cout << "Importando dados do arquivo " << file << endl;
    int n_importados = 0; 

    // TODO: 
    // Abra um arquivo .csv com a seguinte formatação:
    // Matricula;Nome;Ano de Ingresso;Curso;IRA
    // Para cada linha do arquivo, criar um objeto Estudante e escrever no arquivo binário.

    // Atualize o numero de registros no binário.
    // Imprima o numero de estudantes importados:
    cout << "Importacao concluida: " << n_importados << " novos alunos cadastrados" << endl;
     
    
}

void Siga::SalvarListaOrdendaEstudantesPorNome(string arquivo_txt, sorting_method method)
{
    // Iremos aplicar a ordenação na memoria, para isso faca:
    // 1. Ler todos os dados do arquivo binário colocandos em um vetor
    // 2. Ordenar o vetor usando o metodo de ordenação escolhido:
    //    - Ordenar por nome
    switch(method){
        case BUBBLESORT:
            // Ordenação por nome
            break;
        case INSERTIONSORT:
            // Ordenação por nome
            break;
        case SELECTIONSORT:
            // Ordenação por nome
            break;
        default:
           cout << "metodo de ordenação não encontrado" << endl;
            break;
    }
    // 3. Escrever o vetor ordenado no arquivo csv:
    //    matricula;nome;ano de ingresso;curso;IRA

}

void Siga::SalvarListaOrdenadaEstudantes(std::string arquivo_txt)
{
    // Iremos aplicar a ordenação na memoria, para isso faca:
    // 1. Ler todos os dados do arquivo binário colocandos em um vetor
    // 2. Ordenar o vetor usando a seguinte sequencia:
    //    - Ordenar por nome 
    //    - Ordenar por curso
    // Observação: escolha metodos que sejam estaveis na segunda chamada de ordenação.
    // 3. Escrever o vetor ordenado no arquivo csv 
    //    matricula;nome;ano de ingresso;curso;IRA

}

