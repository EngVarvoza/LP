/**
 * @file funcionarios.c
 * 
 * @author (8200378) <b>Daniel Teixeira</b>
 * @author (8200386) <b>Pedro Alves</b> 
 * @author (8200691) <b>Misael Rodrigues</b>
 * 
 * @date 15 de janeiro de 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionarios.h"
#include "input.h"

/**
 * Esta função imprime os dados do Funcionário 
 * 
 * @param funcionario Funcionário a imprimir
 * 
 * @todo: Imprime " Código | Nome | Data Nascimento (dd/mm/aaaa) | Situação"
 *  
 */
void imprimirFuncionario(Funcionario funcionario) {
    //Imprime os dados
    printf("%4d |%-20s | %c | %2d-%2d-%2d | %d\n",
            funcionario.codigo,
            funcionario.nome,
            funcionario.cargo,
            funcionario.nascimento.dia, funcionario.nascimento.mes, funcionario.nascimento.ano,
            funcionario.situacao);
}

/**
 * Esta função recebe o Funcionário que o utilizador pretender remover 
 * 
 * @param funcionario Funcionário a remover
 * 
 */
void removerFuncionario(Funcionario *funcionario) {
    (*funcionario).situacao = INATIVO;
}

/**
 * Esta função procura o Funcionário pelo seu Código
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador dos Funcionários
 * @param num Número do Código do Funcionário a procurar
 * 
 * @return posição do funcionário no array se este existir 
 * @return -1 se funcionário não existir
 * 
 */
int procurarFuncionario(Funcionario *funcionarios, int *CONTADOR_F, int num) {
    int i;
    for (i = 0; i < (*CONTADOR_F); i++) {
        //Procura nos códigos em mémoria o código digitado pelo utilizador
        if (funcionarios[i].codigo == num) {
            //Retorna a posição do funcionário se este existir
            return i;
        }
    }
    //Retorna -1 se o funcionário não existir
    return -1;
}

/**
 * Esta função permite inserir os dados do Funcionário a criar
 * 
 * @param funcionario Funcionários
 * @param CONTADOR_F contador dos Funcionários
 * 
 * @return incremento ao "CONTADOR_F" se o Funcionário ainda não existir 
 * @return -1 se o funcionário existir
 * 
 * @todo: Apenas insere o funcionário se o código pretendido ainda não existir
 * 
 * @pre Procurar Funcionário pelo seu Código
 */
int inserirFuncionario(Funcionario *funcionario, int *CONTADOR_F) {
    //Ler CÓDIGO
    int num = obterInt(V_MIN_CODIGO, V_MAX_CODIGO, MSG_CODIGO);

    if (procurarFuncionario(funcionario, CONTADOR_F, num) == -1) {
        funcionario[*CONTADOR_F].situacao = INATIVO;

        //Atribuir a variável local "codigo" ao elemento "codigo" da struct
        funcionario[*CONTADOR_F].codigo = num;

        //Ler NOME
        lerString(funcionario[*CONTADOR_F].nome, MAX_STRING, MSG_NOME);

        //Ler TELEFONE
        funcionario[*CONTADOR_F].telefone =
                obterInt(V_MIN_TELEFONE, V_MAX_TELEFONE, MSG_TELEFONE);

        //Ler ESTADO CIVIL
        funcionario[*CONTADOR_F].estado_civil =
                obterChar(MSG_ESTADOCIVIL);

        //Validar ESTADO CIVIL
        /* Enquanto o Estado Civil for diferente de 'S' ou 'C' fazer sucessiva-
         * mente a mesma pergunta até ser satisfeita a condição
         */
        while (funcionario[*CONTADOR_F].estado_civil != 'S' &&
                funcionario[*CONTADOR_F].estado_civil != 'C') {
            puts("A letra inserida é inválida.");
            funcionario[*CONTADOR_F].estado_civil =
                    obterChar(MSG_ESTADOCIVIL);
        }

        //Ler Nº DE TITULARES
        /* Como é sabido se o Estado Civil do funcionário for SOLTEIRO, ou seja,
         * NÃO CASADO então o número de Titulares é (0) zero, daí a atribuição 
         * automática de 0 Titulares. Caso o funcionário seja CASADO, então 
         * deve-se perguntar se é o único Titular ou se são 2 Titulares.
         */
        if (funcionario[*CONTADOR_F].estado_civil == 'S') {
            funcionario[*CONTADOR_F].titulares = 0;
        } else {
            funcionario[*CONTADOR_F].titulares =
                    obterInt(V_MIN_TITULARES, V_MAX_TITULARES, MSG_TITULARES);
        }

        //Ler DEPENDENTES
        funcionario[*CONTADOR_F].dependentes =
                obterInt(V_MIN_DEPENDENTES, V_MAX_DEPENDENTES, MSG_DEPENDENTES);

        //Ler CARGO
        funcionario[*CONTADOR_F].cargo = obterChar(MSG_CARGO);
        //Validar CARGO
        /* Enquanto o Cargo for diferente de 'A' ou 'C' ou 'E' perguntar suces-
         * -sivamente  a mesma pergunta até ser satisfeita a condição
         */
        while (funcionario[*CONTADOR_F].cargo != 'A'
                && funcionario[*CONTADOR_F].cargo != 'C'
                && funcionario[*CONTADOR_F].cargo != 'E') {
            funcionario[*CONTADOR_F].cargo = obterChar(MSG_CARGO);
        }

        /* Pelos enunciados das fichas das aulas de Laboratórios da Programação
         * cada cargo tem um Vencimento Base (€/dia) diferente. O mesmo acontece
         * com o Subsídio de Alimentação. Desta forma faz-se a atribuição auto-
         * máica para o Cargo do funcionário anteriormente inserido. 
         * Assim sendo:
         * 
         * (A) Administrador
         * Vencimento Base = 80,00€/dia
         * Subsídio de Alimentação = 7,50€/dia
         * 
         * (C) Chefe
         * Vencimento Base = 60,00€/dia
         * Subsídio de Alimentação = 7,50€/dia
         * 
         * (E) Empregado
         * Vencimento Base = 40,00€/dia
         * Subsídio de Alimentação = 5,00€/dia
         * 
         */
        if (funcionario[*CONTADOR_F].cargo == 'A') {
            puts("A : Vencimento Base - 80,00€");
            funcionario[*CONTADOR_F].venc_base = 80.00;
            puts("A : Subsídio de Alimentação - 7,50€");
            funcionario[*CONTADOR_F].sub_alimentacao = 7.50;
        } else if (funcionario[*CONTADOR_F].cargo == 'C') {
            puts("C : Vencimento Base - 60,00€");
            funcionario[*CONTADOR_F].venc_base = 60.00;
            puts("C : Subsídio de Alimentação - 7,50€");
            funcionario[*CONTADOR_F].sub_alimentacao = 7.50;
        } else if (funcionario[*CONTADOR_F].cargo == 'E') {
            puts("E : Vencimento Base - 40,00€");
            funcionario[*CONTADOR_F].venc_base = 40.00;
            puts("E : Subsídio de Alimentação - 5,00€");
            funcionario[*CONTADOR_F].sub_alimentacao = 5.00;
        }

        //Ler DATA DE NASCIMENTO
        funcionario[*CONTADOR_F].nascimento.dia =
                obterInt(V_MIN_DIAS, V_MAX_DIAS, MSG_D_NASCIMENTO);
        funcionario[*CONTADOR_F].nascimento.mes =
                obterInt(V_MIN_MES, V_MAX_MES, MSG_M_NASCIMENTO);
        funcionario[*CONTADOR_F].nascimento.ano =
                obterInt(V_MIN_A_NASCIMENTO, V_MAX_A_NASCIMENTO, MSG_A_NASCIMENTO);

        //Ler DATA DE ENTRADA NA EMPRESA
        funcionario[*CONTADOR_F].entrada.dia =
                obterInt(V_MIN_DIAS, V_MAX_DIAS, MSG_D_ENTRADA);
        funcionario[*CONTADOR_F].entrada.mes =
                obterInt(V_MIN_MES, V_MAX_MES, MSG_M_ENTRADA);
        funcionario[*CONTADOR_F].entrada.ano =
                obterInt(V_MIN_A_ENTRADA, V_MAX_A_ENTRADA, MSG_A_ENTRADA);

        //Ler DATA DE SAÍDA NA EMPRESA
        funcionario[*CONTADOR_F].saida.dia =
                obterInt(V_MIN_D_SAIDA, V_MAX_DIAS, MSG_D_SAIDA);
        funcionario[*CONTADOR_F].saida.mes =
                obterInt(V_MIN_M_SAIDA, V_MAX_MES, MSG_M_SAIDA);
        funcionario[*CONTADOR_F].saida.ano =
                obterInt(V_MIN_A_SAIDA, V_MAX_A_SAIDA, MSG_A_SAIDA);

        funcionario[*CONTADOR_F].situacao = ATIVO;
        return ((*CONTADOR_F)++);
    }
    return -1;
}

