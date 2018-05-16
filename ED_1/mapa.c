// Atividade MAPA para a disciplina Estrutura de Dados 1
// Aluno: Guionardo Furlan
// Curso: Engenharia de Software - Unicesumar - 2018
/*
Jos� � o propriet�rio de um a�ougue em sua cidade, o estabelecimento possui um grande fluxo de pessoas.
Jos� n�o est� conseguindo controlar a fila de clientes que est� se formando para o atendimento,
muitos dos clientes est�o reclamando que n�o est� sendo respeitado a ordem de chegada para serem atendidos.
Sendo assim Jos� solicitou a voc� um software que resolva o problema.


Depois de uma an�lise foi definido que o software dever� ter duas funcionalidades:
- Retirar uma senha para o atendimento.
- Chamada da pr�xima senha no painel para atendimento.

Com base nestas informa��es, voc� dever� desenvolver um programa em linguagem C que atenda as funcionalidades:
- Retirada de nova senha pelo cliente.
- Atendente chamar o pr�ximo n�mero da fila.
- Sair

Funcionalidade e restri��es do programa:
- A cada nova itera��o deve-se apresentar na tela a composi��o da fila.
- Ao ser chamado um n�mero para atendimento, no painel deve-se apresentar a senha anterior, atual e a pr�xima.
- A funcionalidade Sair, s� poder� ser executada se a todas as senhas de atendimento j� foram chamadas.
- A fila deve ter no m�ximo 10 pessoas, caso a fila esteja completa apresentar uma mensagem que �A fila j� est� completa, tente novamente mais tarde.�
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamanhoFila 10

// Pr�xima senha a ser chamada
int proximaSenha = 1;

// �ltima senha gerada
int ultimaSenha = 0;

// Mensagem para ser apresentada
char mensagem[40];

void mostrarFila()
{

	printf("[Anterior] [Atual] [Proxima]\n");

	if (proximaSenha > 2)
	{
		printf("    %03d   ", proximaSenha - 2);
	}
	else
	{
		printf("          ");
	}

	if (proximaSenha > 1)
	{
		printf("   %03d   ", proximaSenha - 1);
	}
	else
	{
		printf("         ");
	}

	if (proximaSenha <= ultimaSenha)
	{
		printf("   %03d   ", proximaSenha);
	}
	else
	{
		printf("         ");
	}

	for (int i = proximaSenha + 1; i <= ultimaSenha; i++)
	{
		printf("  %03d", i);
	}
	printf("\n%s\n\n", mensagem);
}

void pedirSenha()
{
	if (ultimaSenha - proximaSenha + 1 < tamanhoFila)
	{
		ultimaSenha++;
		strcpy(mensagem, "");
	}
	else
	{
		strcpy(mensagem, "A fila ja esta completa, tente novamente mais tarde.");
	}
}

void chamarCliente()
{
	if (proximaSenha <= ultimaSenha)
	{
		strcpy(mensagem, "");

		proximaSenha++;
	}
	else
	{
		strcpy(mensagem, "A fila esta vazia");
	}
}

int main(int argc, char *argv[])
{
	int opcao = 1;
	proximaSenha = 1;
	ultimaSenha = 0;
	while (opcao != 0)
	{
		system("CLS");		
		printf("****************************************\n");
		printf("* SISTEMA DE SENHAS DO ACOUGUE DO JOSE *\n");
		printf("****************************************\n");

		mostrarFila();

		printf("1. Retirar uma senha para o atendimento\n");
		if (proximaSenha <= ultimaSenha)
		{
			printf("2. Chamada da proxima senha\n");
		}
		printf("0. SAIR\n");

		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1:
			pedirSenha();
			break;
		case 2:
			chamarCliente();
			break;
		case 0:
			if (proximaSenha <= ultimaSenha)
			{
				strcpy(mensagem, "Ainda existem clientes na fila");
				opcao = -1;
			}
			break;
		}
	}

	return 0;
}
