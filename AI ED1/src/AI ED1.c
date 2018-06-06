#include <stdio.h>
#include <stdlib.h>
#include "Biblioteca.c"
#include <time.h>
#include <assert.h>

main() {
	setbuf(stdout, NULL);
	menu();
	return 0;
}

void menu() {
	char escolha[1];

	printf("\n---------------------------------------------");
	printf("\nA – Inserir funcionário ---------------------");
	printf("\nB – Excluir dados (funcionário e dependentes)");
	printf("\nC – Alterar dados (funcionário e dependentes)");
	printf("\nD – Relatórios ------------------------------");
	printf("\nE – Finalizar -------------------------------");
	printf("\n---------------------------------------------");
	printf("\n------- Escolha uma das opções acima --------");

	gets(escolha);
	strupr(escolha);

	validarEscolha(escolha);
}

void validarEscolha(char* escolha) {
	while (strcmp(escolha, "A") && strcmp(escolha, "B") && strcmp(escolha, "C")
			&& strcmp(escolha, "D") && strcmp(escolha, "E")) {
		printf("\n------- Opção inválida --------");
		gets(escolha);
		strupr(escolha);
	}

	if (strcmp(escolha, "A") == 0) {
		cadastrarFuncionario();
	} else if (strcmp(escolha, "B") == 0) {

	} else if (strcmp(escolha, "C") == 0) {

	} else if (strcmp(escolha, "D") == 0) {

	} else if (strcmp(escolha, "E") == 0) {

	}
}

void cadastrarFuncionario() {
	funcionario *lista;
	char *data_nasc, *data_admis, *cargo, *nome;
	double salario;
	int matricula, qtdeDependentes;
	dependente dependente;

	preencherDataNasc(data_nasc);
	preencherDataAdmis(data_admis, data_nasc);
	// inserirFuncionario(lista, nome, matricula, data_nasc, data_admis, cargo, salario, qtdeDependentes, dependente);

	printf("\n teste2: %s \n", data_nasc);

	menu();
}

void preencherDataNasc(char *data_nasc) {
	int ano, mes, dia, idadeDias;
	int *anoPont = &ano;
	int *mesPont = &mes;
	int *diaPont = &dia;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	int maximoDias = ((tm.tm_year + 1900 - IDADEMAXIMA) * 365)
			+ ((tm.tm_mon + 1) * 30) + tm.tm_mday;
	int minimoDias = ((tm.tm_year + 1900 - IDADEMINIMA) * 365)
			+ ((tm.tm_mon + 1) * 30) + tm.tm_mday;

	char buf[DATE_LEN];

	printf("\nInforme a Data de Nascimento:");

	obterAno(anoPont);
	obterMes(mesPont);
	obterDia(diaPont);

	idadeDias = (ano * 365) + (mes * 30) + dia;

	if (idadeDias > minimoDias || idadeDias < maximoDias) {
		printf("\nO funcionário deve ter entre 16 e 100 anos");
		preencherDataNasc(data_nasc);
		return;
	}

	data_nasc[0] = '\0';

	sprintf(buf, "%d", ano);
	strcpy(data_nasc, buf);

	strcat(data_nasc, "/");

	sprintf(buf, "%d", mes);
	strcat(data_nasc, buf);

	strcat(data_nasc, "/");

	sprintf(buf, "%d", dia);
	strcat(data_nasc, buf);
}

void preencherDataAdmis(char *data_admis, char *data_nasc) {

	int ano, mes, dia, idadeDias;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	char data_nasc_aux[DATE_LEN];

	strcpy(data_nasc_aux, data_nasc);

	char** numeros = str_split(data_nasc_aux, '/');

	if (numeros) {
		int i;
		for (i = 0; *(numeros + i); i++) {
//			printf("%s", *(numeros + i));
			int x = 0;

			sprintf(*(numeros + i), "%d", x );
			if (i == 0) {
				ano = x;
				printf("\n%i", ano);
			} else if (i == 1) {
				mes = x;
				printf("\n%i", mes);
			} else {
				dia = x;
				printf("\n%i", dia);
			}

			free(*(numeros + i));
		}
		printf("\n");
		free(numeros);
	}

	int maximoDias = (ano * 365) + (mes * 30) + dia;

	char buf[12];

	printf("\nInforme a Data de Nascimento:");

	idadeDias = (ano * 365) + (mes * 30) + dia;

	if (idadeDias < maximoDias) {
		printf(
				"\nA data de admissão não pode ser menor que a data de nascimento");
		preencherDataNasc(data_admis);
	}

	sprintf(buf, "%d", ano);
	strcpy(data_admis, buf);

	strcat(data_admis, "/");

	sprintf(buf, "%d", mes);
	strcat(data_admis, buf);

	strcat(data_admis, "/");

	sprintf(buf, "%d", dia);
	strcat(data_admis, buf);
}

void obterAno(int *ano) {
	do {
		printf("\nDigite o ano: ");
		scanf("%i", ano);

		if (*ano < 1900) {
			printf("\nPreencha um ano válido");
		}
	} while (*ano < 1900);
}

void obterMes(int *mes) {
	do {
		printf("\nDigite o mês: ");
		scanf("%i", mes);

		if (*mes < 1 || *mes > 12) {
			printf("\nPreencha um mês válido");
		}
	} while (*mes < 1 || *mes > 12);
}

void obterDia(int *dia) {
	do {
		printf("\nDigite o dia: ");
		scanf("%i", dia);

		if (*dia < 1 || *dia > 31) {
			printf("\nPreencha um dia válido");
		}
	} while (*dia < 1 || *dia > 31);
}

void preencherCargo(char *cargo) {

}

void preencherNome(char *nome) {

}

void preencherSalario(double *salario) {

}

void preencherMatricula(int *matricula) {

}

void preencherQtdeDependentes(int *qtde) {

}

funcionario* inserirFuncionario(funcionario *lista, char *nome, int matricula,
		char *data_nasc, char *data_admis, char *cargo, double salario,
		int qtdeDependentes, dependente dependente) {
	funcionario *novo = (funcionario*) malloc(sizeof(funcionario)); //Criar espaço de memória
	//Preencher funcionario
	novo->matricula = matricula;
	strcpy(novo->nome, nome);
	strcpy(novo->data_nasc, data_nasc);
	strcpy(novo->data_admis, data_nasc);
	strcpy(novo->cargo, cargo);
	novo->salario = salario;
	novo->qtdeDependentes = qtdeDependentes;
	novo->dependente = dependente;

	novo->proximo = lista;
	return novo;
}

dependente* inserirDependente(dependente *lista, char *nome, int codigo,
		char* data_nasc, char* parentesco) {
	dependente *novo = (dependente*) malloc(sizeof(dependente)); //Criar espaço de memória
	//Preencher dependente
	novo->codigo = codigo;
	strcpy(novo->nome, nome);
	novo->proximo = NULL; //Qualquer elemento novo aponta para NULL

	//Ligá-lo-ei à lista
	if (lista == NULL) {
		return novo;
	} else {
		dependente *tmp = lista;
		while (tmp->proximo != NULL) {
			tmp = tmp->proximo;
		}
		tmp->proximo = novo;
		return lista;
	}
}

char** str_split(char* a_str, const char a_delim) {
	char** result = 0;
	size_t count = 0;
	char* tmp = a_str;
	char* last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	 knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char*) * count);

	if (result) {
		size_t idx = 0;
		char* token = strtok(a_str, delim);

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}
