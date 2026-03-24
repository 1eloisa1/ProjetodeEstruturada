#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "ListaCompras.h"

using namespace std;


void carregarDados(ListaCompras *dados, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        exit(1);
    }

    char data[50], codCliente[50], codProduto[50], nomeProduto[250];

    char cabecalho[500];
    fgets(cabecalho, sizeof(cabecalho), arquivo);


    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, codCliente, codProduto, nomeProduto) == 4) {

        string clienteStr = codCliente;
        string produtoStr = codProduto;
        string nomeStr = nomeProduto;

        int indiceCliente;
        if (dados->mapaCliente.find(clienteStr) == dados->mapaCliente.end()) {
            indiceCliente = (int)dados->clienteCodigo.size();
            dados->clienteCodigo.push_back(clienteStr);
            dados->mapaCliente[clienteStr] = indiceCliente;
            dados->comprasCliente.push_back(list<int>());
        } else {
            indiceCliente = dados->mapaCliente[clienteStr];
        }

        int indiceProduto;
        if (dados->mapaProduto.find(produtoStr) == dados->mapaProduto.end()) {
            indiceProduto = (int)dados->produtoCodigo.size();
            dados->produtoCodigo.push_back(produtoStr);
            dados->produtoNomes.push_back(nomeStr);
            dados->mapaProduto[produtoStr] = indiceProduto;
        } else {
            indiceProduto = dados->mapaProduto[produtoStr];
        }
        
        dados->comprasCliente[indiceCliente].push_back(indiceProduto);
    }

    fclose(arquivo);

}

void mostrarComprasCliente(ListaCompras *dados, string codigoCliente) {
    if (dados->mapaCliente.find(codigoCliente) == dados->mapaCliente.end()) {
        printf("Erro: Cliente %s nao encontrado no sistema.\n", codigoCliente.c_str());
        return;
    }

    int indice = dados->mapaCliente[codigoCliente];
    printf("Historico de compras do cliente %s:\n", codigoCliente.c_str());

    for (int idProd : dados->comprasCliente[indice]) {
        printf(" - %s\n", dados->produtoNomes[idProd].c_str());
    }
}