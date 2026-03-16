#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

typedef struct {
    vector<string> clientesCodigos; // Índice -> Código Original
    map<string, int> mapaCliente;   // Código Original -> Índice

    vector<string> produtosNomes;   // Índice -> Nome do Produto
    map<string, int> mapaProduto;   // Código Original do Produto -> Índice

    vector< list<int> > comprasCliente; // Lista de compras por cliente
} ListaCompras;

void carregarDados(ListaCompras *dados, const char *nomeArquivo);
void mostrarComprasCliente(ListaCompras *dados, string codigoCliente);

#endif