#include <iostream>
#include <iomanip> // Para formatar as casas decimais
#include "ListaCompras.h"
#include "Similaridade.h"

using namespace std;

int main() {
    ListaCompras dados;
    carregarDados(&dados, "dados_venda.csv");

    cout << "Calculando matrizes... (isso pode demorar se a base for grande)" << endl;
    Matriz A = criarMatrizDensa(&dados);
    Matriz I = calcularIntersecao(&A);
    MatrizSimilaridade S = calcularSimilaridade(&I, &dados);

    string c1, c2;
    cout << "\n--- Teste de Similaridade ---" << endl;
    for(int i = 0; i < 2; i++) {
        cout << "Digite o codigo do Cliente 1: "; cin >> c1;
        cout << "Digite o codigo do Cliente 2: "; cin >> c2;

        if(dados.mapaCliente.count(c1) && dados.mapaCliente.count(c2)) {
            int idx1 = dados.mapaCliente[c1];
            int idx2 = dados.mapaCliente[c2];
            
            cout << "Intersecao (produtos em comum): " << I.valores[idx1][idx2] << endl;
            cout << "Similaridade S(" << c1 << ", " << c2 << "): " 
                 << fixed << setprecision(4) << S.valores[idx1][idx2] << endl;
        } else {
            cout << "Um dos clientes nao foi encontrado!" << endl;
        }
    }

    liberarMatriz(A);
    liberarMatriz(I);
    liberarMatrizSim(S);

    return 0;
}