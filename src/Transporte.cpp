#include "Transporte.hpp"

Transporte::Transporte(std::string nome, char tipo, int capacidade, int velocidade,
                       int distanciaEntreDescansos, int tempoDescanso, Cidade* localAtual)
    : nome(nome), tipo(tipo), capacidade(capacidade), velocidade(velocidade),
      distanciaEntreDescansos(distanciaEntreDescansos), tempoDescanso(tempoDescanso),
      localAtual(localAtual) {}

std::string Transporte::getNome() const {
    return nome;
}

char Transporte::getTipo() const {
    return tipo;
}

int Transporte::getCapacidade() const {
    return capacidade;
}

int Transporte::getVelocidade() const {
    return velocidade;
}

int Transporte::getDistanciaEntreDescansos() const {
    return distanciaEntreDescansos;
}

int Transporte::getTempoDescanso() const {
    return tempoDescanso;
}

Cidade* Transporte::getLocalAtual() const {
    return localAtual;
}

void Transporte::setLocalAtual(Cidade* local) {
    localAtual = local;
}