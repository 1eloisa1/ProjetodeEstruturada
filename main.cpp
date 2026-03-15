#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"

using namespace std;

int main(){

    ListaCompras dados;

    carregarDados(&dados,"dados_venda_cluster_2.csv");

    string cliente;

    for(int i=0;i<3;i++){

        cout << "Digite o codigo do cliente: ";
        cin >> cliente;

        mostrarComprasCliente(&dados,cliente);

        cout << endl;
    }

    return 0;
}