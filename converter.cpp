#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

namespace py = pybind11;

// Variáveis globais no C++ (o estado do sistema)
ListaCompras dados;
Matriz matriz;
Matriz intersecao;
MatrizSimilaridade sim;

void carregar_python(std::string caminho) {
    carregarDados(&dados, caminho.c_str());
}

// Essa é a parte que vamos cronometrar no Python
void processar_sistema_python(int tipo) {
    matriz = criarMatrizClienteProduto(&dados);
    intersecao = multiplica_por_transposta(&matriz, tipo);
    sim = calcularSimilaridade(&intersecao, &dados);
}

void mostrar_compras_python(std::string cliente) {
    mostrarComprasCliente(&dados, cliente);
}

float pegar_similaridade_python(std::string c1, std::string c2) {
    if (dados.mapaCliente.count(c1) && dados.mapaCliente.count(c2)) {
        return sim.valores[dados.mapaCliente[c1]][dados.mapaCliente[c2]];
    }
    return -1.0f;
}

void recomendar_python(std::string cliente, int k) {
    mostraRecomendacoes(&dados, &sim, cliente, k);
}

PYBIND11_MODULE(sistema_de_recomendacao_py, m) {
    m.def("carregar", &carregar_python);
    m.def("processar", &processar_sistema_python);
    m.def("ver_compras", &mostrar_compras_python);
    m.def("get_sim", &pegar_similaridade_python);
    m.def("recomendar", &recomendar_python);
}