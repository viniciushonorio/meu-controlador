#include "ControladorDeTransito.hpp"
#include <iostream>

Cidade* ControladorDeTransito::buscarCidade(const std::string& nome) {
    for (Cidade* c : cidades) {
        if (c->getNome() == nome) {
            return c;
        }
    }
    return nullptr;
}

bool ControladorDeTransito::cadastrarCidade(const std::string& nome) {
    if (nome.empty()) {
        std::cout << "[ERRO] O nome da cidade nao pode ser vazio.\n";
        return false;
    }
    if (buscarCidade(nome) != nullptr) {
        std::cout << "[ERRO] Ja existe uma cidade com esse nome.\n";
        return false;
    }

    cidades.push_back(new Cidade(nome));

    std::cout << "Cidade \"" << nome << "\" cadastrada com sucesso.\n";
    return true;
}