#ifndef _LEITURA_H_
#define _LEITURA_H_

#include "Vetor.h"

struct no_binaria;
typedef struct no_binaria NoBin;
struct no_avl;
typedef struct no_avl NoAVL;

void menu();
void exibir_resultado( Entrada *entrada);
void carregar_arquivos(VetorDin *vetor, NoBin **raiz_arvore, NoAVL **raiz_avl);
void buscar_palavra(VetorDin *vetor, NoBin *raiz_arvore, NoAVL *raiz_avl);
void normalizar_palavra(char *palavra);
Entrada* buscar_vetor(VetorDin *vetor,  char *palavra);
Entrada* buscar_arvore(NoBin *raiz_arvore,  char *palavra);
Entrada* buscar_avl(NoAVL *raiz_avl,  char *palavra);
void liberar_arvore(NoBin *raiz_arvore);
void liberar_avl(NoAVL *raiz_avl);
#endif 