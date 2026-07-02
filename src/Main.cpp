#include <iostream>
#include <string>
#include "ControladorDeTransito.hpp"

int main() {
    ControladorDeTransito controlador;
    bool executando = true;

    while (executando) {
        std::cout << "\n=== CONTROLADOR DE VIAGENS ===\n"
                  << "1 - Cadastrar cidade\n"
                  << "2 - Cadastrar Passageiro\n"
                  << "0 - Sair\n"
                  << "Escolha: ";

        std::string opcao;
        std::getline(std::cin, opcao);

        if (opcao == "1") {
            std::cout << "Nome da cidade: ";
            std::string nome;
            std::getline(std::cin, nome);
            controlador.cadastrarCidade(nome);
        } else if (opcao == "2") {
            std::cout << "Nome do passageiro: ";
            std::string nome;
            std::getline(std::cin, nome);

            std::cout << "Cidade onde o passageiro esta: ";
            std::string cidade;
            std::getline(std::cin, cidade);

            controlador.cadastrarPassageiro(nome, cidade);
        } else if (opcao == "0") {
            executando = false;
        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
    return 0;
}