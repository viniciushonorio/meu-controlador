#include <iostream>
#include <string>
#include "ControladorDeTransito.hpp"

// Le uma linha de texto com uma mensagem antes
std::string lerLinha(const std::string& mensagem) {
    std::cout << mensagem;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// Le um numero inteiro
int lerInteiro(const std::string& mensagem) {
    return std::stoi(lerLinha(mensagem));
}

int main() {
    ControladorDeTransito controlador;
    bool executando = true;

    while (executando) {
        std::cout << "\n=== CONTROLADOR DE VIAGENS ===\n"
                  << "1 - Cadastrar cidade\n"
                  << "2 - Cadastrar passageiro\n"
                  << "3 - Cadastrar trajeto\n"
                  << "4 - Cadastrar transporte\n"
                  << "0 - Sair\n";
        std::string opcao = lerLinha("Escolha: ");

        if (opcao == "1") {
            controlador.cadastrarCidade(lerLinha("Nome da cidade: "));

        } else if (opcao == "2") {
            std::string nome = lerLinha("Nome do passageiro: ");
            std::string cidade = lerLinha("Cidade onde ele esta: ");
            controlador.cadastrarPassageiro(nome, cidade);

        } else if (opcao == "3") {
            std::string origem = lerLinha("Cidade de origem: ");
            std::string destino = lerLinha("Cidade de destino: ");
            char tipo = lerLinha("Tipo (A = Aquatico, T = Terrestre): ")[0];
            int distancia = lerInteiro("Distancia (km): ");
            controlador.cadastrarTrajeto(origem, destino, tipo, distancia);

        } else if (opcao == "4") {
            std::string nome = lerLinha("Nome do transporte: ");
            char tipo = lerLinha("Tipo (A = Aquatico, T = Terrestre): ")[0];
            int capacidade = lerInteiro("Capacidade de passageiros: ");
            int velocidade = lerInteiro("Velocidade (km/h): ");
            int distDescanso = lerInteiro("Distancia entre descansos (km): ");
            int tempoDescanso = lerInteiro("Tempo de descanso (horas): ");
            std::string local = lerLinha("Cidade onde ele esta: ");
            controlador.cadastrarTransporte(nome, tipo, capacidade, velocidade,
                                            distDescanso, tempoDescanso, local);

        } else if (opcao == "0") {
            executando = false;

        } else {
            std::cout << "Opcao invalida.\n";
        }
    }
    return 0;
}