#ifndef RECOMENDACAO_H 
#define RECOMENDACAO_H

#include "ListaCompras.h"

bool compararSimilaridade(Similares a, Similaridade b);

void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada);
list<int> similares;

vector<double> R;

#endif