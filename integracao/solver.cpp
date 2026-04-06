#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <stdio.h>
#include <map>
#include <cmath>

namespace py = pybind11;
using namespace std;

typedef struct {
    vector<string> clienteCodigo; 
    map<string, int> mapaCliente;   

    vector<string> produtoCodigo;   
    vector<string> produtoNomes;
    map<string, int> mapaProduto;  

    vector< list<int> > comprasCliente; 
} ListaCompras;

typedef struct {
    int linhas;     
    int colunas;    
    int **valores;  
} Matriz;

typedef struct {
    int n;          
    float **valores; 
} MatrizSimilaridade;

typedef struct  {
    string nome;
    double similaridade;
} ProdutoRanqueado;

bool compararSimilaridade(const ProdutoRanqueado &a, const ProdutoRanqueado &b) {
    return a.similaridade < b.similaridade; //acho que ta errado, ver depois
}

void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada) {

    list<int> similares;
    vector<double> R;
    vector<ProdutoRanqueado> Vetor;

    if (dados->mapaCliente.count(codigoEntrada) == 0) {
        printf("Cliente nao encontrado!\n");
        return;

    } else{
        for (int i = 0; i < S->n; i++) {
            if (dados->clienteCodigo[i] == codigoEntrada){
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

    sort(Vetor.begin(), Vetor.end(), compararSimilaridade);
        for (int i = 0; i < Vetor.size(); i++) {
            printf("Produto recomendado %d: %s\n", i + 1, Vetor[i].nome.c_str());
    }
        }

} 

Matriz criarMatrizClienteProduto(ListaCompras* dados) {
    Matriz mat;
    mat.linhas = (int)dados->clienteCodigo.size();
    mat.colunas = (int)dados->produtoCodigo.size();

    mat.valores = (int**) malloc(mat.linhas * sizeof(int*));
    for (int i = 0; i < mat.linhas; i++) {
        mat.valores[i] = (int*) malloc(mat.colunas * sizeof(int));
        
        for (int j = 0; j < mat.colunas; j++) {
            mat.valores[i][j] = 0;
        }
        for (int idproduto : dados->comprasCliente[i]) {
                mat.valores[i][idproduto] = 1;
        }
    }

    return mat;
}

Matriz calculaTransposta(Matriz* A) {
    Matriz At;
    At.linhas = A->colunas;
    At.colunas = A->linhas;
    At.valores = (int**) malloc(At.linhas * sizeof(int*));
    for (int i = 0; i < At.linhas; i++) {
        At.valores[i] = (int*) malloc(At.colunas * sizeof(int)); 
    }
    for (int i = 0; i < A->linhas; i++) {
        for (int j = 0; j < A->colunas; j++) {
            At.valores[j][i] = A->valores[i][j];
        }
    }
    return At;
}

Matriz calcularIntersecao(Matriz* A, Matriz* At) {
    Matriz I;
    I.linhas = A->linhas;   
    I.colunas = At->colunas;

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

void recomendar(string id_digitado, vector<vector<string>> dados_csv) {
    ListaCompras dados;

    //tem que converter para o csv lido em python para struct aqui, depois criar a matriz cliente-produto, calcular a transposta, calcular a intersecao, calcular a similaridade e mostrar as recomendacoes, por fim liberar a memoria alocada




PYBIND11_MODULE(meu_solver, m) {
    m.doc() = "Sistema Completo de Recomendacao"; 
    m.def("recomendar", &recomendar, "Executa todo o processo e limpa memoria no fim",
          py::arg("id_alvo"), py::arg("dados_csv"));
}