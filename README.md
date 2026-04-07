#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

namespace py = pybind11;

ListaCompras dados;
Matriz matriz;
Matriz intersecao;
MatrizSimilaridade sim;

void carregar(string caminho) {
    carregarDados(&dados, caminho.c_str());
}

void criar_matriz() {
    matriz = criarMatrizClienteProduto(&dados);
}

void calcular(bool otimizado) {
    intersecao = multiplica_por_transposta(&matriz, otimizado ? 1 : 0);
    sim = calcularSimilaridade(&intersecao, &dados);
}

void recomendar(string cliente, int k) {
    mostraRecomendacoes(&dados, &sim, cliente, k);
}

void compras(string cliente) {
    mostrarComprasCliente(&dados, cliente);
}

int similar(int cliente) {
    return clienteMaisSimilar(&sim, cliente);
}

PYBIND11_MODULE(sistema_de_recomendacao_py, m) {
    m.def("carregar", &carregar);
    m.def("criar_matriz", &criar_matriz);
    m.def("calcular", &calcular);
    m.def("recomendar", &recomendar);
    m.def("compras", &compras);
    m.def("similar", &similar);
}