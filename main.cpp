#include <iostream>
#include <iomanip> 
#include <ctime>
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

using namespace std;

int main() {
    ListaCompras dados;
    carregarDados(&dados, "dados_venda.csv");

    printf("Calculando matrizes... \n");
    Matriz A = criarMatrizClienteProduto(&dados);
    Matriz I;

    int escolha;
    cout << "Escolha como vai executar o teste: " << endl;
        cout << "1. Usar o algoritimo padrao | 2. Usar o algoritmo adaptado" << endl;
        cin >> escolha;

    clock_t t_ini = clock();

    if (escolha == 2) {
        printf("Calculando via Adaptado...\n");
        I = multiplica_por_transposta(&A);
    } else {
        printf("Calculando via Padrao...\n");
        Matriz At = calculaTransposta(&A);
        I = calcularIntersecao(&A, &At);
        liberarMatriz(At);
    }

    clock_t t_fim = clock();
    double tempo = (double)(t_fim - t_ini) / CLOCKS_PER_SEC;
    printf("Tempo de processamento: %.4f segundos\n", tempo);
    

    MatrizSimilaridade S = calcularSimilaridade(&I, &dados);
    string codigoEntrada;
    
    for (int i = 1; i <= 3; i++) {
        printf("[%d/3] Digite o codigo original do cliente: ", i);
        cin >> codigoEntrada;
        mostrarComprasCliente(&dados, codigoEntrada);
    }

    printf("\n Teste de Similaridade \n");
    for(int i = 0; i < 2; i++) {
        string c1, c2;
        cout << "Digite o codigo do Cliente 1: "; cin >> c1;
        cout << "Digite o codigo do Cliente 2: "; cin >> c2;

        if(c1 == c2) {
            cout << "Os clientes sao os mesmos!" << endl;
        continue;
    }
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

        printf("\n Recomendacoes \n");
        for (int i = 1; i <= 3; i++) {
            printf("[%d/3] Digite o codigo original do cliente: ", i);
            cin >> codigoEntrada;
            mostraRecomendacoes(&dados, &S, codigoEntrada);
}


        liberarMatriz(A);
        liberarMatriz(I);
        liberarMatrizSim(S);

        

    return 0;
}
