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
	escolha[0] = '\0';

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
	funcionario *lista;

	while (strcmp(escolha, "A") && strcmp(escolha, "B") && strcmp(escolha, "C")
			&& strcmp(escolha, "D") && strcmp(escolha, "E")) {
		printf("\n------- Opção inválida --------");
		gets(escolha);
		strupr(escolha);
	}

	if (strcmp(escolha, "A") == 0) {
		lista = cadastrarFuncionario(lista);
	} else if (strcmp(escolha, "B") == 0) {
		int posicao = obterPosicaoFuncionario(lista);
		excluirFuncionario(posicao);
	} else if (strcmp(escolha, "C") == 0) {
		alterarFuncionario(lista);
	} else if (strcmp(escolha, "D") == 0) {
		exibirRelatorio(lista);
	} else if (strcmp(escolha, "E") == 0) {
		return;
	}
	menu();
}

funcionario* cadastrarFuncionario(funcionario *lista) {
	char data_nasc[DATE_LEN], data_admis[DATE_LEN], cargo[1], nome[MAX_NOME],
			matricula[9];
	double salario = 0;
	int qtdeDependentes = 0;
	dependente *listaDependentes = (dependente*) malloc(sizeof(dependente));

	preencherNome(nome);
	preencherMatricula(matricula, nome);
	printf("\nMatrícula = %s\n", matricula);
	preencherDataNasc(data_nasc, 16, 100);
	preencherDataAdmis(data_admis, data_nasc);
	preencherCargo(cargo);
	preencherQtdeDependentes(&qtdeDependentes);
	preencherSalario(&salario, cargo, qtdeDependentes);
	printf("\nSalário = %lf\n", salario);

	int i = 0;
	dependente *proximo = listaDependentes;
	for (i = 0; i < qtdeDependentes; i++) {
		printf("\n Informe os dados do %d° dependente", (i + 1));
		proximo = cadastrarDependentes(proximo);
	}

	printf("\n Funcionário inserido com sucesso \n");

	return inserirFuncionario(lista, nome, matricula, data_nasc, data_admis,
			cargo, salario, qtdeDependentes, listaDependentes);
}

void preencherDataNasc(char *data_nasc, int min, int max) {
	int ano, mes, dia, idadeDias;
	int *anoPont = &ano;
	int *mesPont = &mes;
	int *diaPont = &dia;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	int maximoDias = ((tm.tm_year + 1900 - max) * 365) + ((tm.tm_mon + 1) * 30)
			+ tm.tm_mday;
	int minimoDias = ((tm.tm_year + 1900 - min) * 365) + ((tm.tm_mon + 1) * 30)
			+ tm.tm_mday;

	printf("\nInforme a Data de Nascimento:");

	obterAno(anoPont);
	obterMes(mesPont);
	obterDia(diaPont);

	idadeDias = (ano * 365) + (mes * 30) + dia;

	if (idadeDias > minimoDias || idadeDias < maximoDias) {
		printf("\nO funcionário deve ter entre 16 e 100 anos");
		preencherDataNasc(data_nasc, min, max);
		return;
	}

	montarData(data_nasc, ano, mes, dia);
}

void preencherDataAdmis(char *data_admis, char *data_nasc) {

	int ano, mes, dia, idadeDias;
	int *anoPont = &ano;
	int *mesPont = &mes;
	int *diaPont = &dia;

	char data_nasc_aux[DATE_LEN];

	strcpy(data_nasc_aux, data_nasc);

	char** numeros = str_split(data_nasc_aux, '/');

	if (numeros) {
		int i;
		for (i = 0; *(numeros + i); i++) {
			int x = (int) strtol(*(numeros + i), (char **) NULL, 10);

			if (i == 0) {
				ano = x;
			} else if (i == 1) {
				mes = x;
			} else {
				dia = x;
			}

			free(*(numeros + i));
		}
		printf("\n");
		free(numeros);
	}

	int maximoDias = (ano * 365) + (mes * 30) + dia;

	printf("\nInforme a Data de Admissão:");

	obterAno(anoPont);
	obterMes(mesPont);
	obterDia(diaPont);

	idadeDias = (ano * 365) + (mes * 30) + dia;

	if (idadeDias < maximoDias) {
		printf(
				"\nA data de admissão não pode ser menor que a data de nascimento");
		preencherDataAdmis(data_admis, data_nasc);
		return;
	}

	montarData(data_admis, ano, mes, dia);
}

