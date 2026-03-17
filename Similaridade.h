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

Matriz criarMatrizDensa(ListaCompras* dados);

Matriz calcularIntersecao(Matriz* A);

MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, ListaCompras* dados);

void liberarMatriz(Matriz mat);

void liberarMatrizSim(MatrizSimilaridade mat);

#endif