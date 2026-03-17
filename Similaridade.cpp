#include <stdio.h>  
#include <stdlib.h> 
#include "Similaridade.h" 

Matriz criarMatrizDensa(ListaCompras* dados) {
    Matriz mat;
    mat.linhas = (int)dados->clientesCodigos.size();
    mat.colunas = (int)dados->produtosNomes.size();

    mat.valores = (int**) malloc(mat.linhas * sizeof(int*));
    for (int i = 0; i < mat.linhas; i++) {
        // Usa malloc no lugar de calloc
        mat.valores[i] = (int*) malloc(mat.colunas * sizeof(int));
        
        // Zera os elementos manualmente
        for (int j = 0; j < mat.colunas; j++) {
            mat.valores[i][j] = 0;
        }
    }

    for (int i = 0; i < mat.linhas; i++) {
        for (int idProduto : dados->comprasCliente[i]) {
            mat.valores[i][idProduto] = 1;
        }
    }
    return mat;
}

Matriz calcularIntersecao(Matriz* A) {
    Matriz I;
    I.linhas = A->linhas;   
    I.colunas = A->linhas;
    
    I.valores = (int**) malloc(I.linhas * sizeof(int*));
    for (int i = 0; i < I.linhas; i++) {
        // Usa malloc no lugar de calloc
        I.valores[i] = (int*) malloc(I.colunas * sizeof(int)); 
        
        // Zera os elementos manualmente (muito importante para o += funcionar depois)
        for (int j = 0; j < I.colunas; j++) {
            I.valores[i][j] = 0;
        }
    }

    for (int i = 0; i < I.linhas; i++) {          
        for (int j = 0; j < I.colunas; j++) {      
            for (int k = 0; k < A->colunas; k++) {
                I.valores[i][j] += A->valores[i][k] * A->valores[j][k];
            }
        }
    }
    return I;
}

MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, ListaCompras* dados) {
    MatrizSimilaridade S;
    S.n = intersecao->linhas;
    S.valores = (float**) malloc(S.n * sizeof(float*));

    for (int i = 0; i < S.n; i++) {
        S.valores[i] = (float*) malloc(S.n * sizeof(float));
       
        float totalCompradoI = (float)dados->comprasCliente[i].size();
        for (int j = 0; j < S.n; j++) {
            if (totalCompradoI == 0) {
                S.valores[i][j] = 1.0f;
            } else {
                S.valores[i][j] = 1.0f - ((float)intersecao->valores[i][j] / totalCompradoI);
            }
        }
    }
    return S;
}

void liberarMatriz(Matriz mat) {
    for (int i = 0; i < mat.linhas; i++) {
        free(mat.valores[i]);
    }
    free(mat.valores);
}

void liberarMatrizSim(MatrizSimilaridade mat) {
    for (int i = 0; i < mat.n; i++) {
        free(mat.valores[i]);
    }
    free(mat.valores); 
}