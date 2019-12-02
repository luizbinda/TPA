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

struct veiculos
{
    float capacidade; 
    char *motorista; 
    char *codigo;
    int alocado; 
};

typedef struct grafo Grafo;
typedef struct veiculos Veiculos;

Grafo *iniciarGrafo(int numeroDeVertices);
void inserirAresta(Grafo *G, int vertice, int aresta, int peso);
void exibirGrafo(Grafo *G);
Grafo *archive(char nome[], Grafo *G);
Grafo *GrafobyArchive(char nome[]);
void empilha(int x, int *vet, int *visitados, int *base);
int desempilha(int *topo, int *vet, int *visitados);
int bfs(int ini, int alvo, Grafo *C, Grafo *F, int *p);
int min_ret(int x, int y);
void fluxo_maximo(Grafo *C, int saida, int chegada, Veiculos **veiculos, int total, Grafo *distancias);
int buscarNome(Grafo *G, char nome[]);

///////////////////////////////////////////////////////
Veiculos **iniciarVeiculos(int quantidadeDeVeiculos);
int VeiculosbyArchive(char nome[]);
Veiculos **archiveVeiculos(char nome[], Veiculos **V);
void exibirVeiculos(Veiculos **veiculos, int total);
int alocarVeiculo(int fluxo, Veiculos **veiculos, int total);
void listarVeiculosNaoAlocados(Veiculos **veiculos, int total);


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
    int v, w;

    for (v = 0; v < G->vertices; v++)
    {
        printf("%s: ", G->elementos[v]);
        for ( w = 0; w < G->vertices; w++)
        {
            printf("%2.f ", G->matriz[v][w]);
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
            inserirAresta(G, l, c , distancia);
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

void fluxo_maximo(Grafo *C, int saida, int chegada, Veiculos **veiculos, int total, Grafo *distancias)
{
    int i, j, u, cont = 1;
    int fluxo_max = 0;
    int p[C->vertices];
    Grafo *F = iniciarGrafo(C->vertices); 
    F->elementos = C->elementos; // faz o grafo auxiliar aponta para lista de nomes
    
    //Incrementar o fluxo ao longo do caminho
    while (bfs(saida, chegada, C, F, p))
    {
        int distanciaTotal = 0;
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
            printf("\n(%s) para (%s)", C->elementos[p[u]], C->elementos[u]);
            distanciaTotal += distancias->matriz[p[u]][u]; // soma a distancia de acordo com a matriz de distancias
        }
        printf("\n\nFluxo(%d) \n", incremento);
        printf("\nDistacnia Total(%d)\n", distanciaTotal);
        int alocado = alocarVeiculo(incremento, veiculos, total); // funcao para alocar veiculos
        if (alocado == 0) // se alocou todos os veiculos desfaz o ultimo incremento de fluxo
        {
            for (u = C->vertices - 1; p[u] >= 0; u = p[u])
            {
                F->matriz[p[u]][u] -= incremento;
            }
            break;        
        }

        fluxo_max += incremento;
        cont++;
    }

    //sem mais caminhos possiveis ou todos veiculos alocados
    printf("\nQuantidade de Carga Pendente \n\n" );
    
    int v, w;
    for (v = 0; v < C->vertices; v++) // calcula quantidade de carga disponivel
    {
        for ( w = 0; w < C->vertices; w++)
        {
            C->matriz[v][w] -= F->matriz[v][w];
        }
    }
    exibirGrafo(C); 
}

int buscarNome(Grafo *G, char nome[])
{
    int v, w;
    for (v = 0; v < G->vertices; v++)
    {
        if ( strcmp(nome, G->elementos[v]) == 0)        
            return v;   
    }
    return -1;

}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
Veiculos **iniciarVeiculos(int quantidadeDeVeiculos){
    
    int l;

    Veiculos **veiculos = (Veiculos **)malloc(sizeof(Veiculos) * quantidadeDeVeiculos);
    
    for (l = 0; l < quantidadeDeVeiculos; l++)
    {
        veiculos[l] = (Veiculos *)malloc(sizeof(Veiculos));
        veiculos[l]->codigo = (char*)malloc(sizeof(char*));
        veiculos[l]->motorista = (char*)malloc(sizeof(char*));
        veiculos[l]->capacidade = 0;
        veiculos[l]->alocado = 0;
    }
    
    return veiculos;

}

int VeiculosbyArchive(char nome[])
{ //pega qtd de linhas do arquivo e retorna

    FILE *arquivo;
    char linha[700];
    int l = 0;

    arquivo = fopen(nome, "r");

    while (fgets(linha, 700, arquivo))
        l++;

    fclose(arquivo);

    return l;
}

Veiculos **archiveVeiculos(char nome[], Veiculos **V)
{ //preenche a matriz
    FILE *arquivo;
    char linha[700];
    char *subString;
    float capacidade;

    int l = 0; //contador linha da matriz
    arquivo = fopen(nome, "r");

    while ((fgets(linha, 700, arquivo)) != NULL)
    {
        subString = strtok(linha, ";");
        strcpy(V[l]->codigo, subString);
        //printf("codigo: %s \n", subString);

        subString = strtok(NULL, ";");
        strcpy(V[l]->motorista, subString);
        //printf("motorista: %s \n", subString);


        subString = strtok(NULL, ";");
        //printf("capacidade: %s \n\n", subString);

        capacidade = atof(subString);
        V[l]->capacidade = capacidade;

        l++;
    }

    fclose(arquivo);
    return V;
}

void exibirVeiculos(Veiculos **veiculos, int total)
{
    int i;
    for ( i = 0; i < total; i++)
    {
        printf( "codigo: %s, motorista: %s, capacidade: %2.f\n", veiculos[i]->codigo,veiculos[i]->motorista, veiculos[i]->capacidade);
    }
    
}

int alocarVeiculo(int fluxo, Veiculos **veiculos, int total)
{
    int i;
    int *alocarPos = (int*)malloc(sizeof(int) * total);
    int alocado = -1;

    for ( i = 0; i < total; i++)
        alocarPos[i] = 0;
    
    for ( i = 0; i < total; i++)
    {
        if(veiculos[i]->alocado == 0 && veiculos[i]->capacidade >= fluxo)
            alocarPos[i] = 1;
    }

    for ( i = 0; i < total; i++)
    {
        if(alocado == -1 && alocarPos[i] == 1)
            alocado = i;
        else if (alocarPos[i] == 1)
        {
            if (veiculos[i]->capacidade < veiculos[alocado]->capacidade)
               alocado = i;            
        }        
    }
    if (alocado != -1)
    {
        veiculos[alocado]->alocado = 1;
        printf("\nVeiculo alocado\n");
        printf( " Codigo: %s\n motorista: %s\n capacidade: %2.f\n", veiculos[alocado]->codigo, veiculos[alocado]->motorista, veiculos[alocado]->capacidade);
        return 1;
    }
    else
    {
        for ( i = 0; i < total; i++)
        {
            if(veiculos[i]->alocado == 0)
            {
                printf("\nNao existe veiculo para este fluxo\n");
                return -1;
            }
        }
        printf("\n\nNao existe veiculos disponiveis suficientes!!!!!\n\n");  
    } 
    return 0;
    
}

void listarVeiculosNaoAlocados(Veiculos **veiculos, int total)
{
    int i;
    printf("\nVEICULOS NAO ALOCADOS\n");
    for ( i = 0; i < total; i++)
    {
        if (veiculos[i]->alocado == 0)
            printf( "\ncodigo: %s, motorista: %s, capacidade: %2.f", veiculos[i]->codigo,veiculos[i]->motorista, veiculos[i]->capacidade);
    }
}
