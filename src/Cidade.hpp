#ifndef CIDADE_HPP
#define CIDADE_HPP

#include <string>

/**
 * Representa uma cidade cadastrada no sistema.
 * Além do nome, guarda um contador de visitas (quantas viagens
 * finalizaram nesta cidade), usado no relatório de cidades mais visitadas.
 */
class Cidade {
private:
    std::string nome;
    int visitas;

public:
    Cidade(std::string nome, int visitas = 0);

    std::string getNome() const;
    int getVisitas() const;

    // Incrementa o contador de visitas (chamado quando uma viagem termina aqui)
    void registrarVisita();
};

#endif