/**
 * Esta função permite alterar os dados de um Funcionário
 * 
 * @param funcionario Funcionário a alterar
 */
void atualizarFuncionario(Funcionario *funcionario) {

    //Ler NOME
    lerString((*funcionario).nome, MAX_STRING, MSG_NOME);

    //Ler TELEFONE
    (*funcionario).telefone = obterInt(V_MIN_TELEFONE, V_MAX_TELEFONE, MSG_TELEFONE);

    // Ler ESTADO CIVIL
    (*funcionario).estado_civil = obterChar(MSG_ESTADOCIVIL);
    
    //Validar ESTADO CIVIL
    /* Enquanto o Estado Civil for diferente de 'S' ou 'C' fazer sucessiva-
     * mente a mesma pergunta até ser satisfeita a condição
     */
    while ((*funcionario).estado_civil != 'S' && (*funcionario).estado_civil != 'C') {
        puts("A letra inserida é inválida.");
        (*funcionario).estado_civil = obterChar(MSG_ESTADOCIVIL);
    }
    
    //Ler Nº DE TITULARES
    /* Como é sabido se o Estado Civil do funcionário for SOLTEIRO, ou seja,
     * NÃO CASADO então o número de Titulares é (0) zero, daí a atribuição 
     * automática de 0 Titulares. Caso o funcionário seja CASADO, então 
     * deve-se perguntar se é o único Titular ou se são 2 Titulares.
    */
    if ((*funcionario).estado_civil == 'S') {
        (*funcionario).titulares = 0;
    } else {
        (*funcionario).titulares = obterInt(V_MIN_TITULARES, V_MAX_TITULARES, MSG_TITULARES);
    }

    //Ler DEPENDENTES
    (*funcionario).dependentes = obterInt(V_MIN_DEPENDENTES, V_MAX_DEPENDENTES, MSG_DEPENDENTES);

    //Ler CARGO
    (*funcionario).cargo = obterChar(MSG_CARGO);
    
    //Validar CARGO
    /* Enquanto o Cargo for diferente de 'A' ou 'C' ou 'E' perguntar suces-
     * -sivamente  a mesma pergunta até ser satisfeita a condição
    */
    while ((*funcionario).cargo != 'A' && (*funcionario).cargo != 'C' && (*funcionario).cargo != 'E') {
        (*funcionario).cargo = obterChar(MSG_CARGO);
    }

    //Ler VENCIMENTO BASE
    (*funcionario).venc_base = obterFloat(V_MIN_VENCBASE, V_MAX_VENCBASE, MSG_VENCBASE);

    //Ler SUBSÍDIO DE ALIMENTAÇÃO
    (*funcionario).sub_alimentacao = obterFloat(V_MIN_SUBALIM, V_MAX_SUBALIM, MSG_SUBALIM);

    //Ler DATA DE NASCIMENTO
    (*funcionario).nascimento.dia = obterInt(V_MIN_DIAS, V_MAX_DIAS, MSG_D_NASCIMENTO);
    (*funcionario).nascimento.mes = obterInt(V_MIN_MES, V_MAX_MES, MSG_M_NASCIMENTO);
    (*funcionario).nascimento.ano = obterInt(V_MIN_A_NASCIMENTO, V_MAX_A_NASCIMENTO, MSG_A_NASCIMENTO);

    //Ler DATA DE ENTRADA NA EMPRESA
    (*funcionario).entrada.dia = obterInt(V_MIN_DIAS, V_MAX_DIAS, MSG_D_ENTRADA);
    (*funcionario).entrada.mes = obterInt(V_MIN_MES, V_MAX_MES, MSG_M_ENTRADA);
    (*funcionario).entrada.ano = obterInt(V_MIN_A_ENTRADA, V_MAX_A_ENTRADA, MSG_A_ENTRADA);

    //Ler DATA DE SAÍDA NA EMPRESA
    (*funcionario).saida.dia = obterInt(V_MIN_D_SAIDA, V_MAX_DIAS, MSG_D_SAIDA);
    (*funcionario).saida.mes = obterInt(V_MIN_M_SAIDA, V_MAX_MES, MSG_M_SAIDA);
    (*funcionario).saida.ano = obterInt(V_MIN_A_SAIDA, V_MAX_A_SAIDA, MSG_A_SAIDA);

    //Ler SITUAÇÃO
    /* Permite "desremover" um funcionário que tenha sido removido do programa*/
    (*funcionario).situacao = obterInt(INATIVO, ATIVO, MSG_SITUACAO);
}