void montarData(char *data, int ano, int mes, int dia) {

	data[0] = '\0';

	char buf[DATE_LEN];

	sprintf(buf, "%d", ano);
	strcpy(data, buf);

	strcat(data, "/");

	sprintf(buf, "%d", mes);
	strcat(data, buf);

	strcat(data, "/");

	sprintf(buf, "%d", dia);
	strcat(data, buf);
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
	printf("\nDigite um cargo:");
	printf("\nE – Estagiário");
	printf("\nJ – Nível Júnior");
	printf("\nP – Nível Pleno");
	printf("\nS – Nível Sênior");
	printf("\nG – Nível Gerencial");

	gets(cargo);
	strupr(cargo);

	if (strcmp(cargo, "E") == 1 && strcmp(cargo, "J") == 1
			&& strcmp(cargo, "P") == 1 && strcmp(cargo, "S") == 1
			&& strcmp(cargo, "G") == 1) {
		printf("Opção inválida!");
		preencherCargo(cargo);
	}
}

void preencherNome(char *nome) {
	printf("Digite o nome: ");
	gets(nome);
}

void preencherSalario(double *salario, char *cargo, int qtdDependentes) {
	double salarioMinimo = 880;

	if (strcmp(cargo, "E") == 0) {
		*salario = salarioMinimo + (qtdDependentes * 15.9);
	} else if (strcmp(cargo, "J") == 0) {
		*salario = (3 * salarioMinimo) + (qtdDependentes * 23.15);
	} else if (strcmp(cargo, "P") == 0) {
		*salario = (5 * salarioMinimo) + (qtdDependentes * 35.72);
	} else if (strcmp(cargo, "S") == 0) {
		*salario = (7 * salarioMinimo) + (qtdDependentes * 49);
	} else if (strcmp(cargo, "G") == 0) {
		*salario = (9 * salarioMinimo) + (qtdDependentes * 68.29);
	} else {
		preencherSalario(salario, cargo, qtdDependentes);
	}
}

void preencherMatricula(char *matricula, char *nome) {
	int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0, num6 = 0;

	char primeiraletra = nome[0];
	num1 = (int) primeiraletra / 10;
	num2 = (int) primeiraletra % 10;

	num3 = obterPosicaoAlfabeto(primeiraletra) / 10;
	num4 = obterPosicaoAlfabeto(primeiraletra) % 10;

	num5 = 0;
	num6 = 1;

	int ultimoDigito = 0;

	int result1 = num1 * 5, result2 = num2 * 10, result3 = num3 * 15, result4 =
			num4 * 20, result5 = num5 * 25, result6 = num6 * 30;
	int result = result1 + result2 + result3 + result4 + result5 + result6;

	int resultResto = result % 11;

	if (resultResto != 10) {
		ultimoDigito = resultResto;
	}

	char buf[10];

	strcpy(matricula, &primeiraletra);
	sprintf(buf, "%d", num1);
	strcat(matricula, buf);
	sprintf(buf, "%d", num2);
	strcat(matricula, buf);
	sprintf(buf, "%d", num3);
	strcat(matricula, buf);
	sprintf(buf, "%d", num4);
	strcat(matricula, buf);
	sprintf(buf, "%d", num5);
	strcat(matricula, buf);
	sprintf(buf, "%d", num6);
	strcat(matricula, buf);
	sprintf(buf, "%d", ultimoDigito);
	strcat(matricula, buf);
}

