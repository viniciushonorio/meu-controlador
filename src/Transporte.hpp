#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include <string>
#include "Cidade.hpp"

/**
 * Representa um meio de transporte (ex: ônibus, navio).
 * tipo: 'A' para Aquático, 'T' para Terrestre.
 * O transporte precisa descansar 'tempoDescanso' horas a cada
 * 'distanciaEntreDescansos' km percorridos.
 *
 * Observação: localAtual só é atualizado quando a viagem (ou a última
 * viagem de uma cadeia de conexões) é finalizada, conforme o enunciado.
 */
class Transporte {
private:
    std::string nome;
    char tipo;                    // 'A' = Aquático, 'T' = Terrestre
    int capacidade;               // número máximo de passageiros
    int velocidade;               // km/h
    int distanciaEntreDescansos;  // km
    int tempoDescanso;            // horas
    Cidade* localAtual;

public:
    Transporte(std::string nome, char tipo, int capacidade, int velocidade,
               int distanciaEntreDescansos, int tempoDescanso, Cidade* localAtual);

    std::string getNome() const;
    char getTipo() const;
    int getCapacidade() const;
    int getVelocidade() const;
    int getDistanciaEntreDescansos() const;
    int getTempoDescanso() const;
    Cidade* getLocalAtual() const;

    void setLocalAtual(Cidade* local);
};

#endif