/**
 * Esta função permite inserir se se verificar que o Funcionário ainda não existe
 * 
 * @param funcionario Funcionarios
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: Apenas insere o funcionário se este ainda não existir
 */
void inserirFuncionarios(Funcionario *funcionario, int *CONTADOR_F) {
    //Verificar se o Funcionário não existe
    if (inserirFuncionario(funcionario, CONTADOR_F) == -1) {
        puts(ERRO_EXISTE);
    }
}

/**
 * Esta função realiza a procura de um Funcionário pelo seu Código
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_NAO_EXISTE" caso o Funcionário não existe
 * @todo: "ERRO_LISTA_VAZIA" caso não exista Funcionários na lista
 * 
 * @pre Procurar Funcionário pelo seu Código
 */
void procurarFuncionarios(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        //Ler para a variável local "num" o código do funcionário a procurar
        int num = procurarFuncionario(funcionarios, CONTADOR_F, obterInt(V_MIN_CODIGO, V_MAX_CODIGO, MSG_CODIGO));
        //Se o funcionário existir imprime-o se não imprime uma mensagem de aviso
        if (num != -1) {
            imprimirFuncionario(funcionarios[num]);
        } else {
            puts(ERRO_NAO_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função atualiza um Funcionario apartir do seu código
 *  
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_NAO_EXISTE" caso o funcionário não existe
 * @todo: "ERRO_LISTA_VAZIA" caso nao exista funcionários na lista
 * 
 * @pre Procurar Funcionário pelo seu Código
 */
void atualizarFuncionarios(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        //Ler para a variável local "num" o código do funcionário a procurar
        int num = procurarFuncionario(funcionarios, CONTADOR_F, obterInt(V_MIN_CODIGO, V_MAX_CODIGO, MSG_CODIGO));
        //Se o funcionário existir atualiza-o se não imprime uma mensagem de aviso
        if (num != -1) {
            atualizarFuncionario(&(funcionarios[num]));
        } else {
            puts(ERRO_NAO_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/** 
 * Esta função remove um determinado Funcionario apartir do seu código
 *  
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_NAO_EXISTE" caso o funcionário não existe
 * @todo: "ERRO_LISTA_VAZIA" caso nao exista funcionários na lista
 * 
 * @pre: Procurar Funcionário pelo seu Código
 */
void removerFuncionarios(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        //Ler para a variável local "num" o código do funcionário a procurar
        int num = procurarFuncionario(funcionarios, CONTADOR_F, obterInt(V_MIN_CODIGO, V_MAX_CODIGO, MSG_CODIGO));
        //Se o funcionário existir remove-o se não imprime uma mensagem de aviso
        if (num != -1) {
            removerFuncionario(&(funcionarios[num]));
        } else {
            puts(ERRO_NAO_EXISTE);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função tem como objetivo listar todos os Funcionários em memória 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Fúncionarios
 * 
 * @todo: Retorna "ERRO_LISTA_VAZIA" caso não exista funcionários
 * 
 */
void listarFuncionarios(Funcionario *funcionarios, int *CONTADOR_F) {
    if (*CONTADOR_F > 0) {
        int i;
        for (i = 0; i < *CONTADOR_F; i++) {
            imprimirFuncionario(funcionarios[i]);
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}



/**
 * Esta função tem lê os Dias do Funcionário
 * 
 * @param funcionario Funcionário
 * 
 * @todo: Lê os Dias : Completos, Meios, de Fim de Semana, de Faltas)
 */
void diasFuncionarios(Funcionario *funcionario) {
    //Imprimir o funcionário no qual vai inserir os dias    
    printf("\n%4d | %c | %-50s\n", (*funcionario).codigo, (*funcionario).cargo, (*funcionario).nome);

    //Ler DIAS COMPLETOS
    (*funcionario).salarioinfo.dias_completos =
            obterInt(V_MIN_DIASCOMPLETOS, V_MAX_DIAS, MSG_DIASCOMPLETOS);

    //Ler DIAS MEIO
    (*funcionario).salarioinfo.dias_meios =
            obterInt(V_MIN_DIASMEIO, V_MAX_DIAS, MSG_DIASMEIO);

    //Ler DIAS FIM DE SEMANA
    (*funcionario).salarioinfo.dias_fim_semana =
            obterInt(V_MIN_DIASFIMDS, V_MAX_DIAS, MSG_DIASFIMDS);

    //Ler DIAS FALTA
    (*funcionario).salarioinfo.dias_falta =
            obterInt(V_MIN_DIASFALTA, V_MAX_DIAS, MSG_DIASFALTA);
}

/**
 * Esta função calcula o Salário Bruto do Funcionário 
 * 
 * @param vencbase Vencimento Base do Funcionário
 * @param diasI número de dias completos trabalhados
 * @param diasM número de meios dias trabalhados
 * @param diasS número de dias trabalhados ao fim de semana
 * @param diasF número de dias de faltas
 * 
 * @return salariobruto Salário Bruto
 */
float bruto(float vencbase, int diasI, int diasM, int diasS, int diasF) {
    float salariobruto;
    salariobruto = ((vencbase * diasI) + ((vencbase / 2) * diasM) + ((vencbase * diasS) + ((vencbase / 2) * diasS)));

    return salariobruto;
}

/**
 * Esta função calcula o Subsídio de Alimentação do Funcionário
 * 
 * @param subalimentacao Valor do Subsídio de Alimentação
 * @param diasI número de dias completos trabalhados
 * 
 * @return subal Subsídio de Alimentação
 */
float alimentacao(float subalimentacao, int diasI) {
    float subal;
    subal = subalimentacao * diasI;

    return subal;
}

/**
 * Esta função tem calcula o Bónus de salário do Funcionário
 * 
 * @param sbruto Salário Bruto do Funcionário
 * @param diasF número de dias de faltas
 * 
 * @return Valor do Bónus
 */
float bonus(float sbruto, int diasF) {
    if (diasF == 0) {
        return (sbruto * BONUS0);
    } else if (diasF == 1) {
        return (sbruto * BONUS1);
    } else if (diasF >= 2 && diasF <= 3) {
        return (sbruto * BONUS2);
    } else {
        return 0;
    }

}

/**
 * Esta função tem como objetivo calcular o Salário Bruto, Subsídio de 
 * Alimentação e Bónus do Funcionário
 * 
 * 
 * @param funcionarios Funcionário
 * 
 * @pre Caso o valor de Dias Completos seja nulo (valor 0) volta a ler os valores dos Dias
 * 
 */
void calcBFuncionarios(Funcionario *funcionarios) {
    //Verificar se o funcionário não se encotra removido, se removido aos valores é atribuido 0
    if ((*funcionarios).situacao == ATIVO) {
        //Verificar se os dias trabalhados não são nulos (valor 0)
        if ((*funcionarios).salarioinfo.dias_completos == 0) {
            diasFuncionarios(&(*funcionarios));
        }
        
        //Cálculo do SALÁRIO BRUTO
        (*funcionarios).salariocalc.salarioB =
                bruto((*funcionarios).venc_base, (*funcionarios).salarioinfo.dias_completos,
                (*funcionarios).salarioinfo.dias_meios, (*funcionarios).salarioinfo.dias_fim_semana,
                (*funcionarios).salarioinfo.dias_falta);
        
        //Cálculo do SUBSÍDIO DE ALIMENTAÇÃO
        (*funcionarios).salariocalc.sub_alimentacao =
                alimentacao((*funcionarios).sub_alimentacao, (*funcionarios).salarioinfo.dias_completos);
        
        //Acréscimo ao Salário Bruto do Subsídio de Alimetação
        (*funcionarios).salariocalc.salarioB += (*funcionarios).salariocalc.sub_alimentacao;
        
        //Cálculo do BÓNUS
        (*funcionarios).salariocalc.bonus =
                bonus((*funcionarios).salariocalc.salarioB, (*funcionarios).salarioinfo.dias_falta);
        
        //Acréscimo ao Salário Bruto do Bónus
        (*funcionarios).salariocalc.salarioB += (*funcionarios).salariocalc.bonus;       
    } else {
        (*funcionarios).salariocalc.salarioB = 0;
        (*funcionarios).salariocalc.sub_alimentacao = 0;
        (*funcionarios).salariocalc.bonus = 0;
    }
}

/**
 * Esta função tem como objetivo calcular do Salário Líquido do Funcionário 
 * 
 * Esta função também realiza a leitura dos ficheiros das Taxas Contributivas 
 * para a Segurança Social e da Retenção do IRS  
 * 
 * Esta função realiza também o cálculo da TSU do Funcionário e da Entidade 
 * Patronal, relativo a cada Funcionário, e também da retenção do IRS do Funcionário
 * 
 * @param funcionarios Funcionário
 * 
 * @warning: O Ficheiro com as Taxas Contributivas da SS do Funcionário necessita de ter o nome "Taxas_Contributivas_F"
 * @warning: O Ficheiro com as Taxas Contributivas da SS da Entidade Patronal necessita de ter o nome "Taxas_Contributivas_EP"
 * @warning: O Ficheiro com as taxas de retenção de IRS para Solteiro necessita de ter o nome "Tabelas_Ret_IRS_2020_Continente_0"
 * @warning: O Ficheiro com as taxas de retenção de IRS para Casado 1 títular necessita de ter o nome "Tabelas_Ret_IRS_2020_Continente_1"
 * @warning: O Ficheiro com as taxas de retenção de IRS para Casado 2 títulares necessita de ter o nome "Tabelas_Ret_IRS_2020_Continente_2"
 * @warning: Os Ficheiros necessitam de estar em ".txt"
 */
void calcLFuncionarios(Funcionario *funcionarios) {
    //------------------------------------------------------------------------//
    // Leitura das Taxas Contributivas da SS para o Funcionário
    float *TABELA_TAXAS_SS_F;
    TABELA_TAXAS_SS_F = (float*) calloc(3, sizeof (float));
    
    int x;

    FILE * TAXAS_SS_F;  
    TAXAS_SS_F = fopen("Taxas_Contributivas_F.txt", "r");
    
    if (TAXAS_SS_F == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Taxas_Contributivas_F.txt'");
    }

    //Leitura dos valores do Ficheiro
    for (x = 0; x < 3; x++) {
        fscanf(TAXAS_SS_F, "%f", &(*(TABELA_TAXAS_SS_F + x)));
    }

    fclose(TAXAS_SS_F);

    //------------------------------------------------------------------------//
    // Leitura das Taxas Contributivas da SS para a Entidade Patronal
    
    float *TABELA_TAXAS_SS_EP;
    TABELA_TAXAS_SS_EP = (float*) calloc(3, sizeof (float));

    FILE * TAXAS_SS_EP;
    TAXAS_SS_EP = fopen("Taxas_Contributivas_EP.txt", "r");

    if (TAXAS_SS_EP == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Taxas_Contributivas_EP.txt'");
    }

    //Leitura dos valores do Ficheiro
    for (x = 0; x < 3; x++) {
        fscanf(TAXAS_SS_EP, "%f", &(*(TABELA_TAXAS_SS_EP + x)));
    }

    fclose(TAXAS_SS_EP);

    //------------------------------------------------------------------------//
    // Leitura das taxas de retanção de IRS para Solteiro
    
    float *TABELA_IRS_0;
    TABELA_IRS_0 = (float*) calloc(252, sizeof (float));

    FILE *IRS_0;
    IRS_0 = fopen("Tabelas_Ret_IRS_2020_Continente_0.txt", "r");

    if (IRS_0 == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Tabelas_Ret_IRS_2020_Continente_0.txt'");
    }
    
    //Leitura dos valores do Ficheiro
    for (x = 0; x < 252; x++) {
        fscanf(IRS_0, "%f", &(*(TABELA_IRS_0 + x)));
    }

    fclose(IRS_0);

    //------------------------------------------------------------------------//
    // Leitura das taxas de retanção de IRS para Casado 1 titular
    float *TABELA_IRS_1;
    TABELA_IRS_1 = (float*) calloc(252, sizeof (float));

    FILE *IRS_1;
    IRS_1 = fopen("Tabelas_Ret_IRS_2020_Continente_1.txt", "r");

    if (IRS_1 == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Tabelas_Ret_IRS_2020_Continente_1.txt'");
    }

    //Leitura dos valores do Ficheiro
    for (x = 0; x < 252; x++) {
        fscanf(IRS_1, "%f", &(*(TABELA_IRS_0 + x)));
    }

    fclose(IRS_1);

    //------------------------------------------------------------------------//
    // Leitura das taxas de retanção de IRS para Casado 2 titulares

    float *TABELA_IRS_2;
    TABELA_IRS_2 = (float*) calloc(252, sizeof (float));

    FILE *IRS_2;
    IRS_2 = fopen("Tabelas_Ret_IRS_2020_Continente_2.txt", "r");

    if (IRS_2 == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Tabelas_Ret_IRS_2020_Continente_2.txt'");
    }

    //Leitura dos valores do Ficheiro
    for (x = 0; x < 252; x++) {
        fscanf(IRS_2, "%f", &(*(TABELA_IRS_0 + x)));
    }

    fclose(IRS_2);

    //------------------------------------------------------------------------//
    
    //Verificar se o funcionário não está removido, se removido aos valores é atribuido 0
    if ((*funcionarios).situacao == ATIVO) {
        
        //Calcular TSU FUNCIONÁRIO
        if ((*funcionarios).cargo == *"A") {
            (*funcionarios).salariocalc.retencao_SS_F =
                    ((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                    - (*funcionarios).salariocalc.bonus) * (*(TABELA_TAXAS_SS_F));

        } else if ((*funcionarios).cargo == *"C") {
            (*funcionarios).salariocalc.retencao_SS_F =
                    ((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                    - (*funcionarios).salariocalc.bonus) * (*(TABELA_TAXAS_SS_F + 1));

        } else if ((*funcionarios).cargo == *"E") {
            (*funcionarios).salariocalc.retencao_SS_F =
                    ((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                    - (*funcionarios).salariocalc.bonus) * (*(TABELA_TAXAS_SS_F + 2));
        }

        //Calcular TSU ENTIDADE PATRONAL
        if ((*funcionarios).cargo == *"A") {
            (*funcionarios).salariocalc.retencao_SS_EP =
                    (((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                    - (*funcionarios).salariocalc.bonus) * (*(TABELA_TAXAS_SS_EP)));

        } else if ((*funcionarios).cargo == *"C") {
            (*funcionarios).salariocalc.retencao_SS_EP =
                    ((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                    - (*funcionarios).salariocalc.bonus) * (*(TABELA_TAXAS_SS_EP + 1));

        } else if ((*funcionarios).cargo == *"E") {
            (*funcionarios).salariocalc.retencao_SS_EP =
                    ((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                    - (*funcionarios).salariocalc.bonus) * (*(TABELA_TAXAS_SS_EP + 2));
        }


        int y;
        for (y = 0; y < 238; y++) {

            //Calcular IRS FUNCIONÁRIO : Titulares = 0 (Solteiro)
            if ((*funcionarios).titulares == 0) {
                
                if (((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                        - (*funcionarios).salariocalc.bonus) <= (*(TABELA_IRS_0 + y))) {

                    if ((*funcionarios).dependentes == 0) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + (y + 1))));


                    } else if ((*funcionarios).dependentes == 1) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + (y + 2))));

                    } else if ((*funcionarios).dependentes == 2) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + (y + 3))));

                    } else if ((*funcionarios).dependentes == 3) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + (y + 4))));

                    } else if ((*funcionarios).dependentes == 4) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + (y + 5))));

                    } else if ((*funcionarios).dependentes == 5) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + (y + 6))));
                    }

                } else {
                    if ((*funcionarios).dependentes == 0) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + 246)));

                    } else if ((*funcionarios).dependentes == 1) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + 247)));

                    } else if ((*funcionarios).dependentes == 2) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + 248)));

                    } else if ((*funcionarios).dependentes == 3) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + 249)));

                    } else if ((*funcionarios).dependentes == 4) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + 250)));

                    } else if ((*funcionarios).dependentes >= 5) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * (*(TABELA_IRS_0 + 251)));
                    }
                }
            }


            //Calcular IRS FUNCIONÁRIO : Titulares = 1 (Casado - 1 titular)
            if ((*funcionarios).titulares == 1) {
                if (((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                        - (*funcionarios).salariocalc.bonus) <= TABELA_IRS_1[y]) {

                    if ((*funcionarios).dependentes == 0) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[y + 1]);

                    } else if ((*funcionarios).dependentes == 1) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[y + 2]);

                    } else if ((*funcionarios).dependentes == 2) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[y + 3]);

                    } else if ((*funcionarios).dependentes == 3) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[y + 4]);

                    } else if ((*funcionarios).dependentes == 4) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[y + 5]);

                    } else if ((*funcionarios).dependentes == 5) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[y + 6]);
                    }

                } else {
                    if ((*funcionarios).dependentes == 0) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[246]);

                    } else if ((*funcionarios).dependentes == 1) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[247]);

                    } else if ((*funcionarios).dependentes == 2) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[248]);

                    } else if ((*funcionarios).dependentes == 3) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[249]);

                    } else if ((*funcionarios).dependentes == 4) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[250]);

                    } else if ((*funcionarios).dependentes >= 5) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_1[251]);
                    }
                }
            }

            //Calcular IRS FUNCIONÁRIO : Titulares = 2 (Casado - 2 titular)
            if ((*funcionarios).titulares == 2) {
                if (((*funcionarios).salariocalc.salarioB - (*funcionarios).salariocalc.sub_alimentacao
                        - (*funcionarios).salariocalc.bonus) <= TABELA_IRS_2[y]) {

                    if ((*funcionarios).dependentes == 0) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[y + 1]);

                    } else if ((*funcionarios).dependentes == 1) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[y + 2]);

                    } else if ((*funcionarios).dependentes == 2) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[y + 3]);

                    } else if ((*funcionarios).dependentes == 3) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[y + 4]);

                    } else if ((*funcionarios).dependentes == 4) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[y + 5]);

                    } else if ((*funcionarios).dependentes == 5) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[y + 6]);
                    }

                } else {
                    if ((*funcionarios).dependentes == 0) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[246]);

                    } else if ((*funcionarios).dependentes == 1) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[247]);

                    } else if ((*funcionarios).dependentes == 2) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[248]);

                    } else if ((*funcionarios).dependentes == 3) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[249]);

                    } else if ((*funcionarios).dependentes == 4) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[250]);

                    } else if ((*funcionarios).dependentes >= 5) {
                        (*funcionarios).salariocalc.retencao_IRS =
                                (((*funcionarios).salariocalc.salarioB
                                - (*funcionarios).salariocalc.sub_alimentacao
                                - (*funcionarios).salariocalc.bonus) * TABELA_IRS_2[251]);
                    }
                }
            }
        }

        // CALCULAR O SALÁRIO LÍQUIDO 
        (*funcionarios).salariocalc.salarioL =
                ((*funcionarios).salariocalc.salarioB
                - (*funcionarios).salariocalc.retencao_IRS
                - (*funcionarios).salariocalc.retencao_SS_F);

    } else {
        (*funcionarios).salariocalc.retencao_SS_F = 0;
        (*funcionarios).salariocalc.retencao_SS_EP = 0;
        (*funcionarios).salariocalc.retencao_IRS = 0;
        (*funcionarios).salariocalc.salarioL = 0;
    }

    free(TABELA_TAXAS_SS_F);
    free(TABELA_TAXAS_SS_EP);
    free(TABELA_IRS_0);
    free(TABELA_IRS_1);
    free(TABELA_IRS_2);
}

