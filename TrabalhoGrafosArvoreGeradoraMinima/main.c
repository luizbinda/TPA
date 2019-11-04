#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "listaAdjacencia.h"

int main()
{
	printf("A localidade corrente agora � %s \n", setlocale(LC_ALL, ""));
	system("cls");
	grafoBairros *grafo = lerArquivo("MatrizBairros.csv");
	grafo = lerArquivoDistancias(grafo, "MatrizBairros.csv");

	int op = -1;
	int valor;
	while (op != 0)
	{
		printf("1 - grafo conexo\n"
			   "2 - grafo completo\n"
			   "3 - grafo regular\n"
			   "4 - caminho hamiltoniano\n"
			   "0 - Sair\n");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
		{
			system("cls");
			if (verifica_conexo == 1)
				printf("\n GRAFO CONEXO \n\n");
			else
				printf("\n GRAFO NAO CONEXO \n\n");

			system("pause");
			system("cls");
			break;
		}
		case 2:
		{
			system("cls");
			if (verifica_completo == 1)
				printf("\n GRAFO COMPLETO \n\n");
			else
				printf("\n GRAFO NAO COMPLETO \n\n");

			system("pause");
			system("cls");
			break;
		}
		case 3:
		{
			system("cls");
			if (verifica_regular == 1)
				printf("\n GRAFO REGULAR \n\n");
			else
				printf("\n GRAFO NAO REGULAR \n\n");

			system("pause");
			system("cls");
			break;
		}
		case 4:
		{
			system("cls");
			if (verifica_hamiltoniano == 1)
				printf("\n GRAFO COM CAMINHO HAMILTONIANO \n\n");
			else
				printf("\n GRAFO SEM CAMINHO HAMILTONIANO \n\n");

			system("pause");
			system("cls");
			break;
		}
		case 5:
		{
			system("cls");

			system("pause");
			system("cls");
			break;
		}
		case 6:
		{
			system("cls");

			system("pause");
			system("cls");
			break;
		}
		}
	}
}
