#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"
#include <stdio.h>

bool compararSimilaridade(Similares a, Similaridade b) {
    return a.similaridade < b.similaridade; 
}

// lista com todos os clientes com similariade ao cliente de entrada, ordenada por similaridade
void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada) {
    if (dados->mapaCliente.count(codigoEntrada) == 0) {
        printf("Cliente nao encontrado!\n");
        return;
    } else{
        for (int i = 0; i < S->n; i++) {
            if (dados->clientesCodigos[i] == codigoEntrada) {
                continue;
            }
            if (S->valores[dados->mapaCliente[codigoEntrada]][i] < 1) {
                similares.push_back(i);
            }
        }
        //Para cada cliente, crie um vetor 𝑅 de ranqueamento para todos os produtos da loja, atribuindo um valor inicial de 1 para cada produto;
        int indice = dados->mapaCliente[codigoEntrada];


        for (int i = 0; i < dados->produtosNomes.size(); i++) {
            R.push_back(1.0);
        } 

        //Cálculo do Ranqueamento: Para cada cliente 𝑠 ∈ 𝐿 e para cada produto 𝑝 comprado por 𝑠 e não comprado por 𝑐, atualize o ranqueamento específico do produto 𝑝 fazendo: 𝑅𝑝 ← 𝑅𝑝 × 𝑠(𝑐, 𝑠);

        for(int s : similares) {
            for(int p : dados->comprasCliente[s]) {
                if(find(dados->comprasCliente[indice].begin(), dados->comprasCliente[indice].end(),  p) == dados->comprasCliente[indice].end()) {
                    R[p] *= S->valores[indice][s];
                }
            }
        }

        //Ordene o vetor 𝑅 de forma não decrescente e retorne os 𝑘 primeiros produtos da lista 𝑅. Estes serão os produtos melhor ranqueados e, portanto, recomendados ao cliente 𝑐.
    
        for (int i = 0; i < R.size(); i++) {
            // ordem crescente de similaridade
            sort(R.begin(), R.end(), compararSimilaridade);
            printf("Produto: %s, Ranqueamento: %.4f\n", dados->produtosNomes[i].c_str(), R[i]);
        }

}
    //s nomes dos 𝑘 produtos melhor recomendados para cada cliente, demonstrando a funcionalidade completa do sistema de recomendação

    // Crie uma lista 𝐿 com todos os clientes que possuem  similaridade com 𝑐 (similaridade menor que 1 e que não seja o próprio cliente 𝑐);


}