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
    novo_grafo->distancias = (float **)malloc(linhas * sizeof(float *));
    novo_grafo->elementos = (char **)malloc(linhas * sizeof(char *));

    for (l = 0; l < linhas; l++)
        novo_grafo->distancias[l] = (float *)malloc(linhas * sizeof(float));

    for (l = 0; l < linhas; l++)
        novo_grafo->elementos[l] = (char *)malloc(linhas * sizeof(char));

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
    int l, c;

    if (grafo != NULL)
    {
        for (l = 0; l < grafo->numero_vertices; l++)
        {
            for (c = 0; c < grafo->numero_vertices; c++)
            {
                if (c == 0)
                    printf("%s ", grafo->elementos[l]);
                printf("%.2f	", grafo->distancias[l][c]);
            }

            printf("\n");
        }
    }
}

int algoritimo_dijskistra(Grafo *grafo, int origem, int destino)
{
    int i;
    int menor;
    int contador = grafo->numero_vertices - 1;
    int numero_interacoes = 0;

    int *anterior;
    float *distancias;
    int *visitado;

    anterior = (int *)malloc(grafo->numero_vertices * sizeof(int));
    distancias = (float *)malloc(grafo->numero_vertices * sizeof(float));
    visitado = (int *)malloc(grafo->numero_vertices * sizeof(int));

    for (i = 0; i < grafo->numero_vertices; i++)
    {
        anterior[i] = -1;
        distancias[i] = -1;
        visitado[i] = 0;
    }

    distancias[origem] = 0;

    while (contador > 0)
    {
        menor = procura_Menor_Distancia(distancias, visitado, grafo->numero_vertices);
        printf("%s  ", grafo->elementos[menor]);
        if (menor == -1)
            break;

        visitado[menor] = 1;
        contador--;

        for (i = 0; i < grafo->numero_vertices; i++)
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
    printf("\n");
    return distancias[destino];
}

int procura_Menor_Distancia(float *distancias, int *visitado, int numero_vertices)
{

    int i;
    int menor = -1;
    int primeiro = 1;

    for (i = 0; i < numero_vertices; i++)
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
    int l = 0; //contador linha da matriz

    arquivo = fopen(path_arquivo, "r");

    if (arquivo == NULL)
    {
        printf("\n !!! ERRO DE LEITURA DE ARQUIVO !!! \n\n");
    }
    else
    {
        fgets(linha, 700, arquivo);
        while (fgets(linha, 700, arquivo))
        {
            l++; //conta quantas linhas o arquivo possui para montar a matriz de de distancias
            //printf("linha: %d\n", l);
        }
    }
    fclose(arquivo); //fecha o arquivo

    Grafo *novo_grafo = inicializa_grafo(l);

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
        while (!feof(arquivo))
        {

            if ((fgets(linha, 700, arquivo)) != NULL)
            {
                c = 0;                          //zera o contador de colunas para cada linha do arquivo
                subString = strtok(linha, ";"); //divide a linha pelo ;

                strcpy(grafo->elementos[l], subString);

                while (c < grafo->numero_vertices + 1)
                {
                    if (c != 0)
                        inserir_aresta(grafo, l, c - 1, distancia);

                    subString = strtok(NULL, ";");
                    distancia = atof(subString);

                    c++;
                }
                l++;
            }
        }
        fclose(arquivo);
    }
    return grafo;
}
