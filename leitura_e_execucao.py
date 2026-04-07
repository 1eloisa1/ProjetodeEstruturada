import sistema_de_recomendacao_py as sr

def main():
    print("=== Sistema de Recomendação ===")

    # Cria estrutura de dados
    dados = sr.ListaCompras()

    # Carrega o CSV
    arquivo = "dados_venda_cluster_0.csv"
    sr.carregarDados(arquivo)

    print("\nDados carregados com sucesso!")

    print("\nEscolha o tipo de transposição:")
    print("0 - Padrão")
    print("1 - Otimizado")

    try:
        tipo = int(input(">> "))
        if tipo not in [0, 1]:
            print("Valor inválido! Usando padrão (0)")
            tipo = 0
    except:
        print("Valor inválido! Usando padrão (0)")
        tipo = 0

    # Criar matriz cliente-produto
    matriz = sr.criarMatrizClienteProduto(dados)

    # Calcular interseção
    intersecao = sr.multiplica_por_transposta(matriz, tipo)

    # Calcular similaridade
    similaridade = sr.calcularSimilaridade(intersecao, dados)

    #mostra clientes da atividade 1

    for i in range(3):
        cliente = dados.clienteCodigo[i]
        print(f"\nCliente {cliente}:")
        sr.mostrarComprasCliente(dados, cliente)

    #similaridade da atividade 2

    for i in range(2):
        c1 = input("\nDigite o código do primeiro cliente: ")
        c2 = input("Digite o código do segundo cliente: ")

        idx1 = dados.mapaCliente[c1]
        idx2 = dados.mapaCliente[c2]

        valor = similaridade.valores[idx1][idx2]

        print(f"{c1} x {c2} = {valor}")


   #recomendação da atividade 3

    for i in range(3):
        cliente = dados.clienteCodigo[i]

        print(f"\nCliente {cliente}")
        try:
            k = int(input("Quantas recomendações deseja? "))
        except:
            print("Valor inválido! Usando k = 3")
            k = 3

        print(f"Recomendações para {cliente}:")
        sr.mostraRecomendacoes(dados, similaridade, cliente, k)


if __name__ == "__main__":
    main()