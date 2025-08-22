#include "Leitura.h"
#include "Vetor.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// -> VETOR DE PESQUISA BINÁRIA:

void inicializa_vetor(VetorDin *vetor) {
    vetor->vetor = malloc(100 * sizeof(Entrada));
    vetor->qtd = 0;
    vetor->capacidade = 100;
}

void insere_vetor(VetorDin *vetor, const char *palavra, const char *nome_musica, const char *compositor, const char *estrofe) {
    if (vetor->qtd >= vetor->capacidade) {
        vetor->capacidade *= 2;
        vetor->vetor = realloc(vetor->vetor, vetor->capacidade * sizeof(Entrada));
    }

    for (int i = 0; i < vetor->qtd; i++) {
        if (strcmp(vetor->vetor[i].palavra, palavra) == 0) {
            vetor->vetor[i].frequencia++;

            if (vetor->vetor[i].musica.frequencia < 1) {
                vetor->vetor[i].musica.frequencia  = 1;
                strncpy(vetor->vetor[i].musica.nome, nome_musica, 100 - 1);
                strncpy(vetor->vetor[i].musica.compositor, compositor, 100 - 1);
                strncpy(vetor->vetor[i].musica.trecho, estrofe, 101 - 1);
            }
            return;
        }
    }

    strncpy(vetor->vetor[vetor->qtd].palavra, palavra, 100 - 1);
    strncpy(vetor->vetor[vetor->qtd].musica.nome, nome_musica, 100 - 1);
    strncpy(vetor->vetor[vetor->qtd].musica.compositor, compositor, 100 - 1);
    strncpy(vetor->vetor[vetor->qtd].musica.trecho, estrofe, 101 - 1);
    vetor->vetor[vetor->qtd].musica.frequencia = 1;
    vetor->vetor[vetor->qtd].frequencia = 1;
    vetor->qtd++;
}


int comparar_entradas(const void *a, const void *b) {
  return strcmp(((Entrada*)a)->palavra, ((Entrada*)b)->palavra);
}

void ordenar_vetor(VetorDin *vetor) {
  qsort(vetor->vetor, vetor->qtd, sizeof(Entrada), comparar_entradas);
}

Entrada* buscaBin_vetor(const VetorDin *vetor, const char *palavra) {
  int inicio = 0, fim = vetor->qtd - 1;
  while (inicio <= fim) {
      int meio = (inicio + fim) / 2;
      int cmp = strcmp(vetor->vetor[meio].palavra, palavra);

      if (cmp == 0) return &vetor->vetor[meio];
      else if (cmp < 0) inicio = meio + 1;
      else fim = meio - 1;
  }
  return NULL;
}

void liberar_vetor(VetorDin *vetor) {
  free(vetor->vetor);
  vetor->qtd = 0;
  vetor->capacidade = 0;
}