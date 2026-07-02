#include <iostream>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"

int main() {
    // Cidades (os objetos "originais" pra onde todos vão apontar)
    Cidade natal("Natal");
    Cidade mossoro("Mossoro");

    // Trajeto terrestre de Natal a Mossoro
    Trajeto t(&natal, &mossoro, 'T', 280);

    std::cout << "Trajeto: "
              << t.getOrigem()->getNome()
              << " -> "
              << t.getDestino()->getNome()
              << " | tipo: " << t.getTipo()
              << " | distancia: " << t.getDistancia() << " km\n";

    return 0;
}