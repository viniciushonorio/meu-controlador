#ifndef CONTROLADOR_DE_TRANSITO_HPP
#define CONTROLADOR_DE_TRANSITO_HPP

#include <string>
#include <vector>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"

/**
 * Classe central do sistema. Guarda todas as entidades cadastradas,
 * valida e cria viagens (inclusive com conexões), avança o tempo,
 * gera os relatórios e cuida da persistência em arquivos de texto.
 */
class ControladorDeTransito {
private:
    std::vector<Cidade*> cidades;
    std::vector<Passageiro*> passageiros;
    std::vector<Transporte*> transportes;
    std::vector<Trajeto*> trajetos;

    // Buscas por nome (retornam nullptr se não encontrado)
    Cidade* buscarCidade(const std::string& nome);
    Passageiro* buscarPassageiro(const std::string& nome);
    Transporte* buscarTransporte(const std::string& nome);

public:
    // ---- Cadastros (retornam false e imprimem erro em caso de falha) ----
    bool cadastrarCidade(const std::string& nome);
    bool cadastrarPassageiro(const std::string& nome, const std::string& nomeLocalAtual);
    bool cadastrarTransporte(const std::string& nome, char tipo, int capacidade,
                             int velocidade, int distanciaEntreDescansos,
                             int tempoDescanso, const std::string& nomeLocalAtual);
    bool cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino,
                          char tipo, int distancia);
};

#endif