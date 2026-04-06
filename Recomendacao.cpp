#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
#include <stdio.h>

bool compararSimilaridade(const ProdutoRanqueado &a, const ProdutoRanqueado &b) {
    return a.similaridade < b.similaridade; 
}

vector<tuple<string, double>>  mostraRecomendacoes(ListaCompras *dados,  vector<vector<double>>& MatrizSimilaridade *S, string codigoEntrada) {


    list<int> similares;
    vector<double> R;
    vector<ProdutoRanqueado> Vetor;


    int totalProdutos = dados.vetorProdutos.size();
    int totalClientes = dados.vetorClientes.size();
    if (dados->mapaCliente.count(codigoEntrada) == 0) {
        printf("Cliente nao encontrado!\n");
        return;

    } else{
        for (int i = 0; i < S->n; i++) {
            if (dados->clienteCodigo[i] == codigoEntrada) {
                continue;
            }
            if (S->valores[dados->mapaCliente[codigoEntrada]][i] < 1) {
                similares.push_back(i);
            }
        }
        
        int indice = dados->mapaCliente[codigoEntrada];


        for (int i = 0; i < dados->produtoCodigo.size(); i++) {
            R.push_back(1.0);
        } 

        for(int s : similares) {
            for(int p : dados->comprasCliente[s]) {
                if(find(dados->comprasCliente[indice].begin(), dados->comprasCliente[indice].end(),  p) == dados->comprasCliente[indice].end()) {
                    R[p] *= S->valores[indice][s];
                }
            }
        }

        
    for(int i = 1; i <= 10; i++){
        if(R[i] != 1.0) {
            ProdutoRanqueado temp;
            temp.nome = dados->produtoNomes[i];
            temp.similaridade = R[i];
            Vetor.push_back(temp);
        }
    }

    std::sort(Vetor.begin(), Vetor.end(), compararSimilaridade);
        for (int i = 0; i < Vetor.size(); i++) {
            printf("Produto recomendado %d: %s\n", i + 1, Vetor[i].nome.c_str());
    }
        }

}
