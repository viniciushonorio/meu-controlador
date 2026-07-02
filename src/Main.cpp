#include <iostream>
#include <string>
#include "ControladorDeTransito.hpp"

int main() {
    ControladorDeTransito controlador;
    bool executando = true;

    while (executando) {
        std::cout << "\n=== CONTROLADOR DE VIAGENS ===\n"
                  << "1 - Cadastrar cidade\n"
                  << "0 - Sair\n"
                  << "Escolha: ";

        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "1") {
            std::cout << "Nome da cidade: ";
            std::string nome;
            std::getline(std::cin, nome);
            controlador.cadastrarCidade(nome);
        } else if (opcao == "0") {
            executando = false;
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
    return 0;
}