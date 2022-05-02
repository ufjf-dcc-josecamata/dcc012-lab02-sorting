# Algoritmos de Ordenação (Parte 1)

## Objetivos:
Aprender os algoritmos básicos de ordenação. 

## Métodos:

Os métodos básicos que iremos abordar nesta atividade são: 
 - método  da bolha
 - método  da seleção
 - método  da inserção 
 
## O que deve ser feito? 

### Pre-processamento:

Deve concluir a implementação do método ImportCSVData da classe Siga. Esse método deve importar novos estudantes 
a partir de um arquivo CSV em formanto ASCII.  os datalhes do que deve ser implementado está no arquivo siga.cc.

### Implementação dos Métodos de ordenação
Os três métodos de ordenação supracitados deve ser implementados na pasta siga. Aqui, duas escolhas podem ser feitas: 
(1) Usar funções templates. Assim, a sua codificação deve ser feita no arquivo siga/include/sort.h.
(2) Caso optem por não usar funções tamplates, a condificação deve ser em include/sort.h e src/sort.cc

A utilização dos métodos de ordenação se dará na chamada dos seguintes métodos da classe Siga:

 - SalvaListaOrdenadoPorNome()
 - SalvaListaOrdenadaEstudantes()

Novamente, os detalhes do que deve ser implementado, encontra-se no arquivo siga.cc

## Compilação e execução

```
cmake -B build 
cmake --build build 
./build/tests/test1
./build/tests/test2
etc

```


