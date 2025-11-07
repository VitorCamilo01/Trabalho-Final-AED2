# Projeto Final - Repositório de Letras de Músicas (AED2)

![Badge Disciplina](https://img.shields.io/badge/Disciplina-AED2%20(FACOM31303)-blue)
![Badge Linguagem](https://img.shields.io/badge/Linguagem-C-informational)

Este repositório contém o código-fonte do projeto final da disciplina **Algoritmos e Estruturas de Dados 2**.
## 📜 Visão Geral do Problema

O programa foi projetado para ler múltiplos arquivos de texto (`.txt`) contendo letras de músicas[cite: 28]. [cite_start]Ele processa cada palavra (com mais de 3 caracteres), converte-a para minúsculo e descarta espaços e pontuações.

As palavras são então armazenadas em três estruturas de dados distintas, organizadas em ordem alfabética:

1. **Vetor** (para Pesquisa Binária)
2. **Árvore Binária de Busca** 
3. **Árvore AVL** 

Cada palavra no repositório armazena uma tripla de informações: a própria palavra, dados da música onde ela aparece com maior frequência, e a contagem total da frequência da palavra em todo o repositório.

## ✨ Funcionalidades Implementadas

O programa apresenta um menu interativo que permite ao utilizador realizar as seguintes operações:

### A. Carregar Arquivos de Músicas
* O utilizador pode escolher arquivos de texto para serem lidos e processados.
* As palavras e suas informações são carregadas simultaneamente nas três estruturas de dados.
* Ao final do carregamento, o sistema exibe o **tempo de processamento (inserção)** para cada uma das três estruturas.
* **Lógica de Atualização:** Durante a inserção, se uma palavra já existente for encontrada, a contagem de frequência *total* no repositório é atualizada. Além disso, o sistema compara a frequência da palavra na *música atual* com a frequência da música *já armazenada*. Se a frequência da música atual for superior, os dados da música (nome, compositor, estrofe) são substituídos.

### B. Buscar por Palavra
* O utilizador pode digitar uma palavra para busca.
* O sistema realiza a busca nas três estruturas (Vetor, Árvore Binária de Busca e Árvore AVL).
* Para cada estrutura, o programa exibe as informações da música associada (nome, compositor(a), estrofe e frequência) e o **tempo de processamento da consulta**.

### C. Buscar por Frequência
* Permite ao utilizador buscar palavras com base na sua frequência total no repositório.
* Para garantir eficiência nesta busca, foi construída uma **quarta estrutura de dados**: uma Árvore AVL adicional, organizada pela frequência das palavras, e não pela ordem alfabética.

