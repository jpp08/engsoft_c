// Atividade MAPA para a disciplina Estrutura de Dados 1
// Terceira vers�o, usando fila e nome de cliente
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
#define tamanhoFila 5
#define tamanhoNome 10

char mensagem[40]; // Mensagem apresentada ao usu�rio

struct Cliente
{
    char nome[tamanhoNome];
    int posicao;
};

// Fila de clientes
// Indice 0 = Cliente anterior chamado
// Indice 1 = Cliente atual chamado
// Indices 2.. = Pr�ximos clientes
struct Fila
{
    struct Cliente clientes[tamanhoFila];
    struct Cliente clienteAnterior; // Cliente que foi chamado anteriormente
    int tamanho;
    int ultimaPosicao;
    int ultimoChamado;
};

struct Fila fila;

void InicializaVariaveis()
{
    fila.tamanho = 0;
    fila.ultimaPosicao = 0;
    fila.ultimoChamado = 0;
    for (int i = 0; i < tamanhoFila; i++)
    {
        strcpy(fila.clientes[i].nome, "");
        fila.clientes[i].posicao = 0;
    }
    fila.clienteAnterior.posicao = 0;
}

// Adiciona um cliente a fila, retornando o �ndice do vetor
int AdicionaCliente()
{
    strcpy(mensagem, "");
    if (fila.tamanho == tamanhoFila)
    {
        strcpy(mensagem, "A fila ja esta completa, tente novamente mais tarde.");
        return -1;
    }
    char nome[tamanhoNome];

    printf("Nome do cliente:");
    gets(nome);
    if (strlen(nome) == 0)
    {
        strcpy(mensagem, "Cliente deve ser informado");
        return -1;
    }
    strcpy(mensagem, "");
    strcpy(fila.clientes[fila.tamanho].nome, nome);
    fila.clientes[fila.tamanho].posicao = fila.ultimaPosicao + 1;
    fila.ultimaPosicao++;
    fila.tamanho++;
    return fila.tamanho - 1;
}

void add(char nome[10])
{
    if (fila.tamanho == tamanhoFila)
        return;
    strcpy(fila.clientes[fila.tamanho].nome, nome);
    fila.clientes[fila.tamanho].posicao = fila.ultimaPosicao + 1;
    fila.ultimaPosicao++;
    fila.tamanho++;
}
// Chama a senha do pr�ximo cliente, retornando
int ChamarCliente()
{
    strcpy(mensagem, "");
    if (fila.tamanho == 0)
    {
        strcpy(mensagem, "A fila esta vazia");
        return -1;
    }

    int posicaoAnterior = fila.clienteAnterior.posicao;
    fila.clienteAnterior = fila.clientes[0];
    fila.ultimoChamado = fila.clientes[0].posicao;
    if (posicaoAnterior > 0)
    {
        for (int i = 0; i < tamanhoFila - 1; i++)
        {
            fila.clientes[i] = fila.clientes[i + 1];
        }
        fila.tamanho--;
        strcpy(fila.clientes[tamanhoFila - 1].nome, "");
        fila.clientes[tamanhoFila - 1].posicao = 0;

        fila.ultimoChamado = fila.clientes[0].posicao;
    }

    return 0;
}

void autoData()
{
    add("Guionardo");
    add("Marines");
    add("Joao");
    add("Benjamin");
}

void dbg()
{
    printf("***********************\n");
    printf("UltimoChamado %02d\n", fila.ultimoChamado);
    printf("UltimaPosicao %02d\n", fila.ultimaPosicao);
    printf("Tamanho       %02d\n", fila.tamanho);
    printf("Anterior      %s %02d\n\n", fila.clienteAnterior.nome, fila.clienteAnterior.posicao);

    for (int i = 0; i < tamanhoFila; i++)
    {
        printf("#%02d = %s %02d\n", i, fila.clientes[i].nome, fila.clientes[i].posicao);
    }
    printf("\n");
}

void MostraFila()
{
#ifdef debug
    dbg();
#endif
    if (strlen(mensagem) > 0)
    {
        printf("\nMensagem: %s\n\n", mensagem);
    }

    if (fila.clienteAnterior.posicao > 0 && (fila.clienteAnterior.posicao < fila.ultimoChamado || fila.tamanho == 0))
    {
        printf("Cliente anterior #%02d:%s\n", fila.clienteAnterior.posicao, fila.clienteAnterior.nome);
    }
    for (int i = 0; i < fila.tamanho; i++)
    {
        if (fila.clientes[i].posicao == fila.ultimoChamado)
        {
            printf("Cliente atual    #%02d:%s\n", fila.clientes[i].posicao, fila.clientes[i].nome);
        }
        else
        {
            printf("Proximo cliente  #%02d:%s\n", fila.clientes[i].posicao, fila.clientes[i].nome);
        }
    }
    printf("**************************************\n\n");
}

void main()
{
    InicializaVariaveis();
#ifdef debug
    autoData();
#endif
    int opcao = -1;
    while (opcao != 0)
    {
        system("CLS");
        printf("****************************************\n");
        printf("* SISTEMA DE SENHAS DO ACOUGUE DO JOSE *\n");
        printf("****************************************\n");
        MostraFila();
        printf("Opcoes:\n\n");
        if (fila.tamanho < tamanhoFila)
        {
            printf("1. Retirar uma senha para o atendimento\n");
        }
        if (fila.tamanho > 0)
        {
            printf("2. Chamada da proxima senha\n");
        }
        if (fila.tamanho == 0)
        {
            printf("0. SAIR\n");
        }

        scanf("%d", &opcao);
        fflush(stdin); // Limpa o buffer de teclado
        switch (opcao)
        {
        case 1:
            AdicionaCliente();
            break;
        case 2:
            ChamarCliente();
            break;
        case 0:
            if (fila.tamanho > 0)
            {
                strcpy(mensagem, "Ainda existem clientes na fila");
                opcao = -1;
            }
            break;
        }
    }
}
