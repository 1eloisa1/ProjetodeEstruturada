#ifndef SIMILARIDADE_E_RECOMENDACAO_H
#define SIMILARIDADE_E_RECOMENDACAO_H


typedef struct {
    int linhas;     
    int colunas;    
    int **valores;  
} Matriz;


typedef struct {
    int n;          
    float **valores; 
} MatrizSimilaridade;


Matriz criarMatrizClienteProduto(ListaCompras* dados);
Matriz calculaTransposta(Matriz* A);
Matriz calcularIntersecao(Matriz* A, Matriz* At);
Matriz multiplica_por_transposta(Matriz* A);

MatrizSimilaridade calcularSimilaridade(Matriz* intersecao, ListaCompras* dados);

void liberarMatriz(Matriz mat);

void liberarMatrizSim(MatrizSimilaridade mat);

void mostraRecomendacoes(ListaCompras *dados, MatrizSimilaridade *S, string codigoEntrada);

typedef struct  {
    string nome;
    double similaridade;
} ProdutoRanqueado;

bool compararSimilaridade(const ProdutoRanqueado &a, const ProdutoRanqueado &b);

#endif