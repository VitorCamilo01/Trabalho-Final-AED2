#include "Vetor.h"
#include "Leitura.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -> VETOR DE PESQUISA BINÁRIA:

void inicializa_vetor(VetorDin *vetor) {
  vetor->vetor = malloc(100 * sizeof(Entrada));
  if (vetor->vetor == NULL) {
    printf("Erro ao alocar memória para o vetor.\n");
    exit(1);
  }
  vetor->qtd = 0;
  vetor->capacidade = 100;
}

void insere_vetor(VetorDin *vetor, const char *palavra, const char *nome_musica,
                  const char *compositor, const char *estrofe,
                  int frequencia_atual) {
  if (vetor->qtd >= vetor->capacidade) {
    vetor->capacidade *= 2;
    vetor->vetor = realloc(vetor->vetor, vetor->capacidade * sizeof(Entrada));
  }
  for (int i = 0; i < vetor->qtd; i++) {
    if (strcmp(vetor->vetor[i].palavra, palavra) == 0) {
      vetor->vetor[i].frequencia += frequencia_atual;
      if (frequencia_atual > vetor->vetor[i].musica.frequencia) {
        vetor->vetor[i].musica.frequencia = frequencia_atual;
        strncpy(vetor->vetor[i].musica.nome, nome_musica, 100 - 1);
        strncpy(vetor->vetor[i].musica.compositor, compositor, 100 - 1);
        strncpy(vetor->vetor[i].musica.trecho, estrofe, 101 - 1);
      }
      return;
    }
  }

  strncpy(vetor->vetor[vetor->qtd].palavra, palavra, 100 - 1);
  vetor->vetor[vetor->qtd].palavra[100 - 1] = '\0';
  strncpy(vetor->vetor[vetor->qtd].musica.nome, nome_musica, 100 - 1);
  vetor->vetor[vetor->qtd].musica.nome[100 - 1] = '\0';
  strncpy(vetor->vetor[vetor->qtd].musica.compositor, compositor, 100 - 1);
  vetor->vetor[vetor->qtd].musica.compositor[100 - 1] = '\0';
  strncpy(vetor->vetor[vetor->qtd].musica.trecho, estrofe, 101 - 1);
  vetor->vetor[vetor->qtd].musica.trecho[101 - 1] = '\0';
  vetor->vetor[vetor->qtd].musica.frequencia = frequencia_atual;
  vetor->vetor[vetor->qtd].frequencia = frequencia_atual;
  vetor->qtd++;
}
int comparar_entradas(const void *a, const void *b) {
  return strcmp(((Entrada *)a)->palavra, ((Entrada *)b)->palavra);
}

void ordenar_vetor(VetorDin *vetor) {
  qsort(vetor->vetor, vetor->qtd, sizeof(Entrada), comparar_entradas);
}

Entrada *buscaBin_vetor(const VetorDin *vetor, const char *palavra) {
  int inicio = 0, fim = vetor->qtd - 1;
  while (inicio <= fim) {
    int meio = (inicio + fim) / 2;
    int cmp = strcmp(vetor->vetor[meio].palavra, palavra);

    if (cmp == 0)
      return &vetor->vetor[meio];
    else if (cmp < 0)
      inicio = meio + 1;
    else
      fim = meio - 1;
  }
  return NULL;
}

void liberar_vetor(VetorDin *vetor) {
  free(vetor->vetor);
  vetor->qtd = 0;
  vetor->capacidade = 0;
}