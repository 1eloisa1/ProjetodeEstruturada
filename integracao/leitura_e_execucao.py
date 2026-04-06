import csv
import os
import time
import meu_solver

def main():
    arquivo = 'dados_venda.csv'

    if not os.path.exists(arquivo):
        print(f"Erro: O arquivo '{arquivo}' nao foi encontrado.")
        return
    
    dados_csv = []
    with open(arquivo, mode='r', encoding='utf-8') as file:
        leitor = csv.reader(file)

        next(leitor) 

        for linha in leitor:
            dados_csv.append(linha)

    print("Calculando matrizes... \n");
   

    print("Escolha como vai executar o teste: ");
    print("1. Usar o algoritimo padrao | 2. Usar o algoritmo adaptado");
    escolha = int(input("Digite sua escolha: "));

    inicio = time.time();

    if (escolha == 2) {
        print("Calculando via Adaptado...\n");
        I = multiplica_por_transposta(&A);
    } else {
        print("Calculando via Padrao...\n");
        Matriz At = calculaTransposta(&A);
        I = calcularIntersecao(&A, &At);
        liberarMatriz(At);
    }

    fim = time.time()
    tempo = fim - inicio
    print(f"Tempo de processamento: {tempo:.4f} segundos\n", tempo);

    for i in range(3):
        print(f"[{i+1}/3] Digite o codigo original do cliente: ", end="")
        codigoEntrada = input()
        mostrarComprasCliente(&dados, codigoEntrada)
    

    MatrizSimilaridade S = calcularSimilaridade(&I, &dados);
    string codigoEntrada;
    


    print("\n Teste de Similaridade \n");
    for i in range(2):
        c1 = input("Digite o codigo do Cliente 1: ");
        c2 = input("Digite o codigo do Cliente 2: ");

        if(c1 == c2) {
            print("Os clientes sao os mesmos!");
            continue;
        }
        if(dados.mapaCliente.count(c1) and dados.mapaCliente.count(c2)):
            idx1 = dados.mapaCliente[c1];
            idx2 = dados.mapaCliente[c2];
            print("Intersecao (produtos em comum): %d", I.valores[idx1][idx2]);
            print("Similaridade S(%s, %s): %.4f", c1.c_str(), c2.c_str(), S.valores[idx1][idx2]);
    
        else:
            print("Um dos clientes nao foi encontrado!");
    


        print("\n Recomendacoes \n");
        for i in range(3):
            print("[%d/3] Digite o codigo original do cliente: ", i+1);
            codigoEntrada = input();
            mostraRecomendacoes(&dados, &S, codigoEntrada);


        liberarMatriz(A);
        liberarMatriz(I);
        liberarMatrizSim(S);


}
if __name__ == "__main__":
    main()