import sistema_de_recomendacao_py as sr
import time

def main():
    
    arquivo = "dados_venda_cluster_0.csv"
    sr.carregar(arquivo)
    
    tipo = int(input("\nEscolha o tipo de interseção (0-Padrão, 1-Otimizado): "))
    
    inicio = time.time()
    sr.processar(tipo)
    fim = time.time()
    
    print(f"\nProcessamento concluído em {fim - inicio:.4f} segundos!")

    #AT 1: VER COMPRAS 
    print("\nCONSULTA DE COMPRAS")
    for i in range(1, 4):
        cliente = input(f"Digite o código do {i}º cliente para ver compras: ")
        sr.ver_compras(cliente)

    #AT 2 e 4: SIMILARIDADE
    print("\nCONSULTA DE SIMILARIDADE")
    for i in range(1, 3):
        print(f"\nPar {i}:")
        c1 = input("Digite o código do 1º cliente: ")
        c2 = input("Digite o código do 2º cliente: ")
        valor = sr.get_sim(c1, c2)
        if valor >= 0:
            print(f"Similaridade entre {c1} e {c2}: {valor:.4f}")
        else:
            print("Erro: Um ou ambos os clientes não existem.")

    #AT 3: RECOMENDAÇÃO
    print("\nCONSULTA DE RECOMENDAÇÃO")
    for i in range(1, 4):
        cliente = input(f"\nDigite o código do {i}º cliente para recomendação: ")
        k = int(input("Quantas recomendações deseja? "))
        sr.recomendar(cliente, k)


if __name__ == "__main__":
    main()