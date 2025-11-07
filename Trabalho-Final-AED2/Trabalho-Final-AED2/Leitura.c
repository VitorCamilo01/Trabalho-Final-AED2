#include "Leitura.h"
#include "Arvore.h"
#include "Vetor.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void inicializar_contagem(ContagemMusica *contagem) {
  contagem->palavras = malloc(100 * sizeof(ContagemPalavra));
  if (!contagem->palavras) {
    printf("Erro ao alocar memória para contagem de palavras\n");
    exit(1);
  }
  contagem->tamanho = 0;
  contagem->capacidade = 100;
}

void atualizar_contagem(ContagemMusica *contagem, const char *palavra) {
  for (int i = 0; i < contagem->tamanho; i++) {
    if (strcmp(contagem->palavras[i].palavra, palavra) == 0) {
      contagem->palavras[i].frequencia++;
      return;
    }
  }

  if (contagem->tamanho >= contagem->capacidade) {
    contagem->capacidade *= 2;
    ContagemPalavra *temp = realloc(
        contagem->palavras, contagem->capacidade * sizeof(ContagemPalavra));
    if (!temp) {
      printf("Erro ao realocar memória para contagem de palavras\n");
      free(contagem->palavras);
      exit(1);
    }
    contagem->palavras = temp;
  }

  strncpy(contagem->palavras[contagem->tamanho].palavra, palavra, 100 - 1);
  contagem->palavras[contagem->tamanho].palavra[100 - 1] = '\0';
  contagem->palavras[contagem->tamanho].frequencia = 1;
  contagem->tamanho++;
}
void letras_minusculas(char *palavra) {
  for (int i = 0; i < strlen(palavra); i++) {
    palavra[i] = tolower(palavra[i]);
  }
}
void extrair_estrofe(char *letra, char *palavra, char *estrofe) {
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

void processar_letra(char *letra, char *nome_musica, char *compositor,
                     VetorDin *vetor, NoBin **raiz_arvore, NoAVL **raiz_avl,
                     NoAVL **raiz_avlFreq) {
  if (!letra || !nome_musica || !compositor) {
    printf("Parâmetros inválidos para processar_letra\n");
    return;
  }

  char *copia_letra = strdup(letra);
  if (!copia_letra) {
    printf("Erro ao duplicar string da letra\n");
    return;
  }

  char *palavra = strtok(copia_letra, " \t\n\r.,;:!?()[]{}'\"");

  ContagemMusica contagem;
  inicializar_contagem(&contagem);

  while (palavra != NULL) {
    letras_minusculas(palavra);

    if (strlen(palavra) > 3) {
      atualizar_contagem(&contagem, palavra);
    }

    palavra = strtok(NULL, " \t\n\r.,;:!?()[]{}'\"");
  }

  for (int i = 0; i < contagem.tamanho; i++) {
    char estrofe[101];
    extrair_estrofe(letra, contagem.palavras[i].palavra, estrofe);

    insere_vetor(vetor, contagem.palavras[i].palavra, nome_musica, compositor,
                 estrofe, contagem.palavras[i].frequencia);

    *raiz_arvore = inserir_arvoreBinaria(
        *raiz_arvore, contagem.palavras[i].palavra, nome_musica, compositor,
        estrofe, contagem.palavras[i].frequencia);

    *raiz_avl =
        inserir_arvoreAVL(*raiz_avl, contagem.palavras[i].palavra, nome_musica,
                          compositor, estrofe, contagem.palavras[i].frequencia);
    *raiz_avlFreq = inserir_arvoreAVL_frequencia(
        *raiz_avlFreq, contagem.palavras[i].palavra, nome_musica, compositor,
        estrofe, contagem.palavras[i].frequencia);
  }

  if (contagem.palavras) {
    free(contagem.palavras);
  }
  free(copia_letra);
}

void processar_arquivo(char *nome_arquivo, VetorDin *vetor, NoBin **raiz_arvore,
                       NoAVL **raiz_avl, NoAVL **raiz_avlFreq) {
  FILE *arquivo = fopen(nome_arquivo, "r");
  if (!arquivo) {
    printf("Erro ao abrir arquivo: %s\n", nome_arquivo);
    perror("Detalhes do erro");
    return;
  }

  char nome_musica[100], compositor[100];

  if (!fgets(nome_musica, sizeof(nome_musica), arquivo)) {
    printf("Erro ao ler nome da música\n");
    fclose(arquivo);
    return;
  }

  if (!fgets(compositor, sizeof(compositor), arquivo)) {
    printf("Erro ao ler compositor\n");
    fclose(arquivo);
    return;
  }

  nome_musica[strcspn(nome_musica, "\n")] = '\0';
  compositor[strcspn(compositor, "\n")] = '\0';

  fseek(arquivo, 0, SEEK_END);
  long tamanho = ftell(arquivo);
  fseek(arquivo, 0, SEEK_SET);

  if (tamanho <= 0) {
    printf("Arquivo vazio ou erro ao obter tamanho\n");
    fclose(arquivo);
    return;
  }

  char *letra = malloc(tamanho + 1);
  if (!letra) {
    printf("Erro ao alocar memória para o conteúdo do arquivo\n");
    fclose(arquivo);
    return;
  }

  size_t bytes_lidos = fread(letra, 1, tamanho, arquivo);
  letra[bytes_lidos] = '\0';

  char *inicio_letra = letra;
  int linhas_puladas = 0;

  while (*inicio_letra && linhas_puladas < 2) {
    if (*inicio_letra == '\n') {
      linhas_puladas++;
    }
    inicio_letra++;
  }

  if (linhas_puladas == 2 && *inicio_letra) {
    processar_letra(inicio_letra, nome_musica, compositor, vetor, raiz_arvore,
                    raiz_avl, raiz_avlFreq);
  } else {
    printf("Formato de arquivo inválido\n");
  }

  free(letra);
  fclose(arquivo);
}

void exibir_resultado(Entrada *entrada) {
  if (entrada) {
    printf("\n\nMúsica: %s\n", entrada->musica.nome);
    printf("Compositor: %s\n\n", entrada->musica.compositor);
    printf("Estrofe: %s\n", entrada->musica.trecho);
    printf("\nFrequência na música: %d\n", entrada->musica.frequencia);
    printf("Frequência total: %d\n", entrada->frequencia);
  } else {
    printf("Palavra não encontrada no repositório.\n");
  }
}

void carregar_arquivos(VetorDin *vetor, NoBin **raiz_arvore, NoAVL **raiz_avl,
                       NoAVL **raiz_avlFreq) {
  char nome_arquivo[100];
  printf("Digite o nome do arquivo (ou 'sair' para terminar): ");
  scanf("%99s", nome_arquivo);

  while (strcmp(nome_arquivo, "sair") != 0) {
    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio); 

    processar_arquivo(nome_arquivo, vetor, raiz_arvore, raiz_avl, raiz_avlFreq);

    clock_gettime(CLOCK_MONOTONIC, &fim); 

  double tempo = (fim.tv_sec - inicio.tv_sec) +
                     (fim.tv_nsec - inicio.tv_nsec) / 1e9;

  printf("Arquivo %s processado em %.8f segundos.\n\n", nome_arquivo, tempo);

    printf("Digite o nome do próximo arquivo (ou 'sair' para terminar): ");
    scanf("%99s", nome_arquivo);
  }
    system("clear");
    ordenar_vetor(vetor);
}
void buscar_palavra(VetorDin *vetor, NoBin *raiz_arvore, NoAVL *raiz_avl) {

  char palavra[100];
  printf("Digite a palavra a ser buscada: ");
  scanf("%49s", palavra);
  letras_minusculas(palavra);

  printf("\n=== Resultados para \"%s\" ===\n", palavra);

  struct timespec inicio, fim;
  double tempo_decorrido;

  
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  Entrada *resultado_vetor = buscaBin_vetor(vetor, palavra);
  clock_gettime(CLOCK_MONOTONIC, &fim);

  tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

  printf("\n--------------------------------------------------------\n\n");
  printf("\nVetor (busca binária):");
  exibir_resultado(resultado_vetor);
  printf("\nTempo: %.8f segundos\n", tempo_decorrido);
  printf("\n--------------------------------------------------------\n\n");

  
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  Entrada *resultado_arvore = buscar_arvoreBinaria(raiz_arvore, palavra);
  clock_gettime(CLOCK_MONOTONIC, &fim);

  tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

  printf("\nÁrvore Binária:");
  exibir_resultado(resultado_arvore);
  printf("\nTempo: %.8f segundos\n", tempo_decorrido);
  printf("\n--------------------------------------------------------\n\n");

  
  clock_gettime(CLOCK_MONOTONIC, &inicio);
  Entrada *resultado_avl = buscar_arvoreAVL(raiz_avl, palavra);
  clock_gettime(CLOCK_MONOTONIC, &fim);

  tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

  printf("\nÁrvore AVL:");
  exibir_resultado(resultado_avl);
  printf("\nTempo: %.8f segundos\n", tempo_decorrido);
  printf("\n--------------------------------------------------------\n\n");

  printf("Pressione Enter para continuar...\n");
  getchar();
  getchar();
  system("clear");
}

