#ifndef PASSAGEIRO_HPP
#define PASSAGEIRO_HPP

#include <string>
#include "Cidade.hpp"

/**
 * Representa um passageiro cadastrado no sistema.
 * Assim como o transporte, o localAtual só muda quando a viagem
 * final de uma cadeia de conexões é concluída.
 */
class Passageiro {
private:
    std::string nome;
    Cidade* localAtual;

public:
    Passageiro(std::string nome, Cidade* localAtual);

    std::string getNome() const;
    Cidade* getLocalAtual() const;

    void setLocalAtual(Cidade* local);
};

#endif