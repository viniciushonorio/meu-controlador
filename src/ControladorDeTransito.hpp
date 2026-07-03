#ifndef CONTROLADOR_DE_TRANSITO_HPP
#define CONTROLADOR_DE_TRANSITO_HPP

#include <string>
#include <vector>
#include "Cidade.hpp"
#include "Passageiro.hpp"
#include "Trajeto.hpp"
#include "Transporte.hpp"
#include "Viagem.hpp"

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
    std::vector<Viagem*> viagens;

    // Buscas por nome (retornam nullptr se não encontrado)
    Cidade* buscarCidade(const std::string& nome);
    Passageiro* buscarPassageiro(const std::string& nome);
    Transporte* buscarTransporte(const std::string& nome);

    // Retorna a cadeia de viagem em andamento que contém o transporte/passageiro
    // (nullptr se ele não está viajando)
    Viagem* viagemAtivaDoTransporte(Transporte* t);
    Viagem* viagemAtivaDoPassageiro(Passageiro* p);

public:
    // ---- Cadastros (retornam false e imprimem erro em caso de falha) ----
    bool cadastrarCidade(const std::string& nome);

    bool cadastrarPassageiro(const std::string& nome, const std::string& nomeLocalAtual);

    bool cadastrarTransporte(const std::string& nome, char tipo, int capacidade,
                             int velocidade, int distanciaEntreDescansos,
                             int tempoDescanso, const std::string& nomeLocalAtual);

    bool cadastrarTrajeto(const std::string& nomeOrigem, const std::string& nomeDestino,
                          char tipo, int distancia);

    bool iniciarViagem(const std::string& nomeTransporte,
                   const std::vector<std::string>& nomesPassageiros,
                   const std::string& nomeOrigem, const std::string& nomeDestino);
    
    // Avança o tempo de TODAS as viagens em andamento
    void avancarHoras(int horas);

    // ---- Consultas e relatorios ----
    
    void relatarPassageiros();
    void relatarTransportes();
    void relatarViagensEmAndamento();
    void relatarCidadesMaisVisitadas();

    // ---- Persistencia em arquivos de texto ----

    void salvarDados();
    void carregarDados();
    
    // ----- Calculo melhor trajeto -----------
    std::vector<Trajeto*> calcularMelhorTrajeto(Cidade* origem, Cidade* destino, char tipo);
};

#endif