void buscar_frequencia(NoAVL *raiz_avlFreq) {
  char palavra[100];
  printf("Digite a palavra a ser buscada: ");
  scanf("%49s", palavra);
  letras_minusculas(palavra);

  struct timespec inicio, fim;
  clock_gettime(CLOCK_MONOTONIC, &inicio); 

  Entrada *resultado_avl = buscar_arvoreAVL(raiz_avlFreq, palavra);

  clock_gettime(CLOCK_MONOTONIC, &fim); 

  double tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

  printf("\n--------------------------------------------------------\n\n");
  printf("\nÁrvore AVL (frequência) :");
  exibir_resultado(resultado_avl);
  printf("\nTempo: %.8f segundos\n", tempo_decorrido);
  printf("\n--------------------------------------------------------\n\n");

  printf("Pressione Enter para continuar...\n");
  getchar();
  getchar();
  system("clear");
  
}

// * MENU:

void menu(VetorDin *vetor, NoBin **raiz_arvore, NoAVL **raiz_avl,
          NoAVL **raiz_avlFreq) {
  int opcao;
  int freq;
  do {
    printf("--------------- MENU (métodos de busca) ---------------\n\n");
    printf("Olá, seja bem vindo(a)!\n\n");
    printf("Para pesquisar uma palavra, em um arquivo texto, que contém "
           "músicas distintas...\n\n");
    printf("Escolha uma das opções abaixo: \n\n");
    printf("1. Carregar músicas do arquivo\n");
    printf("2. Buscar palavra\n");
    printf("3. Buscar por frequência\n");
    printf("4. Sair\n\n");
    printf("--------------------------------------------------------\n\n");
    printf("=> Opção: ");

    scanf("%d", &opcao);

    system("clear");

    switch (opcao) {

    case 1:
      carregar_arquivos(vetor, raiz_arvore, raiz_avl, raiz_avlFreq);
      break;
    case 2:
      buscar_palavra(vetor, *raiz_arvore, *raiz_avl);
      break;
    case 3:
      buscar_frequencia(*raiz_avlFreq);
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

