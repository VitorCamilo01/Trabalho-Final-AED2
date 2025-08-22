#ifndef _VETOR_H_
#define _VETOR_H_
#include "Leitura.h"

// Estrutura de dados do vetor dinâmico
struct musica {
  char nome[100];
  char compositor[100];
  int frequencia;
  char trecho[101];
};

typedef struct musica Musica;
typedef struct{
  char palavra[100];
  Musica musica;
  int frequencia;
} Entrada;

typedef struct {
  Entrada *vetor;
  int qtd;
  int capacidade;
} VetorDin;

// VETOR DE PESQUISA BINÁRIA:

void inicializa_vetor(VetorDin *vetor);
void insere_vetor(VetorDin *vetor, const char *palavra, const char *nome_musica, const char *compositor, const char *estrofe);
void ordenar_vetor(VetorDin *vetor);
Entrada* buscaBin_vetor(const VetorDin *vetor, const char *palavra);
void liberar_vetor(VetorDin *vetor);

#endif