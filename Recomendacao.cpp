#include <iostream>
#include <vector>
#include <algorithm>
#include "Recomendacao.h"

using namespace std;

bool compararSimilaridade(const ProdutoRanqueado &a, const ProdutoRanqueado &b) {
    return a.score < b.score;
}

void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada, int k) {

    if (dados->mapaCliente.count(codigoEntrada) == 0) {
        cout << "Cliente nao encontrado!\n";
        return;
    }

    int indice = dados->mapaCliente[codigoEntrada];

    vector<double> R(dados->produtoCodigo.size(), 1.0);
    vector<ProdutoRanqueado> ranking;

    vector<int> vizinhos;

    for (int i = 0; i < S->n; i++) {
        if (i != indice && S->valores[indice][i] < 1)
            vizinhos.push_back(i);
    }

    for (int s : vizinhos) {
        for (int p : dados->comprasCliente[]
            s]) {

            if (find(dados->comprasCliente[indice].begin(),
                     dados->comprasCliente[indice].end(),
                     p) == dados->comprasCliente[indice].end()) {

                R[p] *= S->valores[indice][s];
            }
        }
    }

    for (int i = 0; i < R.size(); i++) {
        if (R[i] != 1.0) {
            ProdutoRanqueado prod;
            prod.nome = dados->produtoNomes[i];
            prod.score = R[i];
            ranking.push_back(prod);
        }
    }

    sort(ranking.begin(), ranking.end(), compararSimilaridade);

    cout << "\nRecomendacoes:\n";
    for (int i = 0; i < k && i < ranking.size(); i++) {
        cout << i + 1 << " - " << ranking[i].nome << endl;
    }
}