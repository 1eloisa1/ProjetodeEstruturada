#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace std;

// --- MANTENDO SUAS ESTRUTURAS ---
typedef struct {
    int linhas;
    int colunas;
    int** valores;
} Matriz;

typedef struct {
    int n;
    float** valores;
} MatrizSimilaridade;

// --- SUAS FUNÇÕES (AJUSTADAS APENAS ONDE ERA ESSENCIAL) ---

Matriz criarMatrizClienteProduto(int n_clientes, int n_produtos, const vector<vector<int>>& listaCompras) {
    Matriz mat;
    mat.linhas = n_clientes;
    mat.colunas = n_produtos;

    mat.valores = (int**) malloc(mat.linhas * sizeof(int*));
    for (int i = 0; i < mat.linhas; i++) {
        mat.valores[i] = (int*) malloc(mat.colunas * sizeof(int));
        for (int j = 0; j < mat.colunas; j++) mat.valores[i][j] = 0;

        for (int idproduto : listaCompras[i]) {
            mat.valores[i][idproduto] = 1;
        }
    }
    return mat;
}

Matriz multiplica_por_transposta(Matriz* A) {
    Matriz C;
    C.linhas = A->linhas;
    C.colunas = A->linhas; 
    C.valores = (int**) malloc(C.linhas * sizeof(int*));
    for (int i = 0; i < C.linhas; i++) {
        C.valores[i] = (int*) malloc(C.colunas * sizeof(int));
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

MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, const vector<vector<int>>& listaCompras) {
    MatrizSimilaridade S;
    S.n = intersecao->linhas;
    S.valores = (float**) malloc(S.n * sizeof(float*));
    
    for (int i = 0; i < S.n; i++) {
        S.valores[i] = (float*) malloc(S.n * sizeof(float));
        float totalCompradoI = (float)listaCompras[i].size();
        for (int j = 0; j < S.n; j++) {
            if (totalCompradoI > 0) {
                S.valores[i][j] = 1.0f - ((float)intersecao->valores[i][j] / totalCompradoI);
            } else {
                S.valores[i][j] = 1.0f;
            }
        }
    }
    return S;
}

void liberarMatriz(Matriz mat) {
    for (int i = 0; i < mat.linhas; i++) free(mat.valores[i]);
    free(mat.valores);
}

// --- A "PONTE" PARA O PYBIND11 (O que faz seu código funcionar no Python) ---

vector<vector<float>> solver_recomendacao(int n_clientes, int n_produtos, vector<vector<int>> listaCompras) {
    // 1. Usa sua função para criar a matriz
    Matriz A = criarMatrizClienteProduto(n_clientes, n_produtos, listaCompras);
    
    // 2. Usa sua função de multiplicação
    Matriz I = multiplica_por_transposta(&A);
    
    // 3. Usa sua função de similaridade
    MatrizSimilaridade S = calcularSimilaridade(&I, listaCompras);
    
    // 4. Converte o seu float** para vector<vector<float>> (para o Python entender)
    vector<vector<float>> resultado(S.n, vector<float>(S.n));
    for (int i = 0; i < S.n; i++) {
        for (int j = 0; j < S.n; j++) {
            resultado[i][j] = S.valores[i][j];
        }
    }
    
    // 5. Libera a memória do seu malloc
    liberarMatriz(A);
    liberarMatriz(I);
    // (Adicione liberarMatrizSim se necessário)
    
    return resultado;
}

// Registro do Módulo para o Python
PYBIND11_MODULE(meu_solver, m) {
    m.doc() = "Módulo de recomendação usando o código original em C";
    m.def("calcular_similaridade", &solver_recomendacao, "Calcula a similaridade de Jaccard");
}