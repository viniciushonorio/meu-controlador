#include "Viagem.hpp"

Viagem::Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros,
               Cidade* origem, Cidade* destino, int distancia)
    : transporte(transporte), passageiros(passageiros), origem(origem),
      destino(destino), distancia(distancia), distanciaPercorrida(0),
      kmDesdeUltimoDescanso(0), horasDescansoRestantes(0),
      horasEmTransito(0), emAndamento(false), finalizada(false) {}

void Viagem::iniciarViagem() {
    emAndamento = true;
}

void Viagem::avancarHoras(int horas) {
    for (int h = 0; h < horas; h++) {
        if (finalizada) break;

        horasEmTransito++;

        if (horasDescansoRestantes > 0) {
            horasDescansoRestantes--; 
            continue;
        }

        distanciaPercorrida += transporte->getVelocidade();
        kmDesdeUltimoDescanso += transporte->getVelocidade();

        if (distanciaPercorrida >= distancia) {
            distanciaPercorrida = distancia;
            emAndamento = false;
            finalizada = true;
            transporte->setLocalAtual(destino);
            for (Passageiro* p : passageiros) {
                p->setLocalAtual(destino);
            }
            destino->registrarVisita();
            continue;
        }

        if (transporte->getDistanciaEntreDescansos() > 0 &&
            kmDesdeUltimoDescanso >= transporte->getDistanciaEntreDescansos()) {
            horasDescansoRestantes = transporte->getTempoDescanso();
            kmDesdeUltimoDescanso = 0;
        }
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