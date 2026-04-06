import csv
import os

# Estrutura: { 'cod_cliente': ['Produto A', 'Produto B'] }
mapa_compras = {}

def carregar_dados(arquivo):
    if os.path.exists(arquivo):
        with open(arquivo, mode='r', encoding='utf-8') as f:
            leitor = csv.DictReader(f)
            
            for linha in leitor:
                cod_cliente = linha['COD_CLIENTE']

                nome_produto = linha['NOME_PRODUTO']
                
                if cod_cliente not in mapa_compras:
                    mapa_compras[cod_cliente] = []
                
                mapa_compras[cod_cliente].append(nome_produto)
    else:
        print(f"Erro: O arquivo '{arquivo}' nao foi encontrado.")

def mostrar_compras_cliente(codigo_cliente):
    if codigo_cliente in mapa_compras:
        print(f"Historico de compras do cliente {codigo_cliente}:")
        for produto in mapa_compras[codigo_cliente]:
            print(f" - {produto}")
    else:
        print(f"Erro: Cliente {codigo_cliente} nao encontrado.")
