#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

namespace py = pybind11;

// Variáveis globais que C++ manipula internamente
ListaCompras dados;
Matriz matriz;
Matriz intersecao;
MatrizSimilaridade sim;

// Funções de ponte para o Python chamar
void carregar_python(const std::string& caminho) {
    carregarDados(&dados, caminho.c_str());
}

void criar_matriz_python() {
    matriz = criarMatrizClienteProduto(&dados);
}

void calcular_similaridade_python(bool otimizado) {
    intersecao = multiplica_por_transposta(&matriz, otimizado ? 1 : 0);
    sim = calcularSimilaridade(&intersecao, &dados);
}

void ver_compras_python(const std::string& codigoCliente) {
    mostrarComprasCliente(&dados, codigoCliente);
}

void recomendar_python(const std::string& codigoCliente, int k) {
    mostraRecomendacoes(&dados, &sim, codigoCliente, k);
}

// Funções para o Python obter dados específicos das globais
float pega_similaridade_python(const std::string& c1, const std::string& c2) {
    if (dados.mapaCliente.count(c1) && dados.mapaCliente.count(c2)) {
        int i = dados.mapaCliente[c1];
        int j = dados.mapaCliente[c2];
        return sim.valores[i][j];
    }
    return -1.0f;
}

std::string pega_cliente_codigo_python(int i) {
    if (i >= 0 && i < (int)dados.clienteCodigo.size()) {
        return dados.clienteCodigo[i];
    }
    return "";
}

// Registro do Módulo seguindo o formato do seu exemplo
PYBIND11_MODULE(sistema_de_recomendacao_py, m) {
    m.doc() = "Módulo de Recomendação C++ via Pybind11";

    m.def("carregar", &carregar_python, "Carrega a base de dados", py::arg("caminho"));
    
    m.def("criar_matriz", &criar_matriz_python, "Cria a matriz cliente-produto");
    
    m.def("calcular_similaridade", &calcular_similaridade_python, "Calcula a similaridade", 
          py::arg("otimizado") = true);
    
    m.def("ver_compras", &ver_compras_python, "Mostra compras de um cliente", 
          py::arg("codigo_cliente"));
    
    m.def("recomendar", &recomendar_python, "Mostra recomendações para um cliente", 
          py::arg("codigo_cliente"), py::arg("k"));

    m.def("pega_similaridade", &pega_similaridade_python, "Retorna valor de similaridade entre dois clientes",
          py::arg("c1"), py::arg("c2"));

    m.def("pega_cliente_codigo", &pega_cliente_codigo_python, "Retorna o código do cliente por índice",
          py::arg("i"));
}










import sistema_de_recomendacao_py as sr
import time

def main():
    print("=== Sistema de Recomendação ===")
    
    # 1. Carregar Dados
    arquivo = "dados_venda_cluster_0.csv"
    sr.carregar(arquivo)
    print("\nDados carregados com sucesso!")

    # 2. Configurar e Calcular
    tipo_input = input("\nEscolha o tipo (0-Padrão, 1-Otimizado): ")
    otimizado = True if tipo_input == '1' else False
    
    inicio = time.time()
    sr.criar_matriz()
    sr.calcular_similaridade(otimizado)
    print(f"Tempo de processamento: {time.time() - inicio:.4f}s")

    # 3. Mostrar Compras (Atividade 1)
    print("\n--- Compras de Clientes ---")
    for i in range(3):
        cliente_cod = sr.pega_cliente_codigo(i)
        if cliente_cod:
            sr.ver_compras(cliente_cod)

    # 4. Similaridade (Atividade 2)
    print("\n--- Teste de Similaridade ---")
    c1 = input("Código do primeiro cliente: ")
    c2 = input("Código do segundo cliente: ")
    valor = sr.pega_similaridade(c1, c2)
    print(f"Similaridade entre {c1} e {c2}: {valor:.4f}")

    # 5. Recomendação (Atividade 3)
    print("\n--- Recomendações ---")
    for i in range(3):
        cliente_cod = sr.pega_cliente_codigo(i)
        if cliente_cod:
            try:
                k = int(input(f"Quantas recomendações para {cliente_cod}? "))
                sr.recomendar(cliente_cod, k)
            except ValueError:
                print("Valor inválido.")

if __name__ == "__main__":
    main()