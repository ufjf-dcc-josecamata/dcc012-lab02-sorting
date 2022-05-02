#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

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
    int n_importados = this->n_estudantes;

    ifstream arq;
    arq.open(file, ios::in);
    if(!arq.is_open()){
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }
    string line;
    getline(arq, line); // header line
    while(getline(arq, line)){
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ';')){
            tokens.push_back(token);
        }
        if(tokens.size() == 5){
            Estudante est;
            est.TrocarMatricula(stoi(tokens[0]));
            est.TrocarNome(tokens[1].c_str());
            est.TrocarAnoIngresso(stoi(tokens[2]));
            est.TrocarCurso(stoi(tokens[3]));
            est.TrocarIRA(stof(tokens[4]));
            this->CadastraEstudante(est);
        }
    }
    n_importados = this->n_estudantes - n_importados;
    // TODO: 
    // Abra um arquivo .csv com a seguinte formatação:
    // Matricula;Nome;Ano de Ingresso;Curso;IRA
    // Para cada linha do arquivo, criar um objeto Estudante e escrever no arquivo binário.

    // Atualize o numero de registros no binário.
    // Imprima o numero de estudantes importados:
    cout << "Importacao concluida: " << n_importados << " novos alunos cadastrados" << endl;
     
    
}

bool compare_estudante_nome(Estudante &a, Estudante &b)
{
    return strcmp(a.ObterNome(), b.ObterNome()) < 0;
}

bool compare_estudante_ira(Estudante &a, Estudante &b)
{
    return a.ObterIRA() >  b.ObterIRA();
}

bool compare_estudante_curso(Estudante &a, Estudante &b)
{
    return a.ObterCurso() <  b.ObterCurso();
}

Estudante* Siga::build_vector_from_file()
{
    Estudante *estudantes = new Estudante[this->n_estudantes];
    this->file_stream.seekg(0, this->file_stream.beg);
    for(int i = 0; i < this->n_estudantes; i++){
        estudantes[i].LerDoArquivoBinario(this->file_stream);
    }
    return estudantes;
}

void Siga::SalvarListaOrdendaEstudantesPorNome(string arquivo_txt, sorting_method method)
{
    // Iremos aplicar a ordenação na memoria, para isso faca:
    // 1. Ler todos os dados do arquivo binário colocandos em um vetor
    // 2. Ordenar o vetor usando o metodo de ordenação escolhido:
    //    - Ordenar por nome
    Estudante * list_estudantes = build_vector_from_file();
    switch(method){
        case BUBBLESORT:
            bubble_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
            break;
        case INSERTIONSORT:
            insert_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
            break;
        case SELECTIONSORT:
            selection_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
            break;
        default:
           cout << "metodo de ordenação não encontrado" << endl;
            break;
    }
    // 3. Escrever o vetor ordenado no arquivo ascii 

    ofstream arq;
    arq.open(arquivo_txt, ios::out);
    if(!arq.is_open()){
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }
    for(int i = 0; i < this->n_estudantes; i++){
        arq << list_estudantes[i].ObterMatricula() << ";" << list_estudantes[i].ObterNome() << ";" << list_estudantes[i].ObterAnoIngresso() << ";" << list_estudantes[i].ObterCurso() << ";" << list_estudantes[i].ObterIRA() << endl;
    }

    arq.close();

    delete [] list_estudantes;

}

void Siga::SalvarListaOrdenadaEstudantes(std::string arquivo_txt)
{
    // Iremos aplicar a ordenação na memoria, para isso faca:
    // 1. Ler todos os dados do arquivo binário colocandos em um vetor
    // 2. Ordenar o vetor usando a seguinte sequencia:
    //    - Ordenar por Curso 
    //    - Ordene  por nome (crescente)
    // 3. Escrever o vetor ordenado no arquivo ASCII 
    Estudante * list_estudantes = build_vector_from_file();
            
    bubble_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_nome);
    bubble_sort<Estudante>(list_estudantes, this->n_estudantes, compare_estudante_curso);

    


    ofstream arq;
    arq.open(arquivo_txt, ios::out);
    if(!arq.is_open()){
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }
    for(int i = 0; i < this->n_estudantes; i++){
        arq << list_estudantes[i].ObterMatricula() << ";" << list_estudantes[i].ObterNome() << ";" << list_estudantes[i].ObterAnoIngresso() << ";" << list_estudantes[i].ObterCurso() << ";" << list_estudantes[i].ObterIRA() << endl;
    }

    arq.close();

    delete [] list_estudantes;

}

