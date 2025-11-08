#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------- TAMANHO MAX DE ITENS ------///
#define TAM_MAX 10

// --------- Definição da Estrutura (Struct) -------

struct Item {
  char nome[30];
  char tipo[20];
  int quantidade;
};

//
typedef struct {
  struct Item itens[TAM_MAX]; 
  int totalDeItens;      
} Mochila;

// -------- Limpar Buffer de entrada ---------
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// -------- Função auxiliar para remover '\n' do fgets -------

void removerQuebraLinha(char *str) {
  size_t len = strlen(str);
  if (len > 0 && str[len - 1] == '\n') {
    str[len - 1] = '\0';
  }
}

// ---------- Funções ------------ //

void inicializarMochila(Mochila *Mochila);
void removerMochila(Mochila *Mochila, const char *texto);
void inserirMochila(Mochila *Mochila);
void listarMochila(const Mochila *Mochila);

// --------- Codigo Principal -----//

int main() {
  Mochila minhaMochila;
  inicializarMochila(&minhaMochila);

  int opcao;
  do {
    printf("\n -- Bem vindo a ILHA -- \n");
    printf("1. Cadastre Itens\n");
    printf("2. Remova Itens\n");
    printf("3. Liste Todos os Itens\n");
    printf("0. Saia da Ilha\n");
    printf("Faça sua Escolha: ");
    scanf("%d", &opcao);
    printf("\n");
    limparBufferEntrada();

    switch (opcao) {
    case 1:
      inserirMochila(&minhaMochila);
      break;
    case 2:
      char nomeParaRemover[30];
      printf("Qual Item deseja remover? \n");
      fgets(nomeParaRemover, 30, stdin); 
      removerQuebraLinha(nomeParaRemover);
      removerMochila(&minhaMochila, nomeParaRemover);
      break;
    case 3:
      listarMochila(&minhaMochila);
      break;
    case 0:
      printf("Saindo..\n"); 
      break;
    default:
      printf("Opção inválida!\n");
      break;
    }

  } while (opcao != 0);
  return 0;
}

/// --------- Implementação das funções ------ ////

void inicializarMochila(Mochila *Mochila) {
  Mochila->totalDeItens = 0;
}
void inserirMochila(Mochila *Mochila) {
  if (Mochila->totalDeItens == TAM_MAX) {
    printf("Sua Mochila está cheia, jogue algum item fora.\n");
    return;
  }
  printf("Nome do Item: ");
  fgets(Mochila->itens[Mochila->totalDeItens].nome, 30, stdin);
  removerQuebraLinha(
      Mochila->itens[Mochila->totalDeItens].nome);

  printf("Tipo do Item: ");
  fgets(Mochila->itens[Mochila->totalDeItens].tipo, 20, stdin);
  removerQuebraLinha(
      Mochila->itens[Mochila->totalDeItens].tipo);

  printf("Quantidade: ");
  scanf("%d", &Mochila->itens[Mochila->totalDeItens].quantidade);
  limparBufferEntrada();
  Mochila->totalDeItens++;
} 

void removerMochila(Mochila *Mochila, const char *texto) {
  int i, pos = -1;
  for (i = 0; i < Mochila->totalDeItens; i++) {
    if ((strcmp(Mochila->itens[i].nome, texto) == 0)) {
      pos = i;
      break;
    }
  }
  if (pos == -1) {
    printf("Item \"%s\" não encontrado, verique novamente \n", texto);
    return;
  }

  for (i = pos; i < Mochila->totalDeItens - 1; i++) {
    Mochila->itens[i] = Mochila->itens[i + 1];
  }

  Mochila->totalDeItens--;
  printf("Item \"%s\" removido com sucesso !\n", texto);
}

void listarMochila(const Mochila *Mochila) {
  if (Mochila->totalDeItens == 0) {
    printf("A sua mochila está vazia \n");
    return;
  }
  printf("\n-- Itens da Mochila --\n");
  for (int i = 0; i < Mochila->totalDeItens; i++) {
    printf("Item: %s\n", Mochila->itens[i].nome);
    printf("Tipo: %s\n", Mochila->itens[i].tipo);
    printf("Qtd.: %d\n", Mochila->itens[i].quantidade);
    printf("------------------------\n");
  }

}