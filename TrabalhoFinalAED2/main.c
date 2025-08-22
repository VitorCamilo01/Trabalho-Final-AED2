/* -> Discentes: Giovana de Almeida Faria, Vitor Rodrigues Guimarães Camilo e Samuel Amorim
-> Matrículas: 12421BCC023, 12311ECP009 e 12411BCC
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h> 
#include "Leitura.h"
#include "Vetor.h"
#include "Arvore.h"

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");  
    VetorDin vetor;
    NoBin *raiz_arvore = NULL;
    NoAVL *raiz_avl = NULL;  
    inicializa_vetor(&vetor);
    
    menu(&vetor, &raiz_arvore, &raiz_avl);
    liberar_vetor(&vetor);
    // liberar_arvore(raiz_arvore);
    // liberar_avl(raiz_avl);
    
    return 0;
}