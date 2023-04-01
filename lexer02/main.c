#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 1000

typedef enum Token
{
    Mais,
    Menos,
    Multiplicacao,
    Divisao,
    Potenciacao,
    Numero,
    Indeterminado,
} Token;

struct Tokens
{
    enum Token token;
    union
    {
        char op;
        int num;
    } value;
};

void tokenizar(char *caracteres, int lenth, struct Tokens *vetorTokens, int *numTokens)
{
    int i = 0;
    int j = 0;
    while (i < lenth)
    {
        switch (caracteres[i])
        {
        case '+':
            vetorTokens[j].token = Mais;
            vetorTokens[j].value.op = '+';
            i++;
            j++;
            break;
        case '-':
            vetorTokens[j].token = Menos;
            vetorTokens[j].value.op = '-';
            i++;
            j++;
            break;
        case '*':
            if (caracteres[i + 1] == '*')
            {
                vetorTokens[j].token = Potenciacao;
                vetorTokens[j].value.op = '*';
                i += 2;
            }
            else
            {
                vetorTokens[j].token = Multiplicacao;
                vetorTokens[j].value.op = '*';
                i++;
            }
            j++;
            break;
        case '/':
            vetorTokens[j].token = Divisao;
            vetorTokens[j].value.op = '/';
            i++;
            j++;
            break;
        case ' ':
            i++;
            break;
        default:
            if (isdigit(caracteres[i]))
            {
                vetorTokens[j].token = Numero;
                vetorTokens[j].value.num = caracteres[i] - '0';
                i++;
            }
            else
            {
                vetorTokens[j].token = Indeterminado;
                vetorTokens[j].value.op = caracteres[i];
                i++;
            }
            j++;
        }
    }
    *numTokens = j;
}

int main(int argc, char **argv)
{
    char content[MAX_SIZE];
    FILE *fp;
    int i = 0;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (fgets(content, MAX_SIZE, fp) != NULL)
    {
        for (i = 0; content[i] != '\0'; i++)
            ;
    }
    fclose(fp);

    struct Tokens vetorTokens[i];
    int numTokens;
    tokenizar(content, i, vetorTokens, &numTokens);

    for (int k = 0; k < numTokens; k++)
    {
        if (vetorTokens[k].token == Mais)
            printf("Mais: +\n");
        else if (vetorTokens[k].token == Menos)
            printf("Menos: -\n");
        else if (vetorTokens[k].token == Multiplicacao)
            printf("Multiplicação: *\n");
        else if (vetorTokens[k].token == Divisao)
            printf("Divisão: /\n");
        else if (vetorTokens[k].token == Potenciacao)
            printf("Potenciação: **\n");
        else if (vetorTokens[k].token == Numero)
            printf("Número: %d\n", vetorTokens[k].value.num);
        else if (vetorTokens[k].token == Indeterminado)
        {
            printf("Indeterminado: ");
            printf("%c\n", vetorTokens[k].value.op);
        }
    }

    return 0;
}