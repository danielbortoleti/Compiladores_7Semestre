#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

typedef enum Token {
  Mais,
  Menos,
  Multiplicacao,
  Divisao,
  Indeterminado,
} Token;

struct Tokens {
  enum Token token;
  char value;
};

void tokenizar(char *caracteres, int lenth, struct Tokens *vetorTokens) {
  int i = 0;
  while (i < lenth){
    switch (caracteres[i]) {
      case '+':
        vetorTokens[i].token = Mais;
        vetorTokens[i].value = '+';
        i++;
        break;
      case '-':
        vetorTokens[i].token = Menos;
        vetorTokens[i].value = '-';
        i++;
        break;
	case '*':
        vetorTokens[i].token = Multiplicacao;
        vetorTokens[i].value = '*';
        i++;
        break;
	case '/':
        vetorTokens[i].token = Divisao;
        vetorTokens[i].value = '/';
        i++;
        break;		
      case ' ':
        i++;
        break;
      default:
        vetorTokens[i].token = Indeterminado;
        vetorTokens[i].value = caracteres[i];
        i++;
    }
  }
}

int main(int argc, char** argv) {
  char content[MAX_SIZE];
  FILE *fp;
  int i = 0; 

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  while (fgets(content, MAX_SIZE, fp) != NULL) {
    for (i = 0; content[i] != '\0'; i++)
      ;
  }
  fclose(fp);

  struct Tokens vetorTokens[i];
  tokenizar(content, i, vetorTokens);

  for (int k = 0; k < i; k++){
    if (vetorTokens[k].token == Mais)
      printf("Mais: +\n");
    else if (vetorTokens[k].token == Menos)
      printf("Menos: -\n");
	else if (vetorTokens[k].token == Multiplicacao)
      printf("Multiplicação: *\n");	
	else if (vetorTokens[k].token == Divisao)
      printf("Divisão: /\n");	
    else if (vetorTokens[k].token == Indeterminado){
      printf("Indeterminado: ");
      printf("%c\n",vetorTokens[k].value);
    }
  }
  
  return 0;
}
