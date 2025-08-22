#include "Leitura.h"
#include "Arvore.h"
#include "Vetor.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void letras_minusculas(char *palavra) {
  for (int i = 0; i < strlen(palavra); i++) {
    palavra[i] = tolower(palavra[i]);
  }
}
void extrair_estrofe( char *letra,  char *palavra, char *estrofe) {
  const char *pos = strstr(letra, palavra);
  if (pos) {
    int inicio = pos - letra;
    inicio = inicio > 30 ? inicio - 30 : 0;
    strncpy(estrofe, letra + inicio, 101 - 1);
    estrofe[101 - 1] = '\0';
    char *ultimo_espaco = strrchr(estrofe, ' ');
    if (ultimo_espaco && (estrofe + strlen(estrofe) - ultimo_espaco) > 20) {
      *ultimo_espaco = '\0';
    }
  } else {
    strncpy(estrofe, letra, 101 - 1);
    estrofe[101 - 1] = '\0';
  }
}

void processar_letra( char *letra,  char *nome_musica,
                      char *compositor, VetorDin *vetor,
                     NoBin **raiz_arvore, NoAVL **raiz_avl) {
  char *copia_letra = strdup(letra);
  char *palavra = strtok(copia_letra, " \t\n\r.,;:!?()[]{}'\"");

  while (palavra != NULL) {
    letras_minusculas(palavra);

    if (strlen(palavra) > 3) {
      char estrofe[101];
      extrair_estrofe(letra, palavra, estrofe);
      insere_vetor(vetor, palavra, nome_musica, compositor, estrofe);
      *raiz_arvore = inserir_arvoreBinaria(*raiz_arvore, palavra, nome_musica,
                                           compositor, estrofe);
      //insere_arvore_avl(raiz_avl, palavra, nome_musica, compositor, estrofe);
    }

    palavra = strtok(NULL, " \t\n\r.,;:!?()[]{}'\"");
  }

  free(copia_letra);
}

void processar_arquivo( char *nome_arquivo, VetorDin *vetor,
                       NoBin **raiz_arvore, NoAVL **raiz_avl) {
  FILE *arquivo = fopen(nome_arquivo, "r");
  if (!arquivo) {
    perror("Erro ao abrir arquivo");
    return;
  }

  char nome_musica[100], compositor[100];
  fgets(nome_musica, 100, arquivo);
  fgets(compositor, 100, arquivo);

  nome_musica[strcspn(nome_musica, "\n")] = '\0';
  compositor[strcspn(compositor, "\n")] = '\0';

  fseek(arquivo, 0, SEEK_END);
  long tamanho = ftell(arquivo);
  fseek(arquivo, 0, SEEK_SET);

  char *letra = malloc(tamanho + 1);
  fread(letra, 1, tamanho, arquivo);
  letra[tamanho] = '\0';

  char *inicio_letra = strchr(letra, '\n');
  if (inicio_letra)
    inicio_letra = strchr(inicio_letra + 1, '\n');
  if (inicio_letra)
    inicio_letra++;

  if (inicio_letra) {
    processar_letra(inicio_letra, nome_musica, compositor, vetor, raiz_arvore,
                    raiz_avl);
  }

  free(letra);
  fclose(arquivo);
}

void exibir_resultado( Entrada *entrada) {
    if (entrada) {
        printf("\nMúsica: %s\n", entrada->musica.nome); 
        printf("Compositor: %s\n", entrada->musica.compositor);
        printf("Estrofe: %s\n", entrada->musica.trecho); 
        printf("Frequência na música: %d\n", entrada->musica.frequencia); 
        printf("Frequência total: %d\n", entrada->frequencia); 
    } else {
        printf("Palavra não encontrada no repositório.\n");
    }
}
void carregar_arquivos(VetorDin *vetor, NoBin **raiz_arvore, NoAVL **raiz_avl) {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo (ou 'sair' para terminar): ");
    scanf("%99s", nome_arquivo);
    
    while (strcmp(nome_arquivo, "sair") != 0) {
        clock_t inicio = clock();
        processar_arquivo(nome_arquivo, vetor, raiz_arvore, raiz_avl);
        clock_t fim = clock();
        
        double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
        printf("Arquivo %s processado em %.4f segundos.\n", nome_arquivo, tempo);
        
        printf("Digite o nome do próximo arquivo (ou 'sair' para terminar): ");
        scanf("%99s", nome_arquivo);
    }
    
    ordenar_vetor(vetor);
}
void buscar_palavra(VetorDin *vetor, NoBin *raiz_arvore, NoAVL *raiz_avl) {
    char palavra[100];
    printf("Digite a palavra a ser buscada: ");
    scanf("%49s", palavra);
    letras_minusculas(palavra);
    
    printf("\n=== Resultados para \"%s\" ===\n", palavra);
    
    clock_t inicio = clock();
    Entrada *resultado_vetor = buscaBin_vetor(vetor, palavra);
    clock_t fim = clock();
    printf("\nVetor (busca binária):");
    exibir_resultado(resultado_vetor);
    printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    inicio = clock();
    Entrada *resultado_arvore = buscar_arvoreBinaria(raiz_arvore, palavra);
    fim = clock();
    printf("\nÁrvore Binária:");
    exibir_resultado(resultado_arvore);
    printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    // inicio = clock();
    // Entrada *resultado_avl = buscar_avl(raiz_avl, palavra);
    // fim = clock();
    // printf("\nÁrvore AVL:");
    // exibir_resultado(resultado_avl);
    // printf("Tempo: %.6f segundos\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
}
// * MENU:

void menu(VetorDin *vetor, NoBin **raiz_arvore,NoAVL **raiz_avl) {
  int opcao;
  do {

    printf("--------------- MENU (métodos de busca) ---------------\n\n");
    printf("Olá, seja bem vindo(a)!\n\n");
    printf("Para pesquisar uma palavra, em um arquivo texto, que contém "
           "músicas distintas...\n\n");
    printf("Escolha uma das opções abaixo: \n\n");
    printf("1. Carregar músicas do arquivo\n");
    printf("2. Buscar palavra\n");
    printf("3. Buscar por frequência\n");
    printf("4. Sair\n");
    printf("--------------------------------------------------------\n\n");
    printf("=> Opção: ");

    scanf("%d", &opcao);

    switch (opcao) {

    case 1:
      carregar_arquivos(vetor, raiz_arvore, raiz_avl);
      break;

      break;
    case 2:
      buscar_palavra(vetor, *raiz_arvore, *raiz_avl);
      break;
    case 3:
      break;
    case 4:
      printf("Encerrando o programa...\n");
      break;
    default:
      printf("Opção inválida, tente novamente.\n");
      break;
    }

  } while (opcao != 4);
}
