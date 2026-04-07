#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include "ListaCompras.h"
//mesma coisa
using namespace std;

void carregarDados(ListaCompras *dados, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        exit(1);
    }


    char cabecalho[500];
    fgets(cabecalho, sizeof(cabecalho), arquivo);


    char data[50], codCliente[50], codProduto[50], nomeProduto[250];

    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, codCliente, codProduto, nomeProduto) == 4) {

        string clienteStr = codCliente;
        string produtoStr = codProduto;
        string nomeStr = nomeProduto;

        int indiceCliente;
        if (dados->mapaCliente.find(clienteStr) == dados->mapaCliente.end()) {
            indiceCliente = dados->clienteCodigo.size();
            dados->clienteCodigo.push_back(clienteStr);
            dados->mapaCliente[clienteStr] = indiceCliente;
            dados->comprasCliente.push_back(list<int>());
        } else {
            indiceCliente = dados->mapaCliente[clienteStr];
        }

        int indiceProduto;
        if (dados->mapaProduto.find(produtoStr) == dados->mapaProduto.end()) {
            indiceProduto = dados->produtoCodigo.size();
            dados->produtoCodigo.push_back(produtoStr);
            dados->produtoNomes.push_back(nomeStr);
            dados->mapaProduto[produtoStr] = indiceProduto;
        } else {
            indiceProduto = dados->mapaProduto[produtoStr];
        }

        // EVITA DUPLICADOS
        if (find(dados->comprasCliente[indiceCliente].begin(),
                 dados->comprasCliente[indiceCliente].end(),
                 indiceProduto) == dados->comprasCliente[indiceCliente].end()) {
            dados->comprasCliente[indiceCliente].push_back(indiceProduto);
        }
    }

    fclose(arquivo);
}

void mostrarComprasCliente(ListaCompras *dados, string codigoCliente) {
    if (dados->mapaCliente.find(codigoCliente) == dados->mapaCliente.end()) {
        printf("Cliente nao encontrado\n");
        return;
    }

    int idx = dados->mapaCliente[codigoCliente];

    printf("Compras do cliente %s:\n", codigoCliente.c_str());
    for (int p : dados->comprasCliente[idx]) {
        printf(" - %s\n", dados->produtoNomes[p].c_str());
    }
}