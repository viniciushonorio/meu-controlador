#ifndef VIAGEM_HPP
#define VIAGEM_HPP

#include <vector>
#include "Cidade.hpp"
#include "Transporte.hpp"
#include "Passageiro.hpp"

class Viagem {
private:
    Transporte* transporte;
    std::vector<Passageiro*> passageiros;
    Cidade* origem;
    Cidade* destino;
    int distancia;              // km do trecho (vem do trajeto)

    int distanciaPercorrida;    // comeca em 0, cresce a cada hora
    int kmDesdeUltimoDescanso;  // km acumulados desde o último descanso
    int horasDescansoRestantes; // horas restantes de descanso (0 = viajando)
    int horasEmTransito;        // contador pro relatorio
    bool emAndamento;
    bool finalizada;

public:
    Viagem(Transporte* transporte, std::vector<Passageiro*> passageiros,
           Cidade* origem, Cidade* destino, int distancia);

    // Marca este trecho como em andamento (registra a partida)
    void iniciarViagem();

    // Avança 'horas' horas na CADEIA inteira (deve ser chamado na cabeça)
    void avancarHoras(int horas);

    bool isEmAndamento() const;
    bool isFinalizada() const;      // este trecho

    Cidade* getOrigem() const;
    Cidade* getDestino() const;
    Transporte* getTransporte() const;
    const std::vector<Passageiro*>& getPassageiros() const;

    int getDistancia() const;
    int getDistanciaPercorrida() const;
    int getHorasEmTransito() const;

};

#endif