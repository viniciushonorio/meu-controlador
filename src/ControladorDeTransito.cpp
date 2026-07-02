#include "ControladorDeTransito.hpp"
#include <iostream>

// ------------------------------------------------------------------
// Buscas auxiliares
// ------------------------------------------------------------------

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

Transporte* ControladorDeTransito::buscarTransporte(const std::string& nome) {
    for (Transporte* t : transportes)
        if (t->getNome() == nome) return t;
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

bool ControladorDeTransito::cadastrarTransporte(const std::string& nome, char tipo,
                                                int capacidade, int velocidade,
                                                int distanciaEntreDescansos,
                                                int tempoDescanso,
                                                const std::string& nomeLocalAtual) {
    if (nome.empty()) {
        std::cout << "[ERRO] O nome do transporte nao pode ser vazio.\n";
        return false;
    }
    if (buscarTransporte(nome) != nullptr) {
        std::cout << "[ERRO] Ja existe um transporte com o nome \"" << nome << "\".\n";
        return false;
    }
    if (tipo != 'A' && tipo != 'T') {
        std::cout << "[ERRO] Tipo de transporte invalido. Use 'A' (Aquatico) ou 'T' (Terrestre).\n";
        return false;
    }
    if (capacidade <= 0 || velocidade <= 0) {
        std::cout << "[ERRO] Capacidade e velocidade devem ser maiores que zero.\n";
        return false;
    }
    if (distanciaEntreDescansos < 0 || tempoDescanso < 0) {
        std::cout << "[ERRO] Distancia entre descansos e tempo de descanso nao podem ser negativos.\n";
        return false;
    }
    Cidade* local = buscarCidade(nomeLocalAtual);
    if (local == nullptr) {
        std::cout << "[ERRO] Cidade \"" << nomeLocalAtual << "\" nao encontrada.\n";
        return false;
    }

    transportes.push_back(new Transporte(nome, tipo, capacidade, velocidade,
                                         distanciaEntreDescansos, tempoDescanso, local));
    std::cout << "Transporte \"" << nome << "\" cadastrado com sucesso em "
              << nomeLocalAtual << ".\n";
    return true;
}

bool ControladorDeTransito::cadastrarTrajeto(const std::string& nomeOrigem,
                                             const std::string& nomeDestino,
                                             char tipo, int distancia) {
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);

    if (origem == nullptr) {
        std::cout << "[ERRO] Cidade de origem \"" << nomeOrigem << "\" nao encontrada.\n";
        return false;
    }
    if (destino == nullptr) {
        std::cout << "[ERRO] Cidade de destino \"" << nomeDestino << "\" nao encontrada.\n";
        return false;
    }
    if (origem == destino) {
        std::cout << "[ERRO] Origem e destino devem ser cidades diferentes.\n";
        return false;
    }
    if (tipo != 'A' && tipo != 'T') {
        std::cout << "[ERRO] Tipo de trajeto invalido. Use 'A' (Aquatico) ou 'T' (Terrestre).\n";
        return false;
    }
    if (distancia <= 0) {
        std::cout << "[ERRO] A distancia deve ser maior que zero.\n";
        return false;
    }

    trajetos.push_back(new Trajeto(origem, destino, tipo, distancia));
    std::cout << "Trajeto " << nomeOrigem << " -> " << nomeDestino
              << " (" << (tipo == 'A' ? "Aquatico" : "Terrestre")
              << ", " << distancia << " km) cadastrado com sucesso.\n";
    return true;
}