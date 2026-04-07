import sistema_de_recomendacao_py as sr

def main():
    print("=== Sistema de Recomendação ===")

    # Cria estrutura de dados
    dados = sr.ListaCompras()

    # Carrega o CSV
    arquivo = "dados_venda_cluster_0.csv"
    sr.carregarDados(dados, arquivo)

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

    print("\n=== PRODUTOS DE 3 CLIENTES ===")

    for i in range(3):
        cliente = dados.clienteCodigo[i]
        print(f"\nCliente {cliente}:")
        sr.mostrarComprasCliente(dados, cliente)

    print("\n=== SIMILARIDADE DE 2 PARES ===")

    for i in range(2):
        c1 = input("\nDigite o código do primeiro cliente: ")
        c2 = input("Digite o código do segundo cliente: ")

        idx1 = dados.mapaCliente[c1]
        idx2 = dados.mapaCliente[c2]

        valor = similaridade.valores[idx1][idx2]

        print(f"{c1} x {c2} = {valor}")


    print("\n=== RECOMENDAÇÕES PARA 3 CLIENTES ===")

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