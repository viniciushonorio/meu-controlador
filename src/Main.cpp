#include <iostream>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"

int main() {
    // Cidades
    Cidade natal("Natal");
    Cidade mossoro("Mossoro");

    // Transporte terrestre comecando em Natal
    // (nome, tipo, capacidade, velocidade, distEntreDescansos, tempoDescanso, local)
    Transporte onibus("Onibus Expresso", 'T', 40, 70, 300, 2, &natal);

    std::cout << "Transporte: " << onibus.getNome()
              << " | tipo: " << onibus.getTipo()
              << " | capacidade: " << onibus.getCapacidade()
              << " | velocidade: " << onibus.getVelocidade() << " km/h\n";
    std::cout << "Descansa " << onibus.getTempoDescanso()
              << "h a cada " << onibus.getDistanciaEntreDescansos() << " km\n";
    std::cout << "Local atual: " << onibus.getLocalAtual()->getNome() << "\n";

    // Simula o efeito de uma viagem: o transporte muda de cidade
    onibus.setLocalAtual(&mossoro);
    std::cout << "Apos viajar, local atual: "
              << onibus.getLocalAtual()->getNome() << "\n";

    return 0;
}