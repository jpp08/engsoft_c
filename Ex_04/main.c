#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Problema 04
***Um sobre arquivo, com um "enredo" bem mais simples, kkkkk.
Implementar um programa de gerenciamento de high scores. O programa deve:
a.	carregar os high scores de um arquivo e mostrar. Cada high score � composto de um nome (max. 10 caracteres) e um inteiro (pontua��o)
b.	pedir ao usu�rio o seu nome e a sua pontua��oo no jogo. 
c.	posicionar os dados do usu�rio na tabela de highest scores (max. 5) e regravar no arquivo.
*/

#define nomeArquivo "scores.txt"
#define numeroScores 5
#define tamanhoNome 10

// Estrutura utilizada para armazenar os dados de nome e pontua��o
typedef struct score Score;
struct score
{
	char nome[tamanhoNome];
	int pontuacao;
};

// vetor de scores com um elemento a mais para fazer a inser��o
struct score scores[numeroScores + 1];

// M�todo para carregar os dados j� armazenados no arquivo texto
void Carregar()
{
	// Limpar scores
	int i;
	for (i = 0; i < numeroScores; i++)
	{
		strncpy(scores[i].nome, "          ", tamanhoNome);
		scores[i].pontuacao = 0;
	}
	// Abrir arquivo
	FILE *arquivo = fopen(nomeArquivo, "r");
	if (!arquivo)
	{
		// Se o arquivo n�o p�de ser aberto, sai do processo
		return;
	}
	// L� os dados do arquivo diretamente para o vetor de scores
	for (i = 0; i < numeroScores; i++)
	{
		fread(&scores[i], sizeof(Score), 1, arquivo);
	}
	// Fecha o arquivo
	fclose(arquivo);
}

// M�todo para gravar os dados do vetor no arquivo texto
void Gravar()
{
	FILE *arquivo = fopen(nomeArquivo, "w");
	if (!arquivo)
	{
		// N�o foi poss�vel abrir o arquivo para grava��o
		return;
	}

	int i;
	for (i = 0; i < numeroScores; i++)
		fwrite(&scores[i], sizeof(Score), 1, arquivo);
	fclose(arquivo);
}

// M�todo para trocar os valores de dois elementos do vetor
void Trocar(int i1, int i2)
{
	struct score temp;
	strncpy(temp.nome, scores[i1].nome, tamanhoNome);
	temp.pontuacao = scores[i1].pontuacao;
	strncpy(scores[i1].nome, scores[i2].nome, tamanhoNome);
	scores[i1].pontuacao = scores[i2].pontuacao;
	strncpy(scores[i2].nome, temp.nome, tamanhoNome);
	scores[i2].pontuacao = temp.pontuacao;
}

// M�todo para mostrar a tabela de scores
void Mostrar()
{
	int i;
	printf("**** HIGH SCORES ****\n");
	printf("Nome       Pontuacao\n");
	for (i = 0; i < numeroScores; i++)
	{
		if (scores[i].pontuacao > 0)
		{
			printf("#%d : %10s %d\n", i + 1, scores[i].nome, scores[i].pontuacao);
		}
	}
	printf("*********************\n");
}

// M�todo para ordenar a tabela de scores
void Ordenar()
{
	int i, j;
	for (i = 0; i < numeroScores; i++)
	{
		for (j = i + 1; j < numeroScores + 1; j++)
		{
			if (scores[i].pontuacao < scores[j].pontuacao)
			{
				Trocar(i, j);
			}
		}
	}
}

// Fun��o para inserir os dados do usu�rio no vetor de dados
// Retorna 0 se o usu�rio n�o desejar mais informar dados
int InformarDadosUsuario()
{
	char nome[10];
	printf("Nome  (0 para sair):");
	scanf("%s", nome);
	if (nome[0] == '0')
	{
		return 0;
	}
	int pontuacao = 0;
	printf("Pontuacao: ");
	scanf("%d", &pontuacao);
	// Verifica se o nome j� foi informado
	int i = 0, encontrou = 0;
	while (i < numeroScores && encontrou == 0)
	{
		if (strcmp(scores[i].nome, nome) == 0) 
		{
			// Se o nome foi encontrado no vetor, i vai ser o �ndice
			encontrou = 1;
		}
		else
		{
			// Incrementa i, percorrendo o vetor
			i++;
		}
	}
	if (!encontrou)
	{		
		// Se n�o encontrou, vai ser colocado no �ltimo elemento do vetor
		// Aqui est� o pulo do gato. O vetor � definido com um elemento a mais.
		// Este �ltimo elemento � usado para se colocar o novo dado que o usu�rio informou.
		i = numeroScores;
	}

	strncpy(scores[i].nome, nome, tamanhoNome);
	scores[i].pontuacao = pontuacao;
	Ordenar();
	return 1;
}

int main(int argc, char *argv[])
{
	int continua = 1;
	Carregar();
	Ordenar();
	Mostrar();
	do
	{

		if (InformarDadosUsuario())
		{
			Mostrar();
			Gravar();
		}
		else
		{
			continua = 0;
		}
	} while (continua);

	return 0;
}
