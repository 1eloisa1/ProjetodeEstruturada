#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

double soma(double a, double b) {
    return a + b;
}

PYBIND11_MODULE(meu_modulo, m) {
    m.doc() = "Exemplo de integração";
    m.def("soma", &soma, "Função que soma dois números");
}

