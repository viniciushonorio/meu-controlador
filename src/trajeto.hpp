#ifndef TRAJETO_HPP
#define TRAJETO_HPP

#include "Cidade.hpp"

/**
 * Representa um trajeto direcionado entre duas cidades.
 * tipo: 'A' para Aquático, 'T' para Terrestre.
 * Um transporte só pode usar trajetos do mesmo tipo que ele.
 */
class Trajeto {
private:
    Cidade* origem;
    Cidade* destino;
    char tipo;      // 'A' = Aquático, 'T' = Terrestre
    int distancia;  // em km

public:
    Trajeto(Cidade* origem, Cidade* destino, char tipo, int distancia);

    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    char getTipo() const;
    int getDistancia() const;
};

#endif
