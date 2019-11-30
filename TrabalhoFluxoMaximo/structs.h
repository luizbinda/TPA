#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct grafo
{
    int vertices; // nó
    int arestas;  // caminho
    float **matriz;
    char **elementos;
};
typedef struct grafo Grafo;

float **iniciarMatriz(int numeroDeVertices);
Grafo *iniciarGrafo(int numeroDeVertices);
void inserirAresta(Grafo *G, int vertice, int aresta, int peso);
void exibirGrafo(Grafo *G);
Grafo *archive(char nome[], Grafo *G);
Grafo *GrafobyArchive(char nome[]);
void empilha(int x, int *vet, int *visitados, int *base);
int desempilha(int *topo, int *vet, int *visitados);
int bfs(int ini, int alvo, Grafo *C, Grafo *F, int *p);
int min_ret(int x, int y);

float **iniciarMatriz(int numeroDeVertices)
{ //Inicia matriz com 0

    float **matriz = (float **)malloc(numeroDeVertices * sizeof(int *));

    for (int i = 0; i < numeroDeVertices; i++)
    {
        matriz[i] = (float *)malloc(numeroDeVertices * sizeof(int));
        for (int j = 0; j < numeroDeVertices; ++j)
        {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

Grafo *iniciarGrafo(int linhas)
{ //Inicia grafo

    int l, c;

    Grafo *novo_grafo = (Grafo *)malloc(sizeof(Grafo));
    novo_grafo->vertices = linhas;
    novo_grafo->matriz = (float **)malloc(sizeof(float *) * linhas);
    novo_grafo->elementos = (char **)malloc(linhas * sizeof(char *));

    for (l = 0; l < linhas; l++)
        novo_grafo->matriz[l] = (float *)malloc(sizeof(float) * linhas);
    for (l = 0; l < linhas; l++)
        novo_grafo->elementos[l] = (char *)malloc(sizeof(char *) * linhas);

    for (l = 0; l < linhas; l++)
        for (c = 0; c < linhas; c++)
            novo_grafo->matriz[l][c] = 0;

    return novo_grafo;
};

void inserirAresta(Grafo *G, int vertice, int aresta, int peso)
{ //Insere um arco

    if (G->matriz[vertice][aresta] == 0 && peso != 0)
    {
        G->matriz[vertice][aresta] = peso;
        G->arestas++;
    }
}

void exibirGrafo(Grafo *G)
{ //Imprime grafo

    for (int v = 0; v < G->vertices; v++)
    {
        printf("%d: ", v);
        for (int w = 0; w < G->vertices; w++)
        {
            printf("%2f ", G->matriz[v][w]);
        }
        printf("\n");
    }
}

Grafo *archive(char nome[], Grafo *G)
{ //preenche a matriz
    FILE *arquivo;
    char linha[700];
    char *subString;
    float distancia;

    int c = 0; //contador coluna da matriz
    int l = 0; //contador linha da matriz
    arquivo = fopen(nome, "r");

    fgets(linha, 700, arquivo);
    while ((fgets(linha, 700, arquivo)) != NULL)
    {
        c = 0;
        subString = strtok(linha, ";");
        strcpy(G->elementos[l], subString);

        subString = strtok(NULL, ";");
        distancia = atof(subString);

        while (subString != NULL && c < G->vertices)
        {
            inserirAresta(G, l, c - 1, distancia);
            subString = strtok(NULL, ";");
            distancia = atof(subString);
            c++;
        }
        l++;
    }

    fclose(arquivo);
    return G;
}

Grafo *GrafobyArchive(char nome[])
{ //pega qtd de linhas do arquivo, cria um grafo vazio e chama preencher

    FILE *arquivo;
    char linha[700];
    int l = 0;

    arquivo = fopen(nome, "r");

    while (fgets(linha, 700, arquivo))
        l++;

    fclose(arquivo);

    return archive(nome, iniciarGrafo(l - 1));
}

void empilha(int x, int *vet, int *visitados, int *base)
{
    vet[*base] = x;
    *base = *base + 1;
    visitados[x] = 1;
}

int desempilha(int *topo, int *vet, int *visitados)
{
    int x = vet[*topo];
    *topo = *topo + 1;
    visitados[x] = 2;
    return x;
}

int bfs(int ini, int alvo, Grafo *C, Grafo *F, int *p)
{

    int i, v;
    int visitados[C->vertices];
    int vet[C->vertices + 2];

    for (i = 0; i < C->vertices; i++)
    {
        visitados[i] = 0;
    }

    int *topo = (int *)malloc(sizeof(int));
    int *base = (int *)malloc(sizeof(int));
    *topo = 0;
    *base = 0;

    empilha(ini, vet, visitados, base);
    p[ini] = -1;

    while (*topo != *base)
    {
        i = desempilha(topo, vet, visitados);
        //Procura todos os nodos adjacentes nao visitados.
        //Se a capacidade de i e v for positiva, empilha v
        for (v = 0; v < C->vertices; v++)
        {
            if (visitados[v] == 0 && C->matriz[i][v] - F->matriz[i][v] > 0)
            {
                empilha(v, vet, visitados, base);
                p[v] = i;
            }
        }
    }
    //se desempilhou entao o alvo foi alcancado
    return visitados[alvo] == 2;
}

int min_ret(int x, int y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

void fluxo_maximo(Grafo *C, int saida, int chegada)
{
    int i, j, u, cont = 1;
    int fluxo_max = 0;
    int p[C->vertices];
    Grafo *F = iniciarGrafo(C->vertices);

    //Incrementar o fluxo ao longo do caminho
    while (bfs(saida, chegada, C, F, p))
    {
        printf("\n\n|Iteracao %d|\n", cont);
        // Determino quanto vou incrementar no fluxo
        int incremento = 9999;
        for (u = C->vertices - 1; p[u] >= 0; u = p[u])
        {
            incremento = min_ret(incremento, C->matriz[p[u]][u] - F->matriz[p[u]][u]);
        }
        //entao incremento
        for (u = C->vertices - 1; p[u] >= 0; u = p[u])
        {
            F->matriz[p[u]][u] += incremento;
            //Caso nao digrafo F->matriz[u][p[u]] -= incremento;
            printf("\n(%d) para (%d) fluxo: %2f", p[u], u, F->matriz[p[u]][u]);
        }

        fluxo_max += incremento;
        cont++;
    }
    //sem mais caminhos possiveis
    printf("\nFluxo maximo: %d", fluxo_max);
}
