#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define TAM_MEMORIA 256
#define ARGUMENTO_ARQUIVO_OBRIGATORIO "Argumento do arquivo é obrigatório!"

enum instrucao
{
    NOP = 0x00,
    STA = 0x10,
    LDA = 0x20,
    ADD = 0x30,
    OR = 0x40,
    AND = 0x50,
    NOT = 0x60,
    JMP = 0x80,
    JN = 0x90,
    JZ = 0xA0,
    HLT = 0xF0
};

void carregar_arquivo(const char *arquivo, uint8_t *acumulador, uint8_t *contador_programa, uint8_t *memoria)
{
    FILE *ponteiro_arquivo = fopen(arquivo, "rb");
    if (ponteiro_arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fread(memoria, sizeof(uint8_t), TAM_MEMORIA, ponteiro_arquivo);
    fclose(ponteiro_arquivo);

    *acumulador = memoria[1];
    *contador_programa = memoria[2];
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf(ARGUMENTO_ARQUIVO_OBRIGATORIO);
        return 1;
    }

    uint8_t acumulador = 0;
    uint8_t contador_programa = 0;
    uint8_t memoria[TAM_MEMORIA] = {0};
    int flag_n = 0;
    int flag_z = 0;

    carregar_arquivo(argv[1], &acumulador, &contador_programa, memoria);

    while (contador_programa < TAM_MEMORIA)
    {
        uint8_t instrucao = memoria[contador_programa];

        switch (instrucao)
        {
        case NOP:
            // Não faz nada
            break;
        case STA:
            contador_programa++;
            memoria[memoria[contador_programa]] = acumulador;
            break;
        case LDA:
            contador_programa++;
            acumulador = memoria[memoria[contador_programa]];
            break;
        case ADD:
            contador_programa++;
            acumulador += memoria[memoria[contador_programa]];
            break;
        case OR:
            contador_programa++;
            acumulador |= memoria[memoria[contador_programa]];
            break;
        case AND:
            contador_programa++;
            acumulador &= memoria[memoria[contador_programa]];
            break;
        case NOT:
            acumulador = ~acumulador;
            break;
        case JMP:
            contador_programa++;
            contador_programa = memoria[contador_programa] - 1;
            break;
        case JN:
            if (flag_n)
            {
                contador_programa++;
                contador_programa = memoria[contador_programa] - 1;
            }
            break;
        case JZ:
            if (flag_z)
            {
                contador_programa++;
                contador_programa = memoria[contador_programa] - 1;
            }
            break;
        case HLT:
            printf("Acumulador: %d\n", acumulador);
            printf("Contador de Programa: %d\n", contador_programa);
            printf("Flags: N = %d, Z = %d\n", flag_n, flag_z);
            return 0;
        default:
            break;
        }

        // Atualiza as flags
        flag_z = (acumulador == 0) ? 1 : 0;
        flag_n = (acumulador & 0x80) ? 1 : 0;

        contador_programa++;
    }

    return 0;
}