void preencherQtdeDependentes(int *qtde) {
	printf("Quantos dependente você possui? ( 0 a 10 )");

	scanf("%i", qtde);

	if (*qtde < 0 || *qtde > 10) {
		preencherQtdeDependentes(qtde);
	}
}

funcionario* inserirFuncionario(funcionario *lista, char *nome, int matricula,
		char *data_nasc, char *data_admis, char *cargo, double salario,
		int qtdeDependentes, dependente *dependentes) {
	funcionario *novo = (funcionario*) malloc(sizeof(funcionario)); //Criar espaço de memória
	//Preencher funcionario
	novo->matricula = matricula;
	strcpy(novo->nome, nome);
	strcpy(novo->data_nasc, data_nasc);
	strcpy(novo->data_admis, data_nasc);
	strcpy(novo->cargo, cargo);
	novo->salario = salario;
	novo->qtdeDependentes = qtdeDependentes;
	novo->dependentes = dependentes;

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

	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	count += last_comma < (a_str + strlen(a_str) - 1);

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

int gerarNumeroAleatorio(int max) {
	if ((max - 1) == RAND_MAX) {
		return rand();
	} else {
		assert(max <= RAND_MAX);
		int end = RAND_MAX / max;
		assert(end > 0);
		end *= max;
		int r;
		while ((r = rand()) >= end)
			;

		return r % max;
	}
}

dependente* cadastrarDependentes(dependente *dependente) {
	char nome[MAX_NOME], dataNascimento[DATE_LEN], parentesco[1];
	int codigo;

	codigo = gerarNumeroAleatorio(100);
	preencherNome(nome);
	preencherDataNasc(dataNascimento, 0, 24);
	preencherParentesco(parentesco);

	return inserirDependente(dependente, nome, codigo, dataNascimento,
			parentesco);
}

void preencherParentesco(char *parentesco) {
	printf("\nDigite um parentesco:");
	printf("\nE – Enteado");
	printf("\nF – Filho/Filha");
	printf("\nT – Tutelado");

	gets(parentesco);
	strupr(parentesco);

	if (strcmp(parentesco, "E") == 1 && strcmp(parentesco, "F") == 1
			&& strcmp(parentesco, "T") == 1) {
		printf("Opção inválida!");
		preencherCargo(parentesco);
	}
}

int obterPosicaoFuncionario(funcionario *lista) {
	int posicao = 0;

	return posicao;
}

void excluirFuncionario(int posicao) {

}

void alterarFuncionario(funcionario *lista){
	excluirFuncionario(obterPosicaoFuncionario(lista));
	cadastrarFuncionario(lista);
}

void exibirRelatorio(funcionario* lista){

}

int obterPosicaoAlfabeto(char letra) {
	if (letra == 'A') {
		return 1;
	} else if (letra == 'B') {
		return 2;
	} else if (letra == 'C') {
		return 3;
	} else if (letra == 'D') {
		return 4;
	} else if (letra == 'E') {
		return 5;
	} else if (letra == 'F') {
		return 6;
	} else if (letra == 'G') {
		return 7;
	} else if (letra == 'H') {
		return 8;
	} else if (letra == 'I') {
		return 9;
	} else if (letra == 'J') {
		return 10;
	} else if (letra == 'K') {
		return 11;
	} else if (letra == 'L') {
		return 12;
	} else if (letra == 'M') {
		return 13;
	} else if (letra == 'N') {
		return 14;
	} else if (letra == 'O') {
		return 15;
	} else if (letra == 'P') {
		return 16;
	} else if (letra == 'Q') {
		return 17;
	} else if (letra == 'R') {
		return 18;
	} else if (letra == 'S') {
		return 19;
	} else if (letra == 'T') {
		return 20;
	} else if (letra == 'U') {
		return 21;
	} else if (letra == 'V') {
		return 22;
	} else if (letra == 'W') {
		return 23;
	} else if (letra == 'X') {
		return 24;
	} else if (letra == 'Y') {
		return 25;
	} else if (letra == 'Z') {
		return 26;
	} else {
		return 0;
	}
}
