#ifndef SIMILARIDADE_H 
#define SIMILARIDADE_H

#include "ListaCompras.h"

typedef struct {
    int linhas;     
    int colunas;    
    int **valores;  
} Matriz;


typedef struct {
    int n;          
    float **valores; 
} MatrizSimilaridade;


Matriz criarMatrizClienteProduto(ListaCompras* dados);
Matriz calculaTransposta(Matriz* A);
Matriz calcularIntersecao(Matriz* A, Matriz* At);
Matriz multiplica_por_transposta(Matriz* A);

MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, ListaCompras* dados);

void liberarMatriz(Matriz mat);

void liberarMatrizSim(MatrizSimilaridade mat);

#endif