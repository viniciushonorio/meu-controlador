#ifndef CONTROLADOR_DE_TRANSITO_HPP
#define CONTROLADOR_DE_TRANSITO_HPP

#include <string>
#include <vector>
#include "Cidade.hpp"

class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    Cidade* buscarCidade(const std::string& nome);

public:
    bool cadastrarCidade(const std::string& nome);
};

#endif