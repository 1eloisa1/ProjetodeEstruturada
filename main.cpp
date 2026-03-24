#include <iostream>
#include <iomanip> 
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

using namespace std;

int main() {
    ListaCompras dados;
    carregarDados(&dados, "dados_venda.csv");

    printf("Calculando matrizes... \n");
    Matriz A = criarMatrizClienteProduto(&dados);
    Matriz I = calcularIntersecao(&A);
    MatrizSimilaridade S = calcularSimilaridade(&I, &dados);


    
    string codigoEntrada;
    
    for (int i = 1; i <= 3; i++) {
        printf("%d/3] Digite o codigo original do cliente: ", i);
        cin >> codigoEntrada;
        mostrarComprasCliente(&dados, codigoEntrada);
    }


    string c1, c2;
    printf("\n Teste de Similaridade \n");
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


     for (int i = 1; i <= 3; i++) {
        printf("%d/3] Digite o codigo original do cliente: ", i);
        cin >> codigoEntrada;
        mostraRecomendacoes(&dados, &S, codigoEntrada);
    }

    
    liberarMatriz(A);
    liberarMatriz(I);
    liberarMatrizSim(S);

    return 0;
}
