#include "Cidade.hpp"

Cidade::Cidade(std::string nome, int visitas)
    : nome(nome), visitas(visitas) {}

std::string Cidade::getNome() const {
    return nome;
}

int Cidade::getVisitas() const {
    return visitas;
}

void Cidade::registrarVisita() {
    visitas++;
}