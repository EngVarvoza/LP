#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H


#define MSG_CODIGO "Código [1-1000]: "
#define V_MIN_CODIGO 1 
#define V_MAX_CODIGO 1000

#define MSG_NOME "Nome [0-20]: "
#define MAX_STRING 20

#define MSG_TELEFONE "Telemóvel: "
#define V_MIN_TELEFONE 910000000
#define V_MAX_TELEFONE 969999999

#define MSG_ESTADOCIVIL "Estado Civil [S/C]: " /* S - Solteiro | C - Casado */

#define MSG_TITULARES "Nº Titulares [1/2]: "
#define V_MIN_TITULARES 1
#define V_MAX_TITULARES 2

#define MSG_DEPENDENTES "Nº de Dependentes: " 
#define V_MIN_DEPENDENTES 0
#define V_MAX_DEPENDENTES 20

#define MSG_CARGO "Cargo [A/C/E]: " /* A - Administrador | C - Chefe | E - Empregado */

#define MSG_VENCBASE "Vencimento Base: " 
#define V_MIN_VENCBASE 0.00 
#define V_MAX_VENCBASE 1000000.00

#define MSG_SUBALIM "Subsídio de Alimentação: "
#define V_MIN_SUBALIM 0.00 
#define V_MAX_SUBALIM 20.00

#define V_MIN_DIAS 1
#define V_MAX_DIAS 31

#define V_MIN_MES 1 
#define V_MAX_MES 12

#define MSG_D_NASCIMENTO "Data de Nascimento - DIA: "

#define MSG_M_NASCIMENTO "Data de Nascimento - MÊS: "

#define MSG_A_NASCIMENTO "Data de Nascimento - ANO: " 
#define V_MIN_A_NASCIMENTO 1940 /* pessoas que em 2021 completam 81 anos */
#define V_MAX_A_NASCIMENTO 2003 /* pessoas que em 2021 completam 18 anos (idade minima legal para trabalhar */


#define MSG_D_ENTRADA "Data de Entrada - DIA: " 

#define MSG_M_ENTRADA "Data de Entrada - MÊS: " 

#define MSG_A_ENTRADA "Data de Entrada - ANO: " 
#define V_MIN_A_ENTRADA 2010 /* Criação da Empresa em 2010 */
#define V_MAX_A_ENTRADA 2021 /* Ano atual */


#define MSG_D_SAIDA "Data de Saída - DIA: " 
#define V_MIN_D_SAIDA 0 /*0 pois funcionário pode ainda não ter saído da empresa*/

#define MSG_M_SAIDA "Data de Saída - MÊS: "
#define V_MIN_M_SAIDA 0 /*0 pois funcionário pode ainda não ter saído da empresa*/

#define MSG_A_SAIDA "Data de Saída - ANO: "
#define V_MIN_A_SAIDA 0 /*0 pois funcionário pode ainda não ter saído da empresa*/
#define V_MAX_A_SAIDA 2021 /* Ano atual */

#define MSG_SITUACAO "Situação [0-Inativo/1-Ativo]: "
#define ATIVO 1
#define INATIVO 0

#define MSG_DIASCOMPLETOS "Nº de dias completos: "
#define V_MIN_DIASCOMPLETOS 0 /*0 pois pode não trabalhar naquele mês*/

#define MSG_DIASMEIO "Nº de meios dias: "
#define V_MIN_DIASMEIO 0 /*0 pois pode não trabalhar naquele mês*/

#define MSG_DIASFIMDS "Nº de dias ao fim de semana: "
#define V_MIN_DIASFIMDS 0 /*0 pois pode não trabalhar naquele mês*/

#define MSG_DIASFALTA "Nº de dias de falta: "
#define V_MIN_DIASFALTA 0 /*0 pois pode não trabalhar naquele mês*/

#define ERRO_NAO_EXISTE "O funcionário não existe na lista!"
#define ERRO_LISTA_VAZIA "A lista de funcionários está vazia!"
#define ERRO_EXISTE "O código do funcionário já se encontra atribuído!"

#define BONUS0 0.10
#define BONUS1 0.06
#define BONUS2 0.03

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int dias_completos;
    int dias_meios;
    int dias_fim_semana;
    int dias_falta;
} Salarioinfo;

typedef struct {
    float salarioB;
    float sub_alimentacao;
    float bonus;
    float retencao_IRS;
    float retencao_SS_F;
    float retencao_SS_EP;
    float salarioL;
} Salariocalc;

typedef struct {
    int codigo;
    char nome[MAX_STRING];
    int telefone;
    char estado_civil;
    int titulares;
    int dependentes;
    char cargo;
    float venc_base;
    float sub_alimentacao;
    Data nascimento;
    Data entrada;
    Data saida;
    int situacao;
    Salarioinfo salarioinfo;
    Salariocalc salariocalc;
} Funcionario;


void inserirFuncionarios(Funcionario *funcionario, int *CONTADOR_F);
void procurarFuncionarios(Funcionario *funcionarios, int *CONTADOR_F);
void atualizarFuncionarios(Funcionario *funcionarios, int *CONTADOR_F);
void removerFuncionarios(Funcionario *funcionarios, int *CONTADOR_F);
void listarFuncionarios(Funcionario *funcionarios, int *CONTADOR_F);

void calcularSalarios(Funcionario *funcionarios, int *CONTADOR_F);

void Relatorios(Funcionario *funcionarios, int *CONTADOR_F);

void obterDadosFX(Funcionario *funcionarios, int *CONTADOR_F);

void gravarInfoFuncionariosFX(Funcionario *funcionarios, int *CONTADOR_F);
void gravarDiasFuncionariosFX(Funcionario *funcionarios, int *CONTADOR_F);

#endif /* FUNCIONARIOS_H */

