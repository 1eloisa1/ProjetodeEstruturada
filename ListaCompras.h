#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

typedef struct {
    vector<string> clientesCodigos; 
    map<string, int> mapaCliente;   

    vector<string> produtosNomes;   
    map<string, int> mapaProduto;  

    vector< list<int> > comprasCliente; 
} ListaCompras;

void carregarDados(ListaCompras *dados, const char *nomeArquivo);
void mostrarComprasCliente(ListaCompras *dados, string codigoCliente);

#endif