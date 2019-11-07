#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"

char *iniciarString(char *conteudo)
{
    char *string = (char *)malloc(sizeof(conteudo));
    strcpy(string, conteudo);
    return string;
}

int main()
{
    char string[100];
    printf("Digite o primeiro no: ");
    scanf("%s", string);
    char *primeiro_no = iniciarString(string);
    printf("Digite o segundo no: ");
    scanf("%s", string);
    char *segundo_no = iniciarString(string);
    printf("Digite o terceiro no: ");
    scanf("%s", string);
    char *terceiro_no = iniciarString(string);
    printf("Digite o quarto no: ");
    scanf("%s", string);
    char *quarto_no = iniciarString(string);

    Grafo *grafo = verifica_tamanho_arquivo("ProblemaSlideCaminhoMínimo.csv");
    grafo = ler_arquivo_distancias(grafo, "ProblemaSlideCaminhoMínimo.csv");
    imprime_grafo(grafo);

    printf("distancia nodo1 para nodo2: %d", algoritimo_dijskistra(grafo, 1, 2));

    return 0;
}
