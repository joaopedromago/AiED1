/*
 * Biblioteca.c
 *
 *  Created on: 21 de mai de 2018
 *      Author: n226814168
 */

#ifndef BIBLIOTECA_C_
#define BIBLIOTECA_C_

#define MAX_NOME 80
#define TAM 3
#define DATE_LEN 10

#define IDADEMINIMA 17
#define IDADEMAXIMA 100

//Estrutura
struct dependente{
	char 	nome[MAX_NOME];
	int		codigo;
	char 	data_nasc[DATE_LEN];
	char	parentesco[1];
	struct  dependente *proximo;
};
typedef struct dependente dependente;

struct funcionario{
	char 	nome[MAX_NOME];
	int		matricula;
	char 	data_nasc[DATE_LEN];
	char	data_admis[DATE_LEN];
	char	cargo[1];
	double	salario;
	int		qtdeDependentes;
	dependente	dependente;
	struct  funcionario *proximo;
};
typedef struct funcionario funcionario;

//Protótipos

void menu();
void validarEscolha(char* escolha);
void cadastrarFuncionario();

void preencherDataNasc(char *data_nasc);
void preencherDataAdmis(char *data_admis, char *data_nasc);
void obterAno(int *ano);
void obterMes(int *mes);
void obterDia(int *dia);
void preencherCargo(char *cargo);
void preencherNome(char *nome);
void preencherSalario(double *salario, char *cargo, int qtdDependentes);
void preencherMatricula(int *matricula);
void preencherQtdeDependentes(int *qtde);

funcionario* inserirFuncionario(funcionario *lista, char *nome, int matricula,
		char *data_nasc, char *data_admis, char *cargo, double salario, int qtdeDependentes,
		dependente dependente);
dependente* inserirDependente(dependente *lista, char *nome, int codigo,
		char* data_nasc, char* parentesco);

// util
char** str_split(char* a_str, const char a_delim);
void montarData(char *data, int ano, int mes, int dia);
int gerarNumeroAleatorio(int max);

#endif /* BIBLIOTECA_C_ */
