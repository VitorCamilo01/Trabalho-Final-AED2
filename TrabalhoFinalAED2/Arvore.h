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
  int altura;
};

typedef struct no_avl NoAVL;

// ÁRVORE BINÁRIA:

NoBin* criar_no_arvoreBinaria( char *palavra,  char *nome_musica,
  char *compositor,  char *estrofe);
NoBin* inserir_arvoreBinaria(NoBin *raiz,  char *palavra,  char *nome_musica,  char *compositor,  char *estrofe);
Entrada* buscar_arvoreBinaria(NoBin *raiz,  char *palavra);
void liberar_arvoreBinaria(NoBin *raiz);
void percurso_pre_fixado(NoBin *arv_bin);
void percurso_central(NoBin *arv_bin);
void percurso_pos_fixado(NoBin *arv_bin);
// ÁRVORE AVL:

// void incializa_arvore_avl(NoAVL **);
// int arvore_avl_vazia(NoAVL *);
// void insere_arvore_avl(NoAVL **, char *, char *, char *, char *);
// void busca_arvore_avl(NoAVL *, char *);
// void rotacao_direita(NoAVL **);
// void rotacao_esquerda(NoAVL **);
// void libera_arvore_avl(NoAVL *);
// int altura_arvore_avl(NoAVL *);
// void calculo_fator_balanceamento_arvore_avl(NoAVL *);
// void tipo_rotacao_arvore_avl(NoAVL **);

#endif