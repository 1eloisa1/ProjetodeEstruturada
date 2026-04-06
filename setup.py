from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "sistema_de_recomendacao_py", 
        [
            "converter.cpp", 
            "ListaCompras.cpp", 
            "Recomendacao.cpp", 
            "Similaridade.cpp"
        ],
    ),
]

setup(
    name="sistema_de_recomendacao_py",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)