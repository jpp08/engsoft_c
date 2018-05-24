// MAPA Estrutura de dados 2
// Autor: Guionardo Furlan
// Vers�o: 1.0 - 24/05/2018
// C�digo dispon�vel em https://github.com/guionardo/engsoft_c/tree/master/ED_2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Estrutura para registro do nodo
struct Elemento
{
    int Id;         // Indice do elemento
    int Valor;      // Valor do elemento
    char Dado[1];   // Dado do elemento (n�mero ou opera��o matem�tica)
    int Processado; // Flag indicativa que o n� j� foi processado e seu valor foi calculado

    struct Elemento *nEsquerdo; // N� esquerdo
    struct Elemento *nDireito;  // N� direito
    struct Elemento *nPai;      // N� pai (usado apenas para controlar o n�vel)
    int Nivel;
};

//
// Elemento raiz da �rvore bin�ria
struct Elemento *Raiz = NULL;

// N�mero de elementos da �rvore
int nElementos = 0;

// N�vel (usada para identa��o dos resultados de c�lculos na fun��o ValorNo)
int nNivel = 0;

//
// Fun��o para cria��o de um nodo
struct Elemento *CriaNodo(char *Dado, struct Elemento *Pai)
{

    struct Elemento *elm = malloc(sizeof(struct Elemento));
    if (elm == NULL)
    {
        printf("ERRO NA ALOCA��O DE MEM�RIA!\n");
        return NULL;
    }
    nElementos++;
    elm->Id = nElementos;
    elm->Valor = 0;
    strcpy(elm->Dado, " ");
    elm->Dado[0] = Dado[0];
    elm->Processado = 0;
    elm->nEsquerdo = NULL;
    elm->nDireito = NULL;
    elm->nPai = Pai;
    elm->Nivel = 0;

    printf("Nodo #%d [%s] ", elm->Id, elm->Dado);
    if (Pai == NULL)
    {
        printf("(RAIZ)\n");
        elm->Nivel = 1;
    }
    else
    {
        printf("(Pai = %d)\n", Pai->Id);
        elm->Nivel = Pai->Nivel + 1;
    }

    return elm;
}

//
// M�todo para libera��o dos ponteiros criados
void LiberaPonteiros(struct Elemento *no)
{
    if (no == NULL)
    {
        return;
    }
    //printf("%p ", no);
    if (no->nEsquerdo != NULL)
    {
        LiberaPonteiros(no->nEsquerdo);
        no->nEsquerdo = NULL;
    }
    if (no->nDireito != NULL)
    {
        LiberaPonteiros(no->nDireito);
        no->nDireito = NULL;
    }
    free(no);
}

//
// M�todo para montagem da �rvore bin�ria
void MontaArvore()
{
    printf("# Montando arvore...\n");
    nElementos = 0;
    Raiz = CriaNodo("+", NULL);
    Raiz->nEsquerdo = CriaNodo("*", Raiz);
    Raiz->nDireito = CriaNodo("5", Raiz);
    Raiz->nEsquerdo->nEsquerdo = CriaNodo("-", Raiz->nEsquerdo);
    Raiz->nEsquerdo->nDireito = CriaNodo("+", Raiz->nEsquerdo);
    Raiz->nEsquerdo->nEsquerdo->nEsquerdo = CriaNodo("6", Raiz->nEsquerdo->nEsquerdo);
    Raiz->nEsquerdo->nEsquerdo->nDireito = CriaNodo("3", Raiz->nEsquerdo->nEsquerdo);
    Raiz->nEsquerdo->nDireito->nEsquerdo = CriaNodo("4", Raiz->nEsquerdo->nDireito);
    Raiz->nEsquerdo->nDireito->nDireito = CriaNodo("1", Raiz->nEsquerdo->nDireito);

    printf("%d elementos criados\n\n", nElementos);
}

//
// Fun��o para c�lculo do valor do nodo, com uso de recursividade para percorrer a �rvore bin�ria
int ValorNo(struct Elemento *no)
{
    if (no == NULL)
    {
        return 0;
    }

    printf("%*sNodo %d [%s] ", nNivel * 2, "", no->Id, no->Dado);
    if (no->Processado == 0)
    {
        short n = (short)no->Dado[0];
        printf("(%d) ", n);
        // Testa de o dado do n� � um n�mero
        if (n >= 48 && n <= 57) // 48 = 0, 57 = 9 na tabela ASCII
        {
            no->Valor = (short)no->Dado[0] - 48;
            no->Processado = 1;
            printf("Valor = %d\n", no->Valor);
        }
        else
        {
            printf("\n");
            nNivel++;
            // Obt�m o valor dos nodos filhos, recursivamente
            int valorEsquerdo = ValorNo(no->nEsquerdo);
            int valorDireito = ValorNo(no->nDireito);
            nNivel--;
            // Verifica a opera��o matem�tica e efetua o c�lculo
            switch (n)
            {
            case 43: // '+':
                no->Valor = valorEsquerdo + valorDireito;
                no->Processado = 1;
                printf("Valor (Nodo %d) = %d + %d = %d\n", no->Id, valorEsquerdo, valorDireito, no->Valor);
                break;
            case 45: //'-':
                no->Valor = valorEsquerdo - valorDireito;
                no->Processado = 1;
                printf("Valor (Nodo %d) = %d - %d = %d\n", no->Id, valorEsquerdo, valorDireito, no->Valor);
                break;
            case 42: //'*':
                no->Valor = valorEsquerdo * valorDireito;
                no->Processado = 1;
                printf("Valor (Nodo %d) = %d * %d = %d\n", no->Id, valorEsquerdo, valorDireito, no->Valor);
                break;
            case 47: // '/':
                if (valorDireito != 0)
                {
                    no->Valor = valorEsquerdo / valorDireito;
                }
                else
                {
                    no->Valor = 0;
                }
                printf("Valor (Nodo %d) = %d / %d = %d\n", no->Id, valorEsquerdo, valorDireito, no->Valor);
                no->Processado = 1;
                break;
            default:
                printf("ERRO DADO INVALIDO [%s]\n", no->Dado[0]);
                break;
            }
        }
    }
    else
    {
        printf("Nodo previamente processado. Valor = %d\n", no->Valor);
    }
    return no->Valor;
}

//
// M�todo principal
int main()
{
    printf("**********************************************************\n");
    printf("* CALCULO DE EXPRESSOES MATEMATICAS COM ARVORES BINARIAS *\n");
    printf("* UNICESUMAR - ESOFT - ESTRUTURAS DE DADOS II            *\n");
    printf("* ALUNO: GUIONARDO FURLAN                   RA:1650466-5 *\n");
    printf("**********************************************************\n");
    MontaArvore();
    printf("# Calculando...\n\n");
    int Calculo = ValorNo(Raiz);
    printf("\n# Resultado: %d\n\n", Calculo);
    LiberaPonteiros(Raiz);
    return Calculo;
}
