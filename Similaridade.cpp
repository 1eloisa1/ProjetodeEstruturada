#include <stdio.h>
#include <stdlib.h>
#include "Similaridade.h"

Matriz criarMatrizClienteProduto(ListaCompras* dados) {
    Matriz mat;
    mat.linhas = dados->clienteCodigo.size();
    mat.colunas = dados->produtoCodigo.size();

    mat.valores = (int**) malloc(mat.linhas * sizeof(int*));

    for (int i = 0; i < mat.linhas; i++) {
        mat.valores[i] = (int*) malloc(mat.colunas * sizeof(int));

        for (int j = 0; j < mat.colunas; j++)
            mat.valores[i][j] = 0;

        for (int p : dados->comprasCliente[i])
            mat.valores[i][p] = 1;
    }

    return mat;
}

Matriz calculaTransposta(Matriz* A) {
    Matriz At;
    At.linhas = A->colunas;
    At.colunas = A->linhas;

    At.valores = (int**) malloc(At.linhas * sizeof(int*));

    for (int i = 0; i < At.linhas; i++)
        At.valores[i] = (int*) malloc(At.colunas * sizeof(int));

    for (int i = 0; i < A->linhas; i++)
        for (int j = 0; j < A->colunas; j++)
            At.valores[j][i] = A->valores[i][j];

    return At;
}

Matriz calcularIntersecao(Matriz* A, Matriz* At) {
    Matriz I;
    I.linhas = A->linhas;
    I.colunas = A->linhas;

    I.valores = (int**) malloc(I.linhas * sizeof(int*));

    for (int i = 0; i < I.linhas; i++) {
        I.valores[i] = (int*) malloc(I.colunas * sizeof(int));

        for (int j = 0; j < I.colunas; j++) {
            I.valores[i][j] = 0;

            for (int k = 0; k < A->colunas; k++) {
                I.valores[i][j] += A->valores[i][k] * At->valores[k][j];
            }
        }
    }

    return I;
}

Matriz multiplica_por_transposta(Matriz* A) {
    Matriz C;
    C.linhas = A->linhas;
    C.colunas = A->linhas;

    C.valores = (int**) malloc(C.linhas * sizeof(int*));

    for (int i = 0; i < C.linhas; i++) {
        C.valores[i] = (int*) malloc(C.colunas * sizeof(int));
        for (int j = 0; j < C.colunas; j++)
            C.valores[i][j] = 0;
    }

    for (int i = 0; i < C.linhas; i++) {
        for (int j = i; j < C.linhas; j++) {
            int soma = 0;

            for (int k = 0; k < A->colunas; k++) {
                soma += A->valores[i][k] * A->valores[j][k];
            }

            C.valores[i][j] = soma;
            C.valores[j][i] = soma;
        }
    }

    return C;
}

MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, ListaCompras* dados) {
    MatrizSimilaridade S;
    S.n = intersecao->linhas;

    S.valores = (float**) malloc(S.n * sizeof(float*));

    for (int i = 0; i < S.n; i++) {
        S.valores[i] = (float*) malloc(S.n * sizeof(float));

        float total = dados->comprasCliente[i].size();

        for (int j = 0; j < S.n; j++) {
            if (total == 0)
                S.valores[i][j] = 1.0;
            else
                S.valores[i][j] = 1.0 - ((float)intersecao->valores[i][j] / total);
        }
    }

    return S;
}

void liberarMatriz(Matriz mat) {
    for (int i = 0; i < mat.linhas; i++)
        free(mat.valores[i]);
    free(mat.valores);
}

void liberarMatrizSim(MatrizSimilaridade mat) {
    for (int i = 0; i < mat.n; i++)
        free(mat.valores[i]);
    free(mat.valores);
}