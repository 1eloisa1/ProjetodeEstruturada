#include <stdio.h>
#include <stdlib.h>
#include "Similaridade.h"

Matriz criarMatrizDensa(ListaCompras* dados) {
    Matriz mat;
    mat.linhas = (*dados).clientesCodigos.size();
    mat.colunas = (*dados).produtosNomes.size();

    mat.valores = (int**) malloc(mat.linhas * sizeof(int*));
    for (int i = 0; i < mat.linhas; i++) {
        mat.valores[i] = (int*) malloc(mat.colunas * sizeof(int));
        for (int j = 0; j < mat.colunas; j++) {
            mat.valores[i][j] = 0;
        }
    }

    for (int i = 0; i < mat.linhas; i++) {
        for (int idProduto : (*dados).comprasCliente[i]) {
            mat.valores[i][idProduto] = 1;
        }
    }
    
    return mat;
}

void liberarMatriz(Matriz mat) {
    for (int i = 0; i < mat.linhas; i++) {
        free(mat.valores[i]);
    }
    free(mat.valores);
}