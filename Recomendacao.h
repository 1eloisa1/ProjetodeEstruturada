#ifndef RECOMENDACAO_H 
#define RECOMENDACAO_H

#include "ListaCompras.h"


void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada);

typedef struct  {
    string nome;
    double similaridade;
} ProdutoRanqueado;

bool compararSimilaridade(const ProdutoRanqueado &a, const ProdutoRanqueado &b);


#endif