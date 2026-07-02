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

Viagem* ControladorDeTransito::viagemAtivaDoPassageiro(Passageiro* p) {
    for (Viagem* v : viagens) {
        if (v->isFinalizada()) continue;   
        for (Passageiro* px : v->getPassageiros()) {
            if (px == p) return v;        
        }
    }
    return nullptr;
}

Viagem* ControladorDeTransito::viagemAtivaDoTransporte(Transporte* t) {
    for (Viagem* v : viagens)
        if (!v->isFinalizada() && v->getTransporte() == t) return v;
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

// ------------------------------------------------------------------
// Gestão de viagens
// ------------------------------------------------------------------

bool ControladorDeTransito::iniciarViagem(const std::string& nomeTransporte,
                                          const std::vector<std::string>& nomesPassageiros,
                                          const std::string& nomeOrigem,
                                          const std::string& nomeDestino) {
    // --- Validações básicas ---
    Cidade* origem = buscarCidade(nomeOrigem);
    Cidade* destino = buscarCidade(nomeDestino);
    Transporte* transporte = buscarTransporte(nomeTransporte);

    if (origem == nullptr) {
        std::cout << "[ERRO] Cidade de origem \"" << nomeOrigem << "\" nao encontrada.\n";
        return false;
    }
    if (destino == nullptr) {
        std::cout << "[ERRO] Cidade de destino \"" << nomeDestino << "\" nao encontrada.\n";
        return false;
    }
    if (origem == destino) {
        std::cout << "[ERRO] Origem e destino devem ser diferentes.\n";
        return false;
    }
    if (transporte == nullptr) {
        std::cout << "[ERRO] Transporte \"" << nomeTransporte << "\" nao encontrado.\n";
        return false;
    }

    if (viagemAtivaDoTransporte(transporte) != nullptr) {
        std::cout << "[ERRO] O transporte \"" << nomeTransporte  << "\" ja esta em uma viagem em andamento.\n";
        return false;
    }

    if (transporte->getLocalAtual() != origem) {
        std::cout << "[ERRO] O transporte \"" << nomeTransporte
                  << "\" nao esta na cidade de origem (esta em "
                  << transporte->getLocalAtual()->getNome() << ").\n";
        return false;
    }

    // --- Valida os passageiros ---
    if (nomesPassageiros.empty()) {
        std::cout << "[ERRO] A viagem deve ter pelo menos um passageiro.\n";
        return false;
    }
    if ((int)nomesPassageiros.size() > transporte->getCapacidade()) {
        std::cout << "[ERRO] O transporte comporta no maximo "
                  << transporte->getCapacidade() << " passageiros.\n";
        return false;
    }

    std::vector<Passageiro*> listaPassageiros;
    for (const std::string& nome : nomesPassageiros) {
        Passageiro* p = buscarPassageiro(nome);
        if (p == nullptr) {
            std::cout << "[ERRO] Passageiro \"" << nome << "\" nao encontrado.\n";
            return false;
        }
        if (viagemAtivaDoPassageiro(p) != nullptr) {
            std::cout << "[ERRO] O passageiro \"" << nome << "\" ja esta em uma viagem em andamento.\n";
            return false;
        }
        if (p->getLocalAtual() != origem) {
            std::cout << "[ERRO] O passageiro \"" << nome
                      << "\" nao esta na cidade de origem (esta em "
                      << p->getLocalAtual()->getNome() << ").\n";
            return false;
        }
        listaPassageiros.push_back(p);
    }

    // ----- Procurar trajeto direto compatível:
    Trajeto* trajetoEscolhido = nullptr;
    for (Trajeto* t : trajetos) {
        if (t->getOrigem() == origem && t->getDestino() == destino
            && t->getTipo() == transporte->getTipo()) {
            trajetoEscolhido = t;
            break;
        }
    }
    if (trajetoEscolhido == nullptr) {                     
        std::cout << "[ERRO] Nao existe trajeto direto compativel entre "
                  << nomeOrigem << " e " << nomeDestino << ".\n";
        return false;
    }

    Viagem* v = new Viagem(transporte, listaPassageiros,
                origem, destino, trajetoEscolhido->getDistancia());
    v->iniciarViagem();
    viagens.push_back(v);

    std::cout << "Viagem iniciada: " << nomeOrigem << " -> " << nomeDestino
              << " com o transporte \"" << nomeTransporte << "\".\n";
    return true;                                           
}

void ControladorDeTransito::avancarHoras(int horas) {
    for (Viagem* v : viagens) {
        if (!v->isFinalizada()) {
            v->avancarHoras(horas);
        }
    }
    std::cout << horas << " hora(s) avancada(s).\n";
}

// ------------------------------------------------------------------
// Consultas e relatorios
// ------------------------------------------------------------------

void ControladorDeTransito::relatarPassageiros() {
    std::cout << "\n===== ONDE ESTA CADA PASSAGEIRO =====\n";
    if (passageiros.empty()) {
        std::cout << "Nenhum passageiro cadastrado.\n";
        return;
    }
    for (Passageiro* p : passageiros) {
        Viagem* v = viagemAtivaDoPassageiro(p);
        if (v == nullptr) {
            // Nao esta em nenhuma viagem: esta na cidade do localAtual
            std::cout << "- " << p->getNome() << ": em "
                      << p->getLocalAtual()->getNome() << "\n";
        } else {
            // Em transito: origem, destino e transporte vem da viagem
            std::cout << "- " << p->getNome() << ": em transito (" << v->getOrigem()->getNome() << " -> " << v->getDestino()->getNome() << ", transporte: " << v->getTransporte()->getNome() << ")\n";
        }
    }
}

void ControladorDeTransito::relatarTransportes() {
    std::cout << "\n===== ONDE ESTA CADA TRANSPORTE =====\n";
    if (transportes.empty()) {
        std::cout << "Nenhum transporte cadastrado.\n";
        return;
    }
    for (Transporte* t : transportes) {
        Viagem* v = viagemAtivaDoTransporte(t);
        if (v == nullptr) {
            std::cout << "- " << t->getNome() << ": em "
                      << t->getLocalAtual()->getNome() << "\n";
        } else {
            std::cout << "- " << t->getNome() << ": em transito ("
                      << v->getOrigem()->getNome() << " -> "
                      << v->getDestino()->getNome() << ") ["
                      << v->getDistanciaPercorrida() << "/"
                      << v->getDistancia() << " km]\n";
        }
    }
}