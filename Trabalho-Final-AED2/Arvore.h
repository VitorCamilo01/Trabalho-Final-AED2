#ifndef _ARVORE_H_
#define _ARVORE_H_

#include "Leitura.h"

// Estrutura de dados da Árvore Binária:

struct no_binaria {
  Entrada entrada;
  struct no_binaria *esquerda;
  struct no_binaria *direita;
};

typedef struct no_binaria NoBin;

// Estrutura de dados da Árvore AVL:

struct no_avl {
  Entrada entrada;
  struct no_avl *avl_esquerda;
  struct no_avl *avl_direita;
  int fator;
  int altura;
};

typedef struct no_avl NoAVL;

// ÁRVORE BINÁRIA:

NoBin *criar_no_arvoreBinaria(char *palavra, char *nome_musica,
                              char *compositor, char *estrofe,
                              int frequencia_atual);
NoBin *inserir_arvoreBinaria(NoBin *raiz, char *palavra, char *nome_musica,
                             char *compositor, char *estrofe,
                             int frequencia_atual);
Entrada *buscar_arvoreBinaria(NoBin *raiz, char *palavra);
void liberar_arvoreBinaria(NoBin *raiz);

// ÁRVORE AVL:

NoAVL *criar_no_arvoreAVL(char *palavra, char *nome_musica, char *compositor,
                          char *estrofe, int frequencia_atual);
NoAVL *inserir_arvoreAVL(NoAVL *raiz_avl, char *palavra, char *nome_musica,
                         char *compositor, char *estrofe, int frequencia_atual);
Entrada *buscar_arvoreAVL(NoAVL *raiz_avl, char *palavra);
NoAVL *rotacao_direita(NoAVL **);
NoAVL *rotacao_esquerda(NoAVL **);
NoAVL *inserir_arvoreAVL_frequencia(NoAVL *raiz_avl, char *palavra,
                                    char *nome_musica, char *compositor,
                                    char *estrofe, int frequencia_atual);
int compara_nos(Entrada *entrada1, char *palavra, int frequencia);
void liberar_arvoreAVL(NoAVL *no_avl);
int altura_arvore_avl(NoAVL *no_avl);
int maximo(int a, int b);
int calculo_fator_balanceamento_arvore_avl(NoAVL *no_avl);
void tipo_rotacao_arvore_avl(NoAVL **no_avl);

#endif