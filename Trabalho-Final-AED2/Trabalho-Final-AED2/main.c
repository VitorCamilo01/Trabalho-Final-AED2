/* -> Discentes: Giovana de Almeida Faria, Vitor Rodrigues Guimarães Camilo e
Samuel Amorim
-> Matrículas: 12421BCC023, 12311ECP009 e 12411BCC
*/

#include "Arvore.h"
#include "Leitura.h"
#include "Vetor.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  VetorDin vetor;
  NoBin *raiz_arvore = NULL;
  NoAVL *raiz_avl = NULL, *raiz_avlFreq = NULL;
  inicializa_vetor(&vetor);
  menu(&vetor, &raiz_arvore, &raiz_avl, &raiz_avlFreq);
  liberar_vetor(&vetor);
  liberar_arvoreBinaria(raiz_arvore);
  liberar_arvoreAVL(raiz_avl);
  liberar_arvoreAVL(raiz_avlFreq);
  return 0;
}