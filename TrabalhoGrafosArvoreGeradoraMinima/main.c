#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include <locale.h>

int main()
{
	printf("A localidade corrente agora � %s \n", setlocale(LC_ALL, ""));
	grafoBairros *grafo = lerArquivo("MatrizBairros.csv");
	grafo = lerArquivoDistancias(grafo, "MatrizBairros.csv");
	listarGrafo(grafo);
	if (verifica_conexo(grafo) == 1)
		printf("Conexo\n");
	else
		printf("Não conexo\n");

	if (verifica_completo(grafo) == 1)
		printf("completo\n");
	else
		printf("Não completo\n");

	if (verifica_regular(grafo) == 1)
		printf("regular\n");
	else
		printf("Não regular\n");

	if (verifica_hamiltoniano(grafo) == 1)
		printf("hamiltoniano\n");
	else
		printf("Não hamiltoniano\n");
}
