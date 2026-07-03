# Sistema Controlador de Viagens

Sistema de controle de tráfego entre cidades desenvolvido em C++ com programação
orientada a objetos, para a disciplina de Linguagem de Programação 1 (UFRN/IMD).
Permite cadastrar cidades, trajetos, transportes e passageiros, simular viagens
com avanço de tempo (inclusive com conexões) e gerar relatórios.

**Autor:** Vinicius Honorio dos Santos

## Como compilar

Requisitos: `g++` (C++17) e `make`.

### Make

Isso gera o executável `controlador`. Para compilar sem make:

`g++ -std=c++17 -Wall -Wextra src/*.cpp -o controlador`

Para limpar os arquivos de compilação: `make clean`

## Como executar

`./controlador`

Ao iniciar, o sistema carrega automaticamente os dados salvos na execução
anterior (se existirem) e exibe o menu principal.

## Como usar

1. Cadastre as **cidades** (opção 1) — todo o resto depende delas.
2. Cadastre os **trajetos** entre cidades (opção 3), informando tipo
   ('A' aquático / 'T' terrestre) e distância em km.
3. Cadastre os **transportes** (opção 4) e os **passageiros** (opção 2),
   informando em qual cidade cada um está.
4. Inicie **viagens** (opção 5): origem, destino, transporte e lista de
   passageiros (linha vazia encerra a lista).
5. Use a opção 6 para **avançar as horas** e simular o andamento.
6. Consulte os **relatórios** (opções 7 a 10) e o **melhor trajeto** (opção 11).
7. Saia com a opção 0, que **salva os dados** automaticamente.

## Decisões de projeto e regras de negócio

- **Trajetos são direcionados**: um trajeto de A para B não permite viajar de
  B para A. Para ida e volta, cadastre os dois sentidos.
- **Compatibilidade de tipo**: um transporte só utiliza trajetos do mesmo tipo
  que ele (transporte aquático não anda em trajeto terrestre e vice-versa).
- **Melhor caminho**: calculado pelo algoritmo de Dijkstra, minimizando a
  distância total e considerando apenas trajetos compatíveis com o tipo do
  transporte.
- **Viagens com conexão**: quando não há trajeto direto entre origem e destino,
  o sistema cria automaticamente uma cadeia de viagens (uma por trecho do
  melhor caminho), ligadas por ponteiro. Um trecho só começa quando o anterior
  termina, e o transporte e os passageiros só têm sua localização atualizada
  quando o ÚLTIMO trecho é finalizado, conforme o enunciado. Durante todo o
  percurso, os relatórios os mostram como "em trânsito".
- **Validações de viagem**: a viagem só é permitida se existir caminho
  compatível, se o transporte estiver na cidade de origem e livre, se todos os
  passageiros estiverem na origem e livres, e se a capacidade for respeitada.
- **Descanso**: a cada `distância entre descansos` km percorridos, o transporte
  para por `tempo de descanso` horas antes de continuar.
- **Visitas**: o contador de visitas de uma cidade é incrementado quando uma
  viagem é finalizada nela (chegada ao destino final).
- **Persistência**: os dados são salvos em arquivos de texto (`cidades.txt`,
  `trajetos.txt`, `transportes.txt`, `passageiros.txt`) com campos separados
  por `;`. **Limitação**: viagens em andamento não são persistidas — ao sair,
  recomenda-se avançar as horas até que as viagens em curso sejam concluídas.

## Estrutura do projeto

controlador-de-viagens/
├── Makefile
├── README.md
└── src/
    ├── Cidade.hpp / .cpp       # cidade e contador de visitas
    ├── Trajeto.hpp / .cpp      # ligação direcionada entre cidades
    ├── Transporte.hpp / .cpp   # meio de transporte e seus atributos
    ├── Passageiro.hpp / .cpp   # passageiro e sua localização
    ├── Viagem.hpp / .cpp       # trecho de viagem + simulação e conexões
    ├── ControladorDeTransito.hpp / .cpp  # orquestra tudo (cadastros,
    │                                     # Dijkstra, relatórios, persistência)
    └── main.cpp                # menu da interface de linha de comando