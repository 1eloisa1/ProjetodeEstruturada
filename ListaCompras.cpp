#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "ListaCompras.h"

using namespace std;

void carregarDados(ListaCompras *dados, const char *nomeArquivo){

    FILE *arquivo;

    char data[20];
    char codCliente[50];
    char codProduto[50];
    char nomeProduto[200];

    arquivo = fopen(nomeArquivo,"r");

    if(arquivo == NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    while(fscanf(arquivo,"%[^ ] %[^ ] %[^ ] %[^\n]\n",
                 data,codCliente,codProduto,nomeProduto)==4){

        string clienteStr = codCliente;
        string produtoStr = codProduto;

        int indiceCliente;
        int indiceProduto;

        if(dados->mapaCliente.find(clienteStr) == dados->mapaCliente.end()){

            indiceCliente = dados->clientesCodigos.size();

            dados->clientesCodigos.push_back(clienteStr);

            dados->mapaCliente[clienteStr] = indiceCliente;

            list<int> listaVazia;
            dados->comprasCliente.push_back(listaVazia);

        }
        else{
            indiceCliente = dados->mapaCliente[clienteStr];
        }

        if(dados->mapaProduto.find(produtoStr) == dados->mapaProduto.end()){

            indiceProduto = dados->produtosNomes.size();

            dados->produtosNomes.push_back(nomeProduto);

            dados->mapaProduto[produtoStr] = indiceProduto;
        }
        else{
            indiceProduto = dados->mapaProduto[produtoStr];
        }

        dados->comprasCliente[indiceCliente].push_back(indiceProduto);
    }

    fclose(arquivo);
}

void mostrarComprasCliente(ListaCompras *dados, string codigoCliente){

    if(dados->mapaCliente.find(codigoCliente) == dados->mapaCliente.end()){

        printf("Cliente nao encontrado\n");
        return;
    }

    int indice = dados->mapaCliente[codigoCliente];

    printf("Produtos comprados:\n");

    for(int produto : dados->comprasCliente[indice]){

        cout << dados->produtosNomes[produto] << endl;
    }
}