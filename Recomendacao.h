#ifndef RECOMENDACAO_H 
#define RECOMENDACAO_H

#include "ListaCompras.h"
#include "Similaridade.h"
#include <vector>
#include <string>

using namespace std;

typedef struct  {
    string nome;
    double score;
} ProdutoRanqueado;

void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada, int k);

bool compararSimilaridade(const ProdutoRanqueado &a, const ProdutoRanqueado &b);

#endif