/**
 * Esta função permite calcular os Salários Bruto e Líquido dos Funcionários 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 */
void calcularSalarios(Funcionario *funcionarios, int *CONTADOR_F) {
    if (*CONTADOR_F > 0) {
        int i;
        for (i = 0; i < *CONTADOR_F; i++) {
            calcBFuncionarios(&(funcionarios[i]));
            calcLFuncionarios(&(funcionarios[i]));
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}



/**
 * Esta função cria um Relatório/Listagem sobre o processamento dos Salários 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_LISTA_VAZIA" caso não exista funcionários
 * @warning: É criado um .txt com a informação
 */
void Relatorio1_ListaCalcSalarios(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {

        FILE * REL1 = fopen("Relatório1 - Salários.txt", "w+");
        if (REL1 == NULL) {
            puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Relatório1 - Salários.txt'");
        }

        int i;
        float Sliquido;
        for (i = 0; i < (*CONTADOR_F); i++) {
            fprintf(REL1, "%4i | %-50s | %c |%i| %.2f€ | %.2f€ | %.2f€ || %.2f€ | %.2f€ || %.2f€\n",
                    funcionarios[i].codigo,
                    funcionarios[i].nome,
                    funcionarios[i].cargo,
                    funcionarios[i].situacao,
                    funcionarios[i].salariocalc.salarioB,
                    funcionarios[i].salariocalc.sub_alimentacao,
                    funcionarios[i].salariocalc.bonus,
                    funcionarios[i].salariocalc.retencao_SS_F,
                    funcionarios[i].salariocalc.retencao_IRS,
                    funcionarios[i].salariocalc.salarioL);

            Sliquido += funcionarios[i].salariocalc.salarioL;
        }

        fprintf(REL1, "\n Total : SALÁRIOS LÍQUIDOS - %.2f€", Sliquido);
        fclose(REL1);
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função cria um Relatório/Listagem sobre a retenção de IRS 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_LISTA_VAZIA" caso não exista funcionários
 * @warning: É criado um .txt com a informação
 */
void Relatorio2_ListaIRS(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        FILE * REL2 = fopen("Relatório2 - Retenção IRS.txt", "w+");
        if (REL2 == NULL) {
            puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Relatório2 - Retenção IRS.txt'");
        }

        int i;
        float IRS = 0;
        for (i = 0; i < (*CONTADOR_F); i++) {
            if (funcionarios[i].salariocalc.retencao_IRS > 0) {
                fprintf(REL2, "%4i | %-50s | %c |%i| %.2f€\n",
                        funcionarios[i].codigo,
                        funcionarios[i].nome,
                        funcionarios[i].cargo,
                        funcionarios[i].situacao,
                        funcionarios[i].salariocalc.retencao_IRS);

                IRS += funcionarios[i].salariocalc.retencao_IRS;
            }
        }
        fprintf(REL2, "Total : RETENÇÃO DE IRS - %.2f€", IRS);
        fclose(REL2);
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função cria um Relatório/Listagem sobre a TSU do Funcionário e da Entidade Patronal 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_LISTA_VAZIA" caso não exista funcionários
 * @warning: É criado um .txt com a informação
 */
void Relatorio3_ListaTSU(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        FILE * REL3 = fopen("Relatório3 - Taxa Social Única.txt", "w+");
        if (REL3 == NULL) {
            puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Relatório3 - Taxa Social Única.txt'");
        }

        int i;
        float SS_F = 0, SS_EP = 0;
        for (i = 0; i < (*CONTADOR_F); i++) {
            if (funcionarios[i].salariocalc.retencao_SS_F > 0) {
                fprintf(REL3, "%4i | %-50s | %c |%i| %.2f€ / %.2f€\n",
                        funcionarios[i].codigo,
                        funcionarios[i].nome,
                        funcionarios[i].cargo,
                        funcionarios[i].situacao,
                        funcionarios[i].salariocalc.retencao_SS_F,
                        funcionarios[i].salariocalc.retencao_SS_EP);

                SS_F += funcionarios[i].salariocalc.retencao_SS_F;
                SS_EP += funcionarios[i].salariocalc.retencao_SS_EP;
            }
        }
        fprintf(REL3, "Total : TSU_FUNCIONÁRIOS - %.2f€\n", SS_F);
        fprintf(REL3, "Total : TSU_ENTIDADE PATRONAL - %.2f€\n", SS_EP);
        fclose(REL3);
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função cria um Relatório/Listagem sobre o Bónus 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_LISTA_VAZIA" caso não exista funcionários
 * @warning: É criado um .txt com a informação
 */
void Relatorio4_ListaBonus(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        FILE * REL4 = fopen("Relatório4 - Bónus.txt", "w+");
        if (REL4 == NULL) {
            puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Relatório4 - Bónus.txt'");
        }

        int i;
        float BONUS = 0;
        for (i = 0; i < (*CONTADOR_F); i++) {
            if (funcionarios[i].salariocalc.bonus > 0) {
                fprintf(REL4, "%4i | %-50s | %c |%i| %.2f€\n",
                        funcionarios[i].codigo,
                        funcionarios[i].nome,
                        funcionarios[i].cargo,
                        funcionarios[i].situacao,
                        funcionarios[i].salariocalc.bonus);

                BONUS += funcionarios[i].salariocalc.bonus;
            }
        }
        fprintf(REL4, "Total : BÓNUS - %.2f€\n", BONUS);
        fclose(REL4);
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função cria um Relatório/Listagem sobre as Horas Extraordinárias (Fim de Semana)
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_LISTA_VAZIA" caso não exista funcionários
 * @warning: É criado um .txt com a informação
 */
void Relatorio5_ListaHorasExtra(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        FILE * REL5 = fopen("Relatório5 - Horas Extra.txt", "w+");
        if (REL5 == NULL) {
            puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Relatório5 - Horas Extra.txt'");
        }

        int i;
        float EXTRA = 0;
        for (i = 0; i < (*CONTADOR_F); i++) {
            if (funcionarios[i].salarioinfo.dias_fim_semana > 0) {
                fprintf(REL5, "%4i | %-50s | %c |%i| %.2f€\n",
                        funcionarios[i].codigo,
                        funcionarios[i].nome,
                        funcionarios[i].cargo,
                        funcionarios[i].situacao,
                        ((funcionarios[i].venc_base
                        * funcionarios[i].salarioinfo.dias_fim_semana)
                        + ((funcionarios[i].venc_base / 2)
                        * funcionarios[i].salarioinfo.dias_fim_semana)));

                EXTRA += ((funcionarios[i].venc_base
                        * funcionarios[i].salarioinfo.dias_fim_semana)
                        + ((funcionarios[i].venc_base / 2)
                        * funcionarios[i].salarioinfo.dias_fim_semana));
            }
        }
        fprintf(REL5, "Total : HORAS EXTRA (Fim de Semana) - %.2f€\n", EXTRA);
        fclose(REL5);
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}

/**
 * Esta função cria os Relatórios/Listagens 
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @todo: "ERRO_LISTA_VAZIA" caso não exista funcionários
 * @warning: É criado um .txt com a informação
 */
void Relatorios(Funcionario *funcionarios, int *CONTADOR_F) {
    if (*CONTADOR_F > 0) {
        Relatorio1_ListaCalcSalarios(funcionarios, CONTADOR_F);
        Relatorio2_ListaIRS(funcionarios, CONTADOR_F);
        Relatorio3_ListaTSU(funcionarios, CONTADOR_F);
        Relatorio4_ListaBonus(funcionarios, CONTADOR_F);
        Relatorio5_ListaHorasExtra(funcionarios, CONTADOR_F);
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
}



/**
 * Esta função tem como objetivo ler os dias dos Funcionários apartir de um Ficheiro
 * 
 * @param funcionario Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @warning: O Ficheiro com os dias necessita de ter o nome "Info_Dias_Funcionários"
 * @warning: O Fihceiro necessita de estar no tipo ".txt"
 * 
 * @todo: Retorna "ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO" caso não sejá possível abrir o ficheiro
 */
void obterDiasFX(Funcionario *funcionario, int *CONTADOR_F) {
    int x;

    int *DIAS;
    DIAS = (int*) calloc(((*CONTADOR_F) * 5), sizeof (int));

    FILE *FICHEIRO_DIAS;
    FICHEIRO_DIAS = fopen("Info_Dias_Funcionários.txt", "r");

    if (FICHEIRO_DIAS == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Info_Dias_Funcionários.txt'");
    }
    
    //Ler os valores do Ficheiro
    for (x = 0; x < ((*CONTADOR_F) * 5); x++) {
        fscanf(FICHEIRO_DIAS, "%i ", &(*(DIAS + x)));
    }

    fclose(FICHEIRO_DIAS);

    if ((*CONTADOR_F) > 0) {
        int i;
        for (i = 0; i < (*CONTADOR_F); i++) {
            int y;
            for (y = 0; y < (((*CONTADOR_F) * 5) - 5); y++) {
                //Verifica se o código lido do ficheiro existe na memória, se não existir atribui 0 ao Funcionário
                if (funcionario[i].codigo == y) {
                    funcionario[i].salarioinfo.dias_completos = *(DIAS + (y + 1));
                    funcionario[i].salarioinfo.dias_meios = *(DIAS + (y + 2));
                    funcionario[i].salarioinfo.dias_fim_semana = *(DIAS + (y + 3));
                    funcionario[i].salarioinfo.dias_falta = *(DIAS + (y + 4));
                } else {
                    funcionario[i].salarioinfo.dias_completos = 0;
                    funcionario[i].salarioinfo.dias_meios = 0;
                    funcionario[i].salarioinfo.dias_fim_semana = 0;
                    funcionario[i].salarioinfo.dias_falta = 0;
                }
            }
        }
    } else {
        puts(ERRO_LISTA_VAZIA);
    }
    free(DIAS);
}

/**
 * Esta função tem como objetivo ler os dados dos Funcionários apartir de um Ficheiro
 * 
 * @param funcionario Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @warning: O Ficheiro com os dias necessita de ter o nome "Info_Dados_Funcionários"
 * @warning: O Fihceiro necessita de estar no tipo ".txt"
 * 
 * @todo: Retorna "ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO" caso não sejá possível abrir o ficheiro
 * 
 * @fixme: Apenas permite importar 1 funcionário
 */
void obterFuncionariosFX(Funcionario *funcionarios, int *CONTADOR_F) {
    FILE *FICHEIRO_FUNCIONARIOS;
    FICHEIRO_FUNCIONARIOS = fopen("Info_Dados_Funcionários.txt", "r");
    
    if (FICHEIRO_FUNCIONARIOS == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Info_Dados_Funcionarios.txt'");
    }

    int i;
    for (i = 0; i <= (*CONTADOR_F); i++) {
        fscanf(FICHEIRO_FUNCIONARIOS, "%d %s %d %c %d %d %c %f %f %d %d %d %d %d %d %d %d %d %d\n",
                &(funcionarios[i].codigo),
                &(funcionarios[i].nome),
                &(funcionarios[i].telefone),
                &(funcionarios[i].estado_civil),
                &(funcionarios[i].titulares),
                &(funcionarios[i].dependentes),
                &(funcionarios[i].cargo),
                &(funcionarios[i].venc_base),
                &(funcionarios[i].sub_alimentacao),
                &(funcionarios[i].nascimento.dia),
                &(funcionarios[i].nascimento.mes),
                &(funcionarios[i].nascimento.ano),
                &(funcionarios[i].entrada.dia),
                &(funcionarios[i].entrada.mes),
                &(funcionarios[i].entrada.ano),
                &(funcionarios[i].saida.dia),
                &(funcionarios[i].saida.mes),
                &(funcionarios[i].saida.ano),
                &(funcionarios[i].situacao));
    }
    (*CONTADOR_F)++;
    fclose(FICHEIRO_FUNCIONARIOS);
}

/**
 * Esta função tem como objetivo obter dados a partir de Ficheiros
 * 
 * @param funcionarios Funcionário
 * @param CONTADOR_F contador de Funcionários
 * 
 */
void obterDadosFX(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) >= 0) {
        obterFuncionariosFX(funcionarios, CONTADOR_F);
        obterDiasFX(funcionarios, CONTADOR_F);
    }
}



/**
 * Esta função tem como objetivo gravar/guardar os DADOS dos Funcionários num Ficheiro
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @warning: O Ficheiro com os dados dos Funcionários necessita de ter o nome "Info_Dados_Funcionários"
 * @warning: O Ficheiro necessita de ser do tipo ".txt"
 * 
 * @todo: Retorna "ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO" caso nao sejá possível abrir o ficheiro
 * @todo: Retorna "ERRO_LISTA_VAZIA" caso nao exita funcionários
 */
void gravarInfoFuncionariosFX(Funcionario *funcionarios, int *CONTADOR_F) {   
    FILE * INFO_FUNCIONARIOS = fopen("Info_Dados_Funcionários.txt", "w+");
    
    if (INFO_FUNCIONARIOS == NULL) {
        puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Info_Dados_Funcionários.txt'");
    }
    
    int i;
    for (i = 0; i < (*CONTADOR_F); i++) {
        fprintf(INFO_FUNCIONARIOS, "%i %s %i %c %i %i %c %f %f %i %i %i %i %i %i %i %i %i %i\n",
                funcionarios[i].codigo,
                funcionarios[i].nome,
                funcionarios[i].telefone,
                funcionarios[i].estado_civil,
                funcionarios[i].titulares,
                funcionarios[i].dependentes,
                funcionarios[i].cargo,
                funcionarios[i].venc_base,
                funcionarios[i].sub_alimentacao,
                funcionarios[i].nascimento.dia,
                funcionarios[i].nascimento.mes,
                funcionarios[i].nascimento.ano,
                funcionarios[i].entrada.dia,
                funcionarios[i].entrada.mes,
                funcionarios[i].entrada.ano,
                funcionarios[i].saida.dia,
                funcionarios[i].saida.mes,
                funcionarios[i].saida.ano,
                funcionarios[i].situacao);
    }
    fclose(INFO_FUNCIONARIOS);
}

/**
 * Esta função tem como objetivo gravar/guardar os DIAS de trabalho dos Funcionários num Ficheiro
 * 
 * @param funcionarios Funcionários
 * @param CONTADOR_F contador de Funcionários
 * 
 * @warning: O Ficheiro com os dias de trabalho dos Funcionários necessita de ter o nome "Info_Dados_Funcionários"
 * @warning: O Ficheiro necessita de ser do tipo ".txt"
 * 
 * @todo: "ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO" caso nao sejá possível abrir o ficheiro
 * @todo: "ERRO_LISTA_VAZIA" caso nao exita funcionários
 */
void gravarDiasFuncionariosFX(Funcionario *funcionarios, int *CONTADOR_F) {
    if ((*CONTADOR_F) > 0) {
        FILE * DIAS_FUNC = fopen("Info_Dias_Funcionários.txt", "w+");
        if (DIAS_FUNC == NULL) {
            puts("ERRO: NÃO FOI POSSIVEL EXECUTAR ARQUIVO - 'Info_Dias_Funcionarios.txt'");
        }

        int i;
        for (i = 0; i < (*CONTADOR_F); i++) {
            fprintf(DIAS_FUNC, "%4i %i %i %i %i\n",
                    funcionarios[i].codigo,
                    funcionarios[i].salarioinfo.dias_completos,
                    funcionarios[i].salarioinfo.dias_meios,
                    funcionarios[i].salarioinfo.dias_fim_semana,
                    funcionarios[i].salarioinfo.dias_falta);
        }
        fclose(DIAS_FUNC);
    } else {

        puts(ERRO_LISTA_VAZIA);
    }
}
