#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"

char *inserirString(int size)
{
    char *string = (char *)malloc(size);
    fflush(stdin);
    fgets(string, size * 2, stdin);
    string[strlen(string) - 1] = '\0';
    return string;
}

char **getCaminho(int total_vertices, int max_tamanho_do_caminho)
{
    char **caminho = (char **)malloc(sizeof(char *) * max_tamanho_do_caminho * total_vertices);
    printf("Insira os nos.\n");

    int i;
    for (i = 0; i < total_vertices; ++i)
    {
        printf("No %d: ", i + 1);
        fflush(stdin);
        caminho[i] = inserirString(max_tamanho_do_caminho);
    }
    return caminho;
}

int main()
{
    Grafo *grafo = verifica_tamanho_arquivo("ProblemaSlideCaminhoMínimo.csv");
    grafo = ler_arquivo_distancias(grafo, "ProblemaSlideCaminhoMínimo.csv");

    int i, tamanhoDoCaminho = 4, distanciaTotal = 0;

    char **caminho = getCaminho(tamanhoDoCaminho, 100);

    for (i = 0; i < tamanhoDoCaminho - 1; ++i)
        realizarDijkstra(
            grafo,
            caminho[i],
            caminho[i + 1],
            &distanciaTotal);
    printf("Distancia Total: %d\n", distanciaTotal);

    return 0;
}
