#include "ListaCompras.h"

typedef struct {
    int linhas;
    int colunas;
    int **valores;
} Matriz;

Matriz criarMatrizDensa(ListaCompras* dados);

void liberarMatriz(Matriz mat);
