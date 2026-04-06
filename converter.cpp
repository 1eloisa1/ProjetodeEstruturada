#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "ListaCompras.h"
#include "Similaridade.h"
#include "Recomendacao.h"

namespace py = pybind11;

PYBIND11_MODULE(sistema_de_recomendacao_py, m) {
    m.doc() = "Sistema de recomendacao em C++ integrado com Python";

    // =========================
    // Classe ListaCompras
    // =========================
    py::class_<ListaCompras>(m, "ListaCompras")
        .def(py::init<>());

    // =========================
    // Estruturas de Matriz
    // =========================
    py::class_<Matriz>(m, "Matriz")
        .def(py::init<>());

    py::class_<MatrizSimilaridade>(m, "MatrizSimilaridade")
        .def(py::init<>());

    // =========================
    // Funções expostas
    // =========================

    m.def("carregarDados", &carregarDados, 
        py::arg("dados"), py::arg("nomeArquivo"));

    m.def("criarMatrizClienteProduto", &criarMatrizClienteProduto,
        py::arg("dados"));

    m.def("multiplica_por_transposta", &multiplica_por_transposta,
        py::arg("matriz"));

    m.def("calcularSimilaridade", &calcularSimilaridade,
        py::arg("intersecao"), py::arg("dados"));

    m.def("mostraRecomendacoes", &mostraRecomendacoes,
        py::arg("dados"),
        py::arg("similaridade"),
        py::arg("codigoCliente"),
        py::arg("k"));
}