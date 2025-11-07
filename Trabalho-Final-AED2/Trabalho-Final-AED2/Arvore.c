#include "Arvore.h"
#include "Leitura.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -> ÁRVORE BINÁRIA:

NoBin *criar_no_arvoreBinaria(char *palavra, char *nome_musica,
                              char *compositor, char *estrofe,
                              int frequencia_atual) {
  NoBin *novo = malloc(sizeof(NoBin));

  if (novo == NULL) {
    printf("Erro ao alocar memória para o novo nó da árvore binária.\n");
    return NULL;
  }
  strncpy(novo->entrada.palavra, palavra, 100 - 1);
  novo->entrada.palavra[100 - 1] = '\0';
  strncpy(novo->entrada.musica.nome, nome_musica, 100 - 1);
  novo->entrada.musica.nome[100 - 1] = '\0';
  strncpy(novo->entrada.musica.compositor, compositor, 100 - 1);
  novo->entrada.musica.compositor[100 - 1] = '\0';
  strncpy(novo->entrada.musica.trecho, estrofe, 101 - 1);
  novo->entrada.musica.trecho[101 - 1] = '\0';
  novo->entrada.musica.frequencia = frequencia_atual;
  novo->entrada.frequencia = frequencia_atual;
  novo->esquerda = novo->direita = NULL;
  return novo;
}

NoBin *inserir_arvoreBinaria(NoBin *raiz, char *palavra, char *nome_musica,
                             char *compositor, char *estrofe,
                             int frequencia_atual) {
  if (raiz == NULL) {
    raiz = criar_no_arvoreBinaria(palavra, nome_musica, compositor, estrofe,
                                  frequencia_atual);
    return raiz;
  }

  int cmp = strcmp(raiz->entrada.palavra, palavra);
  if (cmp == 0) {
    raiz->entrada.frequencia += frequencia_atual;

    if (frequencia_atual > raiz->entrada.musica.frequencia) {
      raiz->entrada.musica.frequencia = frequencia_atual;
      strncpy(raiz->entrada.musica.nome, nome_musica, 100 - 1);
      strncpy(raiz->entrada.musica.compositor, compositor, 100 - 1);
      strncpy(raiz->entrada.musica.trecho, estrofe, 101 - 1);
    }
  } else if (cmp < 0) {
    raiz->direita =
        inserir_arvoreBinaria(raiz->direita, palavra, nome_musica, compositor,
                              estrofe, frequencia_atual);
  } else {
    raiz->esquerda =
        inserir_arvoreBinaria(raiz->esquerda, palavra, nome_musica, compositor,
                              estrofe, frequencia_atual);
  }
  return raiz;
}

Entrada *buscar_arvoreBinaria(NoBin *raiz, char *palavra) {
  if (raiz == NULL)
    return NULL;

  int cmp = strcmp(raiz->entrada.palavra, palavra);
  if (cmp == 0)
    return &raiz->entrada;
  else if (cmp < 0)
    return buscar_arvoreBinaria(raiz->direita, palavra);
  else
    return buscar_arvoreBinaria(raiz->esquerda, palavra);
}

void liberar_arvoreBinaria(NoBin *raiz) {
  if (raiz) {
    liberar_arvoreBinaria(raiz->esquerda);
    liberar_arvoreBinaria(raiz->direita);
    free(raiz);
  }
}


// -> ÁRVORE AVL:

NoAVL *criar_no_arvoreAVL(char *palavra, char *nome_musica, char *compositor,
                          char *estrofe, int frequencia_atual) {

  NoAVL *novo = malloc(sizeof(NoAVL));

  if (novo == NULL) {
    printf("Erro ao alocar memória para o novo nó da árvore AVL.\n");
    return NULL;
  }
  strncpy(novo->entrada.palavra, palavra, 100 - 1);
  novo->entrada.palavra[100 - 1] = '\0';
  strncpy(novo->entrada.musica.nome, nome_musica, 100 - 1);
  novo->entrada.musica.nome[100 - 1] = '\0';
  strncpy(novo->entrada.musica.compositor, compositor, 100 - 1);
  novo->entrada.musica.compositor[100 - 1] = '\0';
  strncpy(novo->entrada.musica.trecho, estrofe, 101 - 1);
  novo->entrada.musica.trecho[101 - 1] = '\0';
  novo->entrada.musica.frequencia = frequencia_atual;
  novo->entrada.frequencia = frequencia_atual;
  novo->avl_esquerda = novo->avl_direita = NULL;
  novo->altura = 1;
  novo->fator = 0;

  return novo;
}

NoAVL *inserir_arvoreAVL(NoAVL *raiz_avl, char *palavra, char *nome_musica,
                         char *compositor, char *estrofe,
                         int frequencia_atual) {
  if (raiz_avl == NULL) {
    raiz_avl = criar_no_arvoreAVL(palavra, nome_musica, compositor, estrofe,
                                  frequencia_atual);
    return raiz_avl;
  }

  int cmp = strcmp(raiz_avl->entrada.palavra, palavra);
  if (cmp == 0) {
    raiz_avl->entrada.frequencia += frequencia_atual;

    if (frequencia_atual > raiz_avl->entrada.musica.frequencia) {
      raiz_avl->entrada.musica.frequencia = frequencia_atual;
      strncpy(raiz_avl->entrada.musica.nome, nome_musica, 100 - 1);
      strncpy(raiz_avl->entrada.musica.compositor, compositor, 100 - 1);
      strncpy(raiz_avl->entrada.musica.trecho, estrofe, 101 - 1);
    }
  } else if (cmp < 0) {
    raiz_avl->avl_direita =
        inserir_arvoreAVL(raiz_avl->avl_direita, palavra, nome_musica,
                          compositor, estrofe, frequencia_atual);
  } else {
    raiz_avl->avl_esquerda =
        inserir_arvoreAVL(raiz_avl->avl_esquerda, palavra, nome_musica,
                          compositor, estrofe, frequencia_atual);
  }

  raiz_avl->altura = 1 + maximo(altura_arvore_avl(raiz_avl->avl_esquerda),
                                altura_arvore_avl(raiz_avl->avl_direita));

  int balanceamento = calculo_fator_balanceamento_arvore_avl(raiz_avl);

  if (balanceamento > 1 &&
      strcmp(palavra, raiz_avl->avl_esquerda->entrada.palavra) < 0) {
    return rotacao_direita(&raiz_avl);
  }

  if (balanceamento > 1 &&
      strcmp(palavra, raiz_avl->avl_esquerda->entrada.palavra) > 0) {
    raiz_avl->avl_esquerda = rotacao_esquerda(&raiz_avl->avl_esquerda);
    return rotacao_direita(&raiz_avl);
  }

  if (balanceamento < -1 &&
      strcmp(palavra, raiz_avl->avl_direita->entrada.palavra) > 0) {
    return rotacao_esquerda(&raiz_avl);
  }

  if (balanceamento < -1 &&
      strcmp(palavra, raiz_avl->avl_direita->entrada.palavra) < 0) {
    raiz_avl->avl_direita = rotacao_direita(&raiz_avl->avl_direita);
    return rotacao_esquerda(&raiz_avl);
  }

  return raiz_avl;
}

Entrada *buscar_arvoreAVL(NoAVL *raiz_avl, char *palavra) {

  if (raiz_avl == NULL) {
    return NULL;
  }

  int cmp = strcmp(raiz_avl->entrada.palavra, palavra);

  if (cmp == 0)
    return &raiz_avl->entrada;
  else if (cmp < 0)
    return buscar_arvoreAVL(raiz_avl->avl_direita, palavra);
  else
    return buscar_arvoreAVL(raiz_avl->avl_esquerda, palavra);
}

void liberar_arvoreAVL(NoAVL *raiz_avl) {
  if (raiz_avl != NULL) {
    liberar_arvoreAVL(raiz_avl->avl_esquerda);
    liberar_arvoreAVL(raiz_avl->avl_direita);
    free(raiz_avl);
    return;
  }
}

int compara_nos(Entrada *entrada1, char *palavra, int frequencia) {
  if (frequencia < entrada1->frequencia) {
    return -1;
  } else if (frequencia > entrada1->frequencia) {
    return 1;
  } else {
    return strcmp(palavra, entrada1->palavra);
  }
}

NoAVL *inserir_arvoreAVL_frequencia(NoAVL *raiz_avl, char *palavra,
                                    char *nome_musica, char *compositor,
                                    char *estrofe, int frequencia_atual) {
  if (raiz_avl == NULL) {
    raiz_avl = criar_no_arvoreAVL(palavra, nome_musica, compositor, estrofe,
                                  frequencia_atual);
    return raiz_avl;
  }

  int compara =
      compara_nos(&raiz_avl->entrada, palavra, raiz_avl->entrada.frequencia);

  if (strcmp(palavra, raiz_avl->entrada.palavra) == 0) {
    raiz_avl->entrada.frequencia += frequencia_atual;

    if (frequencia_atual > raiz_avl->entrada.musica.frequencia) {
      raiz_avl->entrada.musica.frequencia = frequencia_atual;
      strncpy(raiz_avl->entrada.musica.nome, nome_musica, 100 - 1);
      raiz_avl->entrada.musica.nome[100 - 1] = '\0';
      strncpy(raiz_avl->entrada.musica.compositor, compositor, 100 - 1);
      raiz_avl->entrada.musica.compositor[100 - 1] = '\0';
      strncpy(raiz_avl->entrada.musica.trecho, estrofe, 101 - 1);
      raiz_avl->entrada.musica.trecho[101 - 1] = '\0';
    }
    return raiz_avl;
  }

  if (compara < 0) {
    raiz_avl->avl_esquerda = inserir_arvoreAVL_frequencia(
        raiz_avl->avl_esquerda, palavra, nome_musica, compositor, estrofe,
        frequencia_atual);
  }

  if (compara > 0) {
    raiz_avl->avl_direita = inserir_arvoreAVL_frequencia(
        raiz_avl->avl_direita, palavra, nome_musica, compositor, estrofe,
        frequencia_atual);
  }

  int frequencia_direita =
      raiz_avl->avl_direita ? raiz_avl->avl_direita->entrada.frequencia : 0;
  int frequencia_esquerda =
      raiz_avl->avl_esquerda ? raiz_avl->avl_esquerda->entrada.frequencia : 0;

  raiz_avl->altura = 1 + maximo(altura_arvore_avl(raiz_avl->avl_esquerda),
                                altura_arvore_avl(raiz_avl->avl_direita));

  int balanceamento = calculo_fator_balanceamento_arvore_avl(raiz_avl);

  if (balanceamento > 1 &&
      strcmp(palavra, raiz_avl->avl_esquerda->entrada.palavra) < 0) {
    return rotacao_direita(&raiz_avl);
  }

  if (balanceamento > 1 &&
      strcmp(palavra, raiz_avl->avl_esquerda->entrada.palavra) > 0) {
    raiz_avl->avl_esquerda = rotacao_esquerda(&raiz_avl->avl_esquerda);
    return rotacao_direita(&raiz_avl);
  }

  if (balanceamento < -1 &&
    strcmp(palavra, raiz_avl->avl_direita->entrada.palavra) > 0) {
    return rotacao_esquerda(&raiz_avl);
  }

  if (balanceamento < -1 &&
      strcmp(palavra, raiz_avl->avl_direita->entrada.palavra) < 0) {
    raiz_avl->avl_direita = rotacao_direita(&raiz_avl->avl_direita);
    return rotacao_esquerda(&raiz_avl);
  }

  return raiz_avl;
}

int altura_arvore_avl(NoAVL *no_avl) {
  if (no_avl == NULL) {
    return 0;
  }
  return no_avl->altura;
}

int maximo(int a, int b) {
  if (a > b) {
    return a;
  } else {
    return b;
  }
}

int calculo_fator_balanceamento_arvore_avl(NoAVL *no_avl) {
  if (no_avl == NULL) {
    return 0;
  } else {
    no_avl->fator = (altura_arvore_avl(no_avl->avl_esquerda) -
                     altura_arvore_avl(no_avl->avl_direita));
    return no_avl->fator;
  }
}

NoAVL *rotacao_direita(NoAVL **no_avl) {
  NoAVL *aux;
  aux = (*no_avl)->avl_esquerda;
  (*no_avl)->avl_esquerda = aux->avl_direita;
  aux->avl_direita = (*no_avl);

  (*no_avl)->altura = 1 + maximo(altura_arvore_avl((*no_avl)->avl_esquerda),
                                 altura_arvore_avl((*no_avl)->avl_direita));
  aux->altura = 1 + maximo(altura_arvore_avl(aux->avl_esquerda),
                           altura_arvore_avl(aux->avl_direita));

  (*no_avl) = aux;

  return *no_avl;
}

NoAVL *rotacao_esquerda(NoAVL **no_avl) {
  NoAVL *aux;
  aux = (*no_avl)->avl_direita;
  (*no_avl)->avl_direita = aux->avl_esquerda;
  aux->avl_esquerda = (*no_avl);

  (*no_avl)->altura = 1 + maximo(altura_arvore_avl((*no_avl)->avl_esquerda),
                                 altura_arvore_avl((*no_avl)->avl_direita));
  aux->altura = 1 + maximo(altura_arvore_avl(aux->avl_direita),
                           altura_arvore_avl(aux->avl_esquerda));

  (*no_avl) = aux;

  return *no_avl;
}
