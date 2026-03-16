#ifndef SIMILARIDADE_H
#define SIMILARIDADE_H

#include "ListaCompras.h"

// Matriz de inteiros (para a densa e interseção)
typedef struct {
    int linhas;
    int colunas;
    int **valores;
} Matriz;

// Matriz de decimais (para a similaridade final)
typedef struct {
    int n; // Matriz quadrada n x n (clientes x clientes)
    float **valores;
} MatrizSimilaridade;

Matriz criarMatrizDensa(ListaCompras* dados);
Matriz calcularIntersecao(Matriz* A);
MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, ListaCompras* dados);

void liberarMatriz(Matriz mat);
void liberarMatrizSim(MatrizSimilaridade mat);

#endif
