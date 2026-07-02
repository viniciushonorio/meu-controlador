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

Passageiro* ControladorDeTransito::buscarPassageiro(const std::string& nome) {
    for (Passageiro* p : passageiros)
        if (p->getNome() == nome) return p;
    return nullptr;
}

// ------------------------------------------------------------------
// Cadastros
// ------------------------------------------------------------------

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

bool ControladorDeTransito::cadastrarPassageiro(const std::string& nome,
                                                const std::string& nomeLocalAtual) {
    if (nome.empty()) {
        std::cout << "[ERRO] O nome do passageiro nao pode ser vazio.\n";
        return false;
    }
    if (buscarPassageiro(nome) != nullptr) {
        std::cout << "[ERRO] Ja existe um passageiro com o nome \"" << nome << "\".\n";
        return false;
    }
    Cidade* local = buscarCidade(nomeLocalAtual);
    if (local == nullptr) {
        std::cout << "[ERRO] Cidade \"" << nomeLocalAtual << "\" nao encontrada.\n";
        return false;
    }

    passageiros.push_back(new Passageiro(nome, local));
    std::cout << "Passageiro \"" << nome << "\" cadastrado com sucesso em "
              << nomeLocalAtual << ".\n";
    return true;
}