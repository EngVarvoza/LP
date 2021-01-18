/**
 * @file funcionarios.c
 * 
 * @author (8200378) <b>Daniel Teixeira</b>
 * @author (8200386) <b>Pedro Alves</b> 
 * @author (8200691) <b>Misael Rodrigues</b>
 * 
 * @date 15 de janeiro de 2021
 */

#include <stdio.h>
#include <string.h>

#include "input.h"

/**
 * Função para a limpeza do Buffer
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Função projetada para obter valores do tipo de dados 'int'
 * 
 * @param minValor Valor mínimo a obter
 * @param maxValor Valor máximo a obter
 * @param msg Mensagem associada ao valor a obter
 * 
 * @return valor Valor a obter
 * 
 * @pre Limpeza do buffer a cada obtenção
 */
int obterInt(int minValor, int maxValor, char *msg) {
    int valor;
    printf(msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função projetada para obter valores do tipo de dados 'float'
 * 
 * @param minValor Valor mínimo a obter
 * @param maxValor Valor máximo a obter
 * @param msg Mensagem associada ao valor a obter
 * 
 * @return valor Valor a obter
 * 
 * @pre Limpeza do buffer a cada obtenção
 */
float obterFloat(float minValor, float maxValor, char *msg) {
    float valor;
    printf(msg);
    while (scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função projetada para obter valores do tipo de dados 'double'
 * 
 * @param minValor Valor mínimo a obter
 * @param maxValor Valor máximo a obter
 * @param msg Mensagem associada ao valor a obter
 * 
 * @return valor Valor a obter
 * 
 * @pre Limpeza do buffer a cada obtenção
 */
double obterDouble(double minValor, double maxValor, char *msg) {
    double valor;
    printf(msg);
    while (scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

/**
 * Função projetada para obter valores do tipo de dados 'char'
 * 
 * @param msg Mensagem associada ao caracter a obter
 * 
 * @return valor Caracter a obter
 * 
 * @pre Limpeza do buffer a cada obtenção
 */
char obterChar(char *msg) {
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}

/**
 * Função para obter "strings"
 * 
 * @param string Array destinado a guardar a string
 * @param tamanho Tamanho máximo da string
 * @param msg Mensagem associada à string a obter
 */
void lerString(char *string, unsigned int tamanho, char *msg) {
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}