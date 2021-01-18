/**
 * @file Main.c
 * 
 * @author (8200378) <b>Daniel Teixeira</b>
 * @author (8200386) <b>Pedro Alves</b> 
 * @author (8200691) <b>Misael Rodrigues</b>
 * 
 * @date 15 de janeiro de 2021
 * 
 * @brief Projeto de <i>Avaliação Contínua</i> da UC <i>Laboratório de Programação</i> em 2020/2021
 */

#include <stdio.h>
#include <stdlib.h>

#include "funcionarios.h"
#include "input.h"

int main() {
    int opcao;
    char op6, op7, op8, op9;

    int *N_FUNC;
    *N_FUNC = 1;

    int *CONTADOR_F;
    *CONTADOR_F = 0;

    Funcionario *funcionarios;
    funcionarios = (Funcionario*) calloc(*N_FUNC, sizeof (Funcionario));

    Funcionario *funcionariosTMP;
    if (*CONTADOR_F == *N_FUNC) {
        funcionariosTMP = (Funcionario*) realloc(funcionarios, (*CONTADOR_F) * sizeof (Funcionario));
        if (funcionariosTMP != NULL) {
            *funcionarios = *funcionariosTMP;
        }
    }

    do {

        puts("\n********** MENU PRINCIPAL **********");
        puts("1 - Criar registo de Funcionário");
        puts("2 - Procurar registo do Funcionário");
        puts("3 - Editar registo do Funcionário");
        puts("4 - Remover registo do Funcionário");
        puts("5 - Listar registos dos Funcionários");
        puts("6 - Calcular Salário");
        puts("7 - Relatórios/Listagens");
        puts("8 - Ler/Importar dados");
        puts("9 - Gravar/Exportar dados");
        puts("0 - Sair");
        puts("************************************");
        printf("Funcionários: %d\n", *CONTADOR_F);
        
        //Ler opção do MENU
        printf("Insira a opção: ");
        scanf("%u", &opcao);
        
        while (opcao < 0 || opcao > 9) {
            printf("Insira a opção: ");
            scanf("%u", &opcao);
        }

        switch (opcao) {
            case 0:
                free(funcionarios);
                break;
            case 1:
                inserirFuncionarios(funcionarios, CONTADOR_F);
                break;
            case 2:
                procurarFuncionarios(funcionarios, CONTADOR_F);
                break;
            case 3:
                atualizarFuncionarios(funcionarios, CONTADOR_F);
                break;
            case 4:
                removerFuncionarios(funcionarios, CONTADOR_F);
                break;
            case 5:
                listarFuncionarios(funcionarios, CONTADOR_F);
                break;
            case 6:
                puts("\n !!!!!!!!!! AVISO !!!!!!!!!!");
                puts("Caso já exista algum processa-");
                puts("mento será alterado!");
                puts("------------------------------");

                printf("Deseja continuar? [S/N]: ");
                scanf(" %c", &op6);

                if (op6 == 'S') {
                    calcularSalarios(funcionarios, CONTADOR_F);
                }
                break;

            case 7:
                puts("\n !!!!!!!!!! AVISO !!!!!!!!!!");
                puts("Caso já exista informação nos");
                puts("ficheiros será alterada!");
                puts("------------------------------");

                printf("Deseja continuar? [S/N]: ");
                scanf(" %c", &op7);

                if (op7 == 'S') {
                    Relatorios(funcionarios, CONTADOR_F);
                    puts("Relaórios/Listagem exportados para ficheiros");
                }
                break;
            case 8:
                puts("\n !!!!!!!!!! AVISO !!!!!!!!!!");
                puts("Caso já exista informação nos");
                puts("ficheiros será alterada!");
                puts("------------------------------");

                printf("Deseja continuar? [S/N]: ");
                scanf(" %c", &op8);

                if (op8 == 'S') {
                    obterDadosFX(funcionarios, CONTADOR_F);
                }
                break;
            case 9:
                puts("\n !!!!!!!!!! AVISO !!!!!!!!!!");
                puts("Caso já exista informação nos");
                puts("ficheiros será alterada!");
                puts("------------------------------");

                printf("Deseja continuar? [S/N]: ");
                scanf(" %c", &op9);

                if (op9 == 'S') {
                    gravarInfoFuncionariosFX(funcionarios, CONTADOR_F);
                    gravarDiasFuncionariosFX(funcionarios, CONTADOR_F);
                }
                break;
            default:
                puts("OPÇÃO INVÁLIDA! (0-9)");
        }
    } while (opcao != 0);
    puts("PROGRAMA ENCERRADO!");
    return 0;
}

