// Atividade MAPA para a disciplina Estrutura de Dados 1
// Segunda vers�o, usando fila
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
int senhaAtual = 0;

// Mensagem para ser apresentada
char mensagem[40];

struct Fila {
	int numeros[tamanhoFila];	// vetor para conter a fila
	int tamanho;				// n�mero de senhas na fila
	int ultimo;					// �ltima senha adicionada
};

struct Fila fila;

void InicializarFila(){
	for(int i=0;i<tamanhoFila;i++){
		fila.numeros[i] = 0;		
	}
	fila.tamanho = 0;
	fila.ultimo = 0;
}

// Adiciona uma senha a fila
// Retorna o n�mero da senha em caso de sucesso, ou 0 em caso de fila completa
int pushSenha(){
	if (fila.tamanho == tamanhoFila) {
		strcpy(mensagem, "A fila ja esta completa, tente novamente mais tarde.");		
		return 0;
	} else {
		fila.numeros[fila.tamanho] = fila.ultimo + 1;
		fila.ultimo++;
		fila.tamanho++;
		return fila.ultimo;
	}
}

// Retorna a pr�xima senha da fila
// 0 se a fila estiver vazia
int popSenha(){
	if (fila.tamanho == 0) {
		strcpy(mensagem, "A fila esta vazia");
		return 0;
	} else {
		senhaAtual = fila.numeros[0];
		// reloca as senhas
		for(int i=0;i<tamanhoFila-1;i++){
			fila.numeros[i] = fila.numeros[i+1];
		}
		fila.numeros[tamanhoFila-1]=0;
		fila.tamanho--;		
		return senhaAtual;
	}
}

void mostrarFila()
{

printf("DBG: ");
for(int i=0;i<tamanhoFila;i++){
	printf("%03d ",fila.numeros[i]);
}
printf("\n");

	printf("[Anterior] [Atual] [Proxima]\n");

	if (senhaAtual > 1)
	{
		printf("    %03d   ", senhaAtual-1);
	}
	else
	{
		if (fila.tamanho==0 && fila.ultimo>0){
			printf("    %03d   ", fila.ultimo);
		} else {
				printf("          ");
						}
	}

	if (senhaAtual > 0)
	{
		printf("   %03d   ", senhaAtual);
	}
	else
	{
		printf("         ");
	}

	if (fila.numeros[1] > 0)
	{
		printf("   %03d   ", fila.numeros[1]);
	}
	else
	{
		printf("         ");
	}

	for (int i = (senhaAtual==0?1:2); i < tamanhoFila; i++)
	{
		if (fila.numeros[i]>0){
			printf("  %03d", fila.numeros[i]);			
		}		
	}
	printf("\n%s\n\n", mensagem);
}

int main(int argc, char *argv[])
{
	int opcao = 1;	
	while (opcao != 0)
	{
		system("CLS");		
		printf("****************************************\n");
		printf("* SISTEMA DE SENHAS DO ACOUGUE DO JOSE *\n");
		printf("****************************************\n");

		mostrarFila();

		printf("1. Retirar uma senha para o atendimento\n");
		
		if (fila.numeros[1] > 0)		
		{
			printf("2. Chamada da proxima senha\n");
		}
		if (fila.tamanho == 0) {
			printf("0. SAIR\n");	
		}
		

		scanf("%d", &opcao);
		switch (opcao)
		{
		case 1:
			pushSenha();
			//pedirSenha();
			break;
		case 2:
			popSenha();
			//chamarCliente();
			break;
		case 0:
			
			if (fila.tamanho>0)
			{
				strcpy(mensagem, "Ainda existem clientes na fila");
			//	opcao = -1;
			}
			break;
		}
	}

	return 0;
}
