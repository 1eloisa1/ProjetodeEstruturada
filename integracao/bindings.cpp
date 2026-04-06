import csv
import os
import time
import meu_solver  # O módulo que você compilou [cite: 78, 97]

def main():
    arquivo_csv = 'dados_venda.csv'

    if not os.path.exists(arquivo_csv):
        print(f"Erro: O arquivo '{arquivo_csv}' nao foi encontrado.")
        return
    
    dados_csv = []
    with open(arquivo_csv, mode='r', encoding='utf-8') as f:
        leitor = csv.reader(f)
        next(leitor)  # Pula o cabeçalho [cite: 69]
        for linha in leitor:
            dados_csv.append(linha)

    print("Calculando matrizes... \n")
    
    print("Escolha como vai executar o teste: ")
    print("1. Usar o algoritimo padrao | 2. Usar o algoritmo adaptado")
    escolha = int(input("Digite sua escolha: "))

    inicio = time.time()

    # O processamento pesado de matrizes deve acontecer dentro de uma 
    # única função no C++ para garantir o desempenho. [cite: 11, 82]
    # No seu solver.cpp, você deve ter uma função que orquestra isso.
    if escolha == 2:
        print("Calculando via Adaptado no C++...\n")
        # meu_solver.executar_processamento(dados_csv, tipo=2)
    else:
        print("Calculando via Padrao no C++...\n")
        # meu_solver.executar_processamento(dados_csv, tipo=1)

    fim = time.time()
    tempo = fim - inicio
    print(f"Tempo de processamento: {tempo:.4f} segundos\n")

    # Histórico de compras
    for i in range(3):
        print(f"[{i+1}/3] Digite o codigo original do cliente para ver historico: ", end="")
        codigoEntrada = input()
        # Chama a função C++ exposta via binding [cite: 118]
        # meu_solver.mostrar_compras(codigoEntrada, dados_csv)
    
    print("\n Teste de Similaridade \n")
    for i in range(2):
        c1 = input("Digite o codigo do Cliente 1: ")
        c2 = input("Digite o codigo do Cliente 2: ")

        if c1 == c2:
            print("Os clientes sao os mesmos!")
            continue
        
        # A lógica de busca no mapaCliente e acesso aos valores da matriz 
        # deve ser feita por uma função no seu solver.cpp [cite: 151]
        # resultado = meu_solver.obter_similaridade(c1, c2)
        # print(f"Similaridade S({c1}, {c2}): {resultado}")

    print("\n Recomendacoes \n")
    for i in range(3):
        print(f"[{i+1}/3] Digite o codigo original do cliente para RECOMENDACAO: ", end="")
        codigoEntrada = input()
        # Esta é a chamada que executa a sua lógica de recomendação em C++ [cite: 219]
        meu_solver.recomendar(id_alvo=codigoEntrada, dados_csv=dados_csv)

    # Nota: A limpeza de memória (liberarMatriz) deve ser feita AUTOMATICAMENTE 
    # dentro das funções do seu solver.cpp ao final da execução. [cite: 13, 83]

if __name__ == "__main__":
    main()