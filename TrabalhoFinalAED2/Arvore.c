#include "Arvore.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Leitura.h"

// -> ÁRVORE BINÁRIA:

NoBin* criar_no_arvoreBinaria( char *palavra,  char *nome_musica,
                          char *compositor,  char *estrofe) {
    NoBin *novo = malloc(sizeof(NoBin));
    strncpy(novo->entrada.palavra, palavra, 100 - 1);
    strncpy(novo->entrada.musica.nome, nome_musica, 100 - 1);
    strncpy(novo->entrada.musica.compositor, compositor, 100 - 1);
    strncpy(novo->entrada.musica.trecho, estrofe, 101 - 1);
    novo->entrada.musica.frequencia = 1;
    novo->entrada.frequencia = 1;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

NoBin* inserir_arvoreBinaria(NoBin *raiz,  char *palavra,  char *nome_musica,  char *compositor,  char *estrofe) {
    if (raiz == NULL) {
        return criar_no_arvoreBinaria(palavra, nome_musica, compositor, estrofe);
    }

    int cmp = strcmp(raiz->entrada.palavra, palavra);
    if (cmp == 0) {
        raiz->entrada.frequencia++;
        if (raiz->entrada.musica.frequencia < 1) {
            raiz->entrada.musica.frequencia = 1;
            strncpy(raiz->entrada.musica.nome, nome_musica, 100 - 1);
            strncpy(raiz->entrada.musica.compositor, compositor, 100 - 1);
            strncpy(raiz->entrada.musica.trecho, estrofe, 101 - 1);
        }
    } else if (cmp < 0) {
        raiz->direita = inserir_arvoreBinaria(raiz->direita, palavra, nome_musica, compositor, estrofe);
    } else {
        raiz->esquerda = inserir_arvoreBinaria(raiz->esquerda, palavra, nome_musica, compositor, estrofe);
    }

    return raiz;
}

Entrada* buscar_arvoreBinaria(NoBin *raiz,  char *palavra) {
    if (raiz == NULL) return NULL;

    int cmp = strcmp(raiz->entrada.palavra, palavra);
    if (cmp == 0) return &raiz->entrada;
    else if (cmp < 0) return buscar_arvoreBinaria(raiz->direita, palavra);
    else return buscar_arvoreBinaria(raiz->esquerda, palavra);
}

void liberar_arvoreBinaria(NoBin *raiz) {
    if (raiz) {
        liberar_arvoreBinaria(raiz->esquerda);
        liberar_arvoreBinaria(raiz->direita);
        free(raiz);
    }
}

void percurso_pre_fixado(NoBin *arv_bin) {
  if (arv_bin == NULL) {
    return;
  } else {
    printf("%s\n", arv_bin->entrada.palavra);
    percurso_pre_fixado(arv_bin->esquerda);
    percurso_pre_fixado(arv_bin->direita);
  }
}

void percurso_central(NoBin *arv_bin) {
  if (arv_bin == NULL) {
    return;
  } else {
    percurso_central(arv_bin->esquerda);
    printf("%s\n", arv_bin->entrada.palavra);
    percurso_central(arv_bin->direita);
  }
}

void percurso_pos_fixado(NoBin *arv_bin) {
  if (arv_bin == NULL) {
    return;
  } else {
    percurso_pos_fixado(arv_bin->esquerda);
    percurso_pos_fixado(arv_bin->direita);
    printf("%s\n", arv_bin->entrada.palavra);
  }
}

// -> ÁRVORE AVL:

// void incializa_arvore_avl(NoAVL **arv_avl) { (*arv_avl) = NULL; }

// int arvore_avl_vazia(NoAVL *arv_avl) { return (arv_avl == NULL); }

// void insere_arvore_avl(NoAVL **no_avl, char *palavra, char *nome_musica, char *compositor, char *estrofe) {
//   if (arvore_avl_vazia(*no_avl)) {
//     *no_avl = (NoAVL *)malloc(sizeof(NoAVL));
//     strcpy((*no_avl)->entrada.palavra, palavra);
//     strcpy((*no_avl)->entrada.musica.nome, nome_musica);
//     strcpy((*no_avl)->entrada.musica.compositor, compositor);
//     strcpy((*no_avl)->entrada.musica.trecho, estrofe);
//     (*no_avl)->avl_esquerda = NULL;
//     (*no_avl)->avl_direita = NULL;
//     (*no_avl)->fator_balanceamento = 0;
//     (*no_avl)->entrada.frequencia = 1;
    
//     return;
//   }

//   else {
//     if (strcmp((*no_avl)->entrada.palavra, palavra) == 0) {
//       (*no_avl)->entrada.frequencia++;
//       return;
//     } else {
//       if (strcmp((*no_avl)->entrada.palavra, palavra) < 0) {
//         insere_arvore_avl(&(*no_avl)->avl_direita, palavra, nome_musica, compositor, estrofe);
//         return;
//       } else {
//         if (strcmp((*no_avl)->entrada.palavra, palavra) > 0) {
//           insere_arvore_avl(&(*no_avl)->avl_esquerda, palavra, nome_musica, compositor, estrofe);
//           return;
//         } else {
//           printf("Erro ao inserir palavra na árvore AVL, registro já "
//                  "existente.\n");
//         }
//       }
//     }
//   }
// }

// void busca_arvore_avl(NoAVL *arv_avl, char *palavra) {

//   if (arv_avl == NULL) {
//     printf("Palavra não encontrada.\n");
//   }

//   while (arv_avl != NULL) {
//     if (strcmp(arv_avl->entrada.palavra, palavra) == 0) {
//       printf("---------------------------------\n");
//       printf("Palavra encontrada: %s\n", arv_avl->entrada.palavra);
//       printf("Música: %s\n", arv_avl->entrada.musica.nome);
//       printf("Compositor: %s\n", arv_avl->entrada.musica.compositor);
//       printf("Trecho: %s\n", arv_avl->entrada.musica.trecho);
//       printf("Frequência: %d\n", arv_avl->entrada.frequencia);
//       printf("---------------------------------\n");
//     } else {
//       if (strcmp(arv_avl->entrada.palavra, palavra) < 0) {
//         arv_avl = arv_avl->avl_direita;
//         busca_arvore_avl(arv_avl, palavra);
//       } else {
//         if (strcmp(arv_avl->entrada.palavra, palavra) > 0) {
//           arv_avl = arv_avl->avl_esquerda;
//           busca_arvore_avl(arv_avl, palavra);
//         }
//       }
//     }
//   }
// }

// void libera_arvore_avl(NoAVL *arv_avl) {
//   if (arv_avl != NULL) {
//     libera_arvore_avl(arv_avl->avl_esquerda);
//     libera_arvore_avl(arv_avl->avl_direita);
//     free(arv_avl);
//     return;
//   }
// }

// int altura_arvore_avl(NoAVL *no_avl) {
//   if (no_avl == NULL) {
//     return 0;
//   } else {
//     altura_arvore_avl(no_avl->avl_esquerda);
//     altura_arvore_avl(no_avl->avl_direita);
//   }
// }

// void calculo_fator_balanceamento_arvore_avl(NoAVL *no_avl) {
//   if (no_avl == NULL) {
//     return;
//   } else {
//     calculo_fator_balanceamento_arvore_avl(no_avl->avl_esquerda);
//     calculo_fator_balanceamento_arvore_avl(no_avl->avl_direita);
//     no_avl->fator_balanceamento = (altura_arvore_avl(no_avl->avl_direita) -altura_arvore_avl(no_avl->avl_esquerda));
//   }
// }

// void rotacao_direita(NoAVL **no_avl) {
//   NoAVL *aux;
//   aux = (*no_avl)->avl_esquerda;
//   (*no_avl)->avl_esquerda = aux->avl_direita;
//   aux->avl_direita = (*no_avl);
//   (*no_avl) = aux;
//   return;
// }

// void rotacao_esquerda(NoAVL **no_avl) {
//   NoAVL *aux;
//   aux = (*no_avl)->avl_direita;
//   (*no_avl)->avl_direita = aux->avl_esquerda;
//   aux->avl_esquerda = (*no_avl);
//   (*no_avl) = aux;
//   return;
// }

// void tipo_rotacao_arvore_avl(NoAVL **no_avl) {
//   if ((*no_avl)->fator_balanceamento == 2) {
//     if ((*no_avl)->avl_direita->fator_balanceamento == 1) {
//       rotacao_esquerda(no_avl);
//     } else {
//       rotacao_direita(&(*no_avl)->avl_direita);
//       rotacao_esquerda(no_avl);
//     }
//   } else {
//     if ((*no_avl)->fator_balanceamento == -2) {
//       if ((*no_avl)->avl_esquerda->fator_balanceamento == -1) {
//         rotacao_direita(no_avl);
//       } else {
//         rotacao_esquerda(&(*no_avl)->avl_esquerda);
//         rotacao_direita(no_avl);
//       }
//     }
//   }
// }