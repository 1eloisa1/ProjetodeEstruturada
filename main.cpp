#include <stdio.h>
#include <iostream>
#include "ListaCompras.h"

using namespace std;

int main() {
    ListaCompras dados;

    // Use o nome exato do seu arquivo aqui
    carregarDados(&dados, "dados_venda.csv");

    string cliente;
    // Teste com 3 clientes
    for (int i = 0; i < 3; i++) {
        cout << "\nDigite o codigo do cliente (ex: 99CL9Y01): ";
        cin >> cliente;

        mostrarComprasCliente(&dados, cliente);
        cout << "------------------------------------------" << endl;
    }

    return 0;
}