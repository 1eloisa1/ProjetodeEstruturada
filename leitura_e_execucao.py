import sistema_de_recomendacao_py as sr

def main():
    print("=== Sistema de Recomendação ===")

    # Cria estrutura de dados
    dados = sr.ListaCompras()

    # Carrega o CSV
    arquivo = "dados_venda_cluster_0.csv"
    sr.carregarDados(dados, arquivo)

    print("\nDados carregados com sucesso!")

    # Criar matriz cliente-produto
    matriz = sr.criarMatrizClienteProduto(dados)

    # Calcular interseção
    intersecao = sr.multiplica_por_transposta(matriz)

    # Calcular similaridade
    similaridade = sr.calcularSimilaridade(intersecao, dados)

    while True:
        print("\nDigite o código do cliente (ou 'sair'):")
        cliente = input(">> ")

        if cliente.lower() == "sair":
            break

        print("\nQuantas recomendações deseja?")
        try:
            k = int(input(">> "))
        except:
            print("Valor inválido!")
            continue

        # Mostrar recomendações
        sr.mostraRecomendacoes(dados, similaridade, cliente, k)

    print("\nEncerrando sistema...")

if __name__ == "__main__":
    main()