#include <iostream>

int main() {
    std::cout << "Controlador de Viagens\n";
    return 0;

    Cidade natal("Natal");
    Passageiro maria("Maria", &natal);  // & pega o endereço de natal
    std::cout << maria.getNome() << " esta em " << maria.getLocalAtual()->getNome() << "\n";
}