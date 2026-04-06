import csv
import os
import time
import Sistema_de_Recomendacao_py

def main():
     #att 1
    if Sistema_de_Recomendacao_py.carregado("dados_venda_inicial/dados_venda.csv"):   
        print("Arquivo carregado\n")


    #if not os.path.exists(arquivo):
        print(f"Erro: O arquivo '{arquivo}' nao foi encontrado.")
        return
    
    dados_csv = []
    with open(arquivo, mode='r', encoding='utf-8') as file:
        leitor = csv.reader(file)

        next(leitor) 

        for linha in leitor:
            dados_csv.append(linha)


#att 2 e 4
    print("Calculando matrizes... \n");

    print("Escolha como vai executar o teste: ");
    print("1. Usar o algoritimo padrao | 2. Usar o algoritmo adaptado");
    escolha = int(input("Digite sua escolha: "));

    inicio = time.time();

    if (escolha == 2) {
        print("Calculando via Adaptado...\n");
        I = Sistema_de_Recomendacao_py.multiplica_por_transposta(&A);
    } else {
        print("Calculando via Padrao...\n");
        Matriz At = Sistema_de_Recomendacao_py.calculaTransposta(&A);
        I = Sistema_de_Recomendacao_py.calcularIntersecao(&A, &At);
        Sistema_de_Recomendacao_py.liberarMatriz(At);
    }

    fim = time.time()
    tempo = fim - inicio
    print(f"Tempo de processamento: {tempo:.4f} segundos\n", tempo);


#att  1 
    for i in range(3):
        print(f"[{i+1}/3] Digite o codigo original do cliente: ", end="")
        codigoEntrada = input()
        compras = Sistema_de_Recomendacao_py.mostrarComprasCliente(codigoEntrada)

        if not compras:
            print("Cliente não encontrado.")
            continue

        print(f"Compras do cliente {codigoEntrada}:")
        for produto in compras:
            print(f"  - {produto}")


        MatrizSimilaridade S = Sistema_de_Recomendacao_py.calcularSimilaridade(&I, &dados);
        string codigoEntrada;
    


#att 4
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
    

#att 3
        print("\n Recomendacoes \n");
        for i in range(3):
            print("[%d/3] Digite o codigo original do cliente: ", i+1);
            codigoEntrada = input();
            Sistema_de_Recomendacao_py.mostraRecomendacoes(codigoEntrada, &dados, &S);


        Sistema_de_Recomendacao_py.liberarMatriz(A);
        Sistema_de_Recomendacao_py.liberarMatriz(I);
        Sistema_de_Recomendacao_py.liberarMatrizSim(S);


}
if __name__ == "__main__":
    main()