#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "ListaCompras.h"

using namespace std;


void podarEspacos(char *s) {
    int n = strlen(s);
    while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\r' || s[n-1] == '\n' || s[n-1] == '\t')) {
        s[n-1] = '\0';
        n--;
    }
}

void carregarDados(ListaCompras *dados, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo %s\n", nomeArquivo);
        exit(1);
    }

    char data[50], codCliente[50], codProduto[50], nomeProduto[250];

    char cabecalho[500];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // MASCARA: %[^,] lê até a vírgula. %[^\n] lê até o fim da linha.
    while (fscanf(arquivo, " %[^,],%[^,],%[^,],%[^\n]", data, codCliente, codProduto, nomeProduto) == 4) {
        
        podarEspacos(codCliente);
        podarEspacos(codProduto);
        podarEspacos(nomeProduto);

        string clienteStr = codCliente;
        string produtoStr = codProduto;

        int indiceCliente;
        if (dados->mapaCliente.find(clienteStr) == dados->mapaCliente.end()) {
            indiceCliente = (int)dados->clientesCodigos.size();
            dados->clientesCodigos.push_back(clienteStr);
            dados->mapaCliente[clienteStr] = indiceCliente;
            dados->comprasCliente.push_back(list<int>());
        } else {
            indiceCliente = dados->mapaCliente[clienteStr];
        }

        int indiceProduto;
        if (dados->mapaProduto.find(produtoStr) == dados->mapaProduto.end()) {
            indiceProduto = (int)dados->produtosNomes.size();
            dados->produtosNomes.push_back(nomeProduto);
            dados->mapaProduto[produtoStr] = indiceProduto;
        } else {
            indiceProduto = dados->mapaProduto[produtoStr];
        }

        // Adicionar compra
        dados->comprasCliente[indiceCliente].push_back(indiceProduto);
    }

    fclose(arquivo);

    /*printf("Carga finalizada. %d clientes e %d produtos lidos.\n", 
        (int)dados->clientesCodigos.size(), (int)dados->produtosNomes.size());*/
}

void mostrarComprasCliente(ListaCompras *dados, string codigoCliente) {
    if (dados->mapaCliente.find(codigoCliente) == dados->mapaCliente.end()) {
        printf("Erro: Cliente %s nao encontrado no sistema.\n", codigoCliente.c_str());
        return;
    }

    int indice = dados->mapaCliente[codigoCliente];
    printf("Historico de compras do cliente %s:\n", codigoCliente.c_str());

    for (int idProd : dados->comprasCliente[indice]) {
        cout << " - " << dados->produtosNomes[idProd] << endl;
    }
}