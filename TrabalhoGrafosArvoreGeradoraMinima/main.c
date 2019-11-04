#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "listaAdjacencia.h"

int main()
{
	printf("A localidade corrente agora � %s \n", setlocale(LC_ALL, ""));
	grafoBairros *grafo = lerArquivo("MatrizBairros.csv");
	grafo = lerArquivoDistancias(grafo, "MatrizBairros.csv");
	listarGrafo(grafo);
	listaAdjacencia *lista = iniciarListaAdjacencia(grafo->numero_vertices);
	lista = copiarMatriz(grafo, lista);
	listarLista(lista, grafo->numero_vertices);
	//listaAdjacencia *kruscal = algoritimo_kruscal(lista, grafo->numero_vertices);
	//listarLista(kruscal, grafo->numero_vertices);
}
