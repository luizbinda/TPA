typedef struct Grafo
{
    char **elementos;
    float **distancias;
    int numero_vertices;
} Grafo;

Grafo *inicializa_grafo(int linhas);
void inserir_aresta(Grafo *grafo, int origem, int destino, float distancia);
int algoritimo_dijskistra(Grafo *grafo, int origem, int destino);
int procura_Menor_Distancia(float *distancias, int *visitado, int numero_vertices);
Grafo *verifica_tamanho_arquivo(char *path_arquivo);
Grafo *ler_arquivo_distancias(Grafo *grafo, char *path_arquivo);

Grafo *inicializa_grafo(int linhas)
{
    int l, c;

    Grafo *novo_grafo = (Grafo *)malloc(sizeof(Grafo));
    novo_grafo->numero_vertices = linhas;
    novo_grafo->distancias = (float **)malloc(sizeof(float *) * linhas);
    novo_grafo->elementos = (char **)malloc(linhas * sizeof(char *));

    for (l = 0; l < linhas; l++)
        novo_grafo->distancias[l] = (float *)malloc(sizeof(float) * linhas);
    for (l = 0; l < linhas; l++)
        novo_grafo->elementos[l] = (char *)malloc(sizeof(char *) * linhas);

    for (l = 0; l < linhas; l++)
        for (c = 0; c < linhas; c++)
            novo_grafo->distancias[l][c] = 0;

    return novo_grafo;
}

void inserir_aresta(Grafo *grafo, int origem, int destino, float distancia)
{
    if (grafo != NULL && origem <= grafo->numero_vertices && destino <= grafo->numero_vertices && distancia >= 0)
        grafo->distancias[origem][destino] = distancia;
}

void imprime_grafo(Grafo *grafo)
{
    int i, j;
    if (grafo != NULL)
    {
        printf("Vertices:\n");
        for (i = 0; i < grafo->numero_vertices; ++i)
        {
            printf("[%s] ", grafo->elementos[i]);
        }
        printf("\n\n");

        printf("Arestas:\n");
        for (i = 0; i < grafo->numero_vertices; ++i)
        {
            for (j = 0; j < grafo->numero_vertices; ++j)
            {
                printf("[%.2f] ", grafo->distancias[i][j]);
            }
            printf("end\n");
        }
    }
    else
    {
        printf("Grafo Nulo.\n");
    }
}

int algoritimo_dijskistra(Grafo *grafo, int origem, int destino)
{
    int i;
    int menor;
    int contador = grafo->numero_vertices - 1;
    int numero_interacoes = 0;

    int *anterior = (int *)malloc(grafo->numero_vertices * sizeof(int));
    int *visitado = (int *)malloc(grafo->numero_vertices * sizeof(int));
    float *distancias = (float *)malloc(grafo->numero_vertices * sizeof(float));

    for (i = 0; i < grafo->numero_vertices; i++)
    {
        anterior[i] = -1;
        distancias[i] = -1;
        visitado[i] = 0;
    }
    distancias[origem] = 0;

    printf("Nodos visitados: ");
    printf("[%s] ", grafo->elementos[origem]);
    while (contador > 0)
    {
        menor = procura_Menor_Distancia(distancias, visitado, grafo->numero_vertices);
        if (menor == -1)
            break;
        visitado[menor] = 1;
        contador--;

        for (i = 0; i < grafo->numero_vertices; ++i)
        {
            if (grafo->distancias[menor][i] != 0)
            {
                if (distancias[i] < 0)
                {
                    distancias[i] = distancias[menor] + grafo->distancias[menor][i];
                    anterior[i] = menor;
                }
                else if (distancias[i] > distancias[menor])
                {
                    distancias[i] = distancias[menor] + grafo->distancias[menor][i];
                    anterior[i] = menor;
                }
            }
        }
        numero_interacoes++;
    }

    int *enderecos = (int *)malloc(sizeof(int) * grafo->numero_vertices);

    for (i = 0; i < grafo->numero_vertices; ++i)
        enderecos[i] = -1;

    int j;
    for (i = destino, j = 0; i != origem; i = anterior[i], ++j)
        enderecos[j] = i;

    for (i = grafo->numero_vertices - 1; i > 0; --i)
        if (enderecos[i] != -1)
            printf("[%s] ", grafo->elementos[enderecos[i]]);

    printf("[%s]", grafo->elementos[destino]);

    printf("\n");

    return distancias[destino];
}

int procura_Menor_Distancia(float *distancias, int *visitado, int numero_vertices)
{
    int i;
    int menor = -1;
    int primeiro = 1;

    for (i = 0; i < numero_vertices; ++i)
    {
        if (distancias[i] >= 0 && visitado[i] == 0)
        {
            if (primeiro)
            {
                menor = i;
                primeiro = 0;
            }
            else
            {
                if (distancias[menor] > distancias[i])
                    menor = i;
            }
        }
    }
    return menor;
}

Grafo *verifica_tamanho_arquivo(char *path_arquivo)
{
    FILE *arquivo;
    char linha[700];
    int l = 0;

    arquivo = fopen(path_arquivo, "r");

    if (arquivo == NULL)
        printf("\n !!! ERRO DE LEITURA DE ARQUIVO !!! \n\n");

    else
    {
        while (fgets(linha, 700, arquivo))
            l++;
    }
    fclose(arquivo);

    Grafo *novo_grafo = inicializa_grafo(l - 1);

    return novo_grafo;
}

Grafo *ler_arquivo_distancias(Grafo *grafo, char *path_arquivo)
{
    FILE *arquivo;
    char linha[700];
    char *subString;
    float distancia;

    int c = 0; //contador coluna da matriz
    int l = 0; //contador linha da matriz
    arquivo = fopen(path_arquivo, "r");

    if (arquivo == NULL)
    {
        printf("\n !!! ERRO DE LEITURA DE ARQUIVO !!! \n\n");
        system("pause");
    }
    else
    {
        fgets(linha, 700, arquivo);
        while ((fgets(linha, 700, arquivo)) != NULL)
        {
            c = 0;
            subString = strtok(linha, ";");
            strcpy(grafo->elementos[l], subString);

            subString = strtok(NULL, ";");
            distancia = atof(subString);

            while (subString != NULL && c < grafo->numero_vertices)
            {
                inserir_aresta(grafo, l, c - 1, distancia);
                subString = strtok(NULL, ";");
                distancia = atof(subString);
                c++;
            }
            l++;
        }
    }
    fclose(arquivo);
    return grafo;
}

int buscarNo(Grafo *grafo, char *name)
{
    int i;
    for (i = 0; i < grafo->numero_vertices; ++i)
        if (!strcmp(grafo->elementos[i], name))
            return i;

    return -1;
}

void realizarDijkstra(Grafo *grafo, char *node1, char *node2, int *distanciaTotal)
{
    printf("%s - %s\n", node1, node2);
    int distancia = algoritimo_dijskistra(
        grafo,
        buscarNo(grafo, node1),
        buscarNo(grafo, node2));

    printf("Distancia: ");
    if (distancia != -1)
    {
        *distanciaTotal += distancia;
        printf("%d", distancia);
    }
    else
    {
        printf("Sem caminho.");
    }

    printf("\n\n");
}
