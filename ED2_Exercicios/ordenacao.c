#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <sys/time.h>

#define qtdNumeros 20

int vetor[qtdNumeros];
int vetorinicial[qtdNumeros];
int ordenado = 0;
char forma[10];
int qtd;
long nanoSecs =0 ;

struct timespec watch; // Registro de cronômetro

void startWatch()
{
	nanoSecs=0;
	clock_gettime(CLOCK_MONOTONIC, &watch);
}

void stopWatch()
{
	struct timespec w2;
	clock_gettime(CLOCK_MONOTONIC, &w2);
	nanoSecs = w2.tv_nsec;	
}

void inicializarVetor()
{
	for (int i = 0; i < qtdNumeros; i++)
	{
		vetor[i] = 0;
		vetorinicial[i] = 0;
	}
}

void gerarVetorAleatorio()
{
	startWatch();
	printf("Gerando vetor aleatório...\n");
	srand(time(NULL));
	for (int i = 0; i < qtdNumeros; i++)
	{
		vetor[i] = rand() % 100;
		vetorinicial[i] = vetor[i];
	}
	stopWatch();
}

void mostrarLista()
{
	printf("Vetor inicial\n");
	for (int i = 0; i < qtdNumeros; i++)
	{
		printf("%03d ", vetorinicial[i]);
	}
	printf("\n\n");
	if (ordenado == 0)
	{
		return;
	}
	printf("Vetor ordenado [%s] = %d iterações\n", forma, qtd);
	for (int i = 0; i < qtdNumeros; i++)
	{
		printf("%03d ", vetor[i]);
	}
	printf("\n\n");
	printf("Duração: %lu ns\n\n",nanoSecs);


}

void cls()
{
#ifdef linux
	system("clear");
#else
	system("cls");
#endif
}

void mostrarMenu()
{
	cls();
	printf("*************************************************\n");
	printf("* ROTINAS DE ORDENAÇÃO                          *\n");
	printf("*************************************************\n");
	mostrarLista();
	printf("1. Gerar lista aleatória\n");
	printf("2. Classificar por BUBBLESORT\n");
	printf("3. Classificar por SELECTIONSORT\n");
	printf("0. Sair\n");
}

void Trocar(int *i1, int *i2)
{
	int i = *i1;
	*i1 = *i2;
	*i2 = i;
}

int classificarBubbleSort()
{
	startWatch();
	qtd = 0;
	int trocado;
	do
	{
		trocado = 0;
		for (int i = 0; i < qtdNumeros - 1; i++)
		{
			if (vetor[i] > vetor[i + 1])
			{
				Trocar(&vetor[i], &vetor[i + 1]);
				trocado = 1;
			}
			qtd++;
		}
	} while (trocado == 1);
stopWatch();
	return 1;
}

int classificarSelectionSort()
{
	startWatch();
	qtd = 0;
	int i, j, min, aux;
	for (i = 0; i < qtdNumeros - 1; i++)
	{
		min = i;
		for (j = (i + 1); j < qtdNumeros; j++)
		{
			if (vetor[j] < vetor[min])
			{
				min = j;
			}
			qtd++;
		}
		if (vetor[i] != vetor[min])
		{
			Trocar(&vetor[i], &vetor[min]);
		}
	}
	stopWatch();
	return 1;
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	inicializarVetor();
	int op = -1;
	while (op != 0)
	{
		mostrarMenu();
		scanf("%d", &op);
		fflush(stdin); // Limpa o buffer de teclado

		switch (op)
		{
		case 1:
			gerarVetorAleatorio();
			ordenado = 0;
			strcpy(forma, "");
			break;
		case 2:
			ordenado = classificarBubbleSort();
			strcpy(forma, "BUBBLESORT");
			break;
		case 3:
			ordenado = classificarSelectionSort();
			strcpy(forma, "SELECTIONSORT");
			break;
		}
	}

	return 0;
}
