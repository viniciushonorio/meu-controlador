#include "Viagem.hpp"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros,
               Cidade* origem, Cidade* destino, int distancia)
    : transporte(transporte), passageiros(passageiros), origem(origem),
      destino(destino), distancia(distancia), proxima(nullptr), distanciaPercorrida(0),
      kmDesdeUltimoDescanso(0), horasDescansoRestantes(0),
      horasEmTransito(0), emAndamento(false), finalizada(false) {}

void Viagem::iniciarViagem() {
    emAndamento = true;
}

void Viagem::setProxima(Viagem* v) {
    proxima = v;
}

Viagem* Viagem::getProxima() const {
    return proxima;
}

Viagem* Viagem::trechoAtual() {
    if (!finalizada) return this;
    if (proxima != nullptr) return proxima->trechoAtual();
    return nullptr;
}

bool Viagem::cadeiaFinalizada() const {
    if (!finalizada) return false;                       // eu nem acabei
    if (proxima != nullptr) return proxima->cadeiaFinalizada();  // eu sim; e o resto?
    return true;                                         // acabei e sou o ultimo
}

Cidade* Viagem::getDestinoFinal() const {
    if (proxima != nullptr) return proxima->getDestinoFinal();
    return destino;
}

void Viagem::avancarUmaHora() {
    horasEmTransito++;

    if (horasDescansoRestantes > 0) {
        horasDescansoRestantes--;
        return;
    }

    distanciaPercorrida += transporte->getVelocidade();
    kmDesdeUltimoDescanso += transporte->getVelocidade();

    if (distanciaPercorrida >= distancia) {
        distanciaPercorrida = distancia;
        emAndamento = false;
        finalizada = true;

        // SO o ultimo trecho da corrente move todo mundo (regra do enunciado!)
        if (proxima == nullptr) {
            transporte->setLocalAtual(destino);
            for (Passageiro* p : passageiros) {
                p->setLocalAtual(destino);
            }
            destino->registrarVisita();
        }
        return;
    }

    if (transporte->getDistanciaEntreDescansos() > 0 &&
        kmDesdeUltimoDescanso >= transporte->getDistanciaEntreDescansos()) {
        horasDescansoRestantes = transporte->getTempoDescanso();
        kmDesdeUltimoDescanso = 0;
    }
}

void Viagem::avancarHoras(int horas) {
    for (int h = 0; h < horas; h++) {
        Viagem* trecho = trechoAtual();
        if (trecho == nullptr) break;               // corrente ja encerrada
        if (!trecho->emAndamento) trecho->iniciarViagem();  // partida do trecho
        trecho->avancarUmaHora();
    }
}

bool Viagem::isEmAndamento() const {
    return emAndamento;
}

bool Viagem::isFinalizada() const {
    return finalizada;
}

Cidade* Viagem::getOrigem() const {
    return origem;
}

Cidade* Viagem::getDestino() const {
    return destino;
}

Transporte* Viagem::getTransporte() const {
    return transporte;
}

const std::vector<Passageiro*>& Viagem::getPassageiros() const {
    return passageiros;
}

int Viagem::getDistancia() const {
    return distancia;
}

int Viagem::getDistanciaPercorrida() const {
    return distanciaPercorrida;
}

int Viagem::getHorasEmTransito() const {
    return horasEmTransito;
}