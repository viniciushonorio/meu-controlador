#ifndef CONTROLADOR_DE_TRANSITO_HPP
#define CONTROLADOR_DE_TRANSITO_HPP

#include <string>
#include <vector>
#include "Cidade.hpp"
#include "Passageiro.hpp"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Passageiro*> passageiros;

    Cidade* buscarCidade(const std::string& nome);
    Passageiro* buscarPassageiro(const std::string& nome);

public:
    bool cadastrarCidade(const std::string& nome);
    bool cadastrarPassageiro(const std::string& nome, const std::string& nomeLocalAtual);
};

#endif