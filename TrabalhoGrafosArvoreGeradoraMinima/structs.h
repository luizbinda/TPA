
typedef struct grafoBairros
{

	char **bairros;		 //vetor de string com nome das bairros
	float **distancias;  //matriz de distancias das cidades
	int numero_vertices; //quantidades de linhas e colunas da matriz

} grafoBairros;

grafoBairros *iniciarGrafo(int linhas)
{

	int i, j;

	//CRIA NOVO GRAFO COM BASE NA QUANTIDADE DE LINHAS E COLUNAS CONTADAS
	grafoBairros *novo_grafo = (grafoBairros *)malloc(sizeof(grafoBairros)); //aloca��o de memoria

	novo_grafo->numero_vertices = linhas;								 //numero de linhas ser� o numero de vertices
	novo_grafo->distancias = (float **)malloc(linhas * sizeof(float *)); //cria vetor de ponteiros para float

	for (i = 0; i < linhas; i++)
	{																		 //percorre o vetor de ponteiros
		novo_grafo->distancias[i] = (float *)malloc(linhas * sizeof(float)); //criar um vetor de ponteiros para cada posi��o
	}

	//PREENCHE TODAS AS DISTANCIAS COM 0
	for (i = 0; i < linhas; i++)
	{
		for (j = 0; j < linhas; j++)
		{
			novo_grafo->distancias[i][j] = 0; //atribui 0 para todas as posições da matriz
		}
	}

	return novo_grafo;
}

void listarGrafo(grafoBairros *grafo)
{

	printf("\n\n IMPRESSAO DA MATRIZ DE DISTANCIAS \n\n");

	int l, c;

	if (grafo != NULL)
	{
		for (l = 0; l < grafo->numero_vertices; l++)
		{
			for (c = 0; c < grafo->numero_vertices; c++)
			{
				if (c == 0 || c == 46)
					printf("%.2f	", grafo->distancias[l][c]);
			}
			printf("\n");
		}
	}
}

grafoBairros *lerArquivo(char *path_arquivo)
{
	printf("\n --- LENDO ARQUIVO ---\n");

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
			printf("linha: %d\n", l);
		}
	}
	fclose(arquivo); //fecha o arquivo

	grafoBairros *novo_grafo = iniciarGrafo(l); //cria a estrutura para montar o grafo

	system("pause");
	system("cls");

	return novo_grafo; //cria a estrutura para montar o grafo
}

void inserir_aresta(grafoBairros *grafo, int origem, int destino, float distancia)
{

	//printf("\n Linha: %d", origem);
	//printf("\n Coluna: %d", destino);
	//printf("\n Distancia: %f", distancia);
	//system("pause");

	if (grafo != NULL && origem <= grafo->numero_vertices && destino <= grafo->numero_vertices && distancia >= 0)
	{

		grafo->distancias[origem][destino - 1] = distancia;
	}
}

grafoBairros *lerArquivoDistancias(grafoBairros *grafo, char *path)
{

	printf("\n --- LENDO ARQUIVO ---\n");

	FILE *arquivo;
	char linha[700];
	char *subString;
	float distancia;

	int c = 0; //contador coluna da matriz
	int l = 0; //contador linha da matriz

	arquivo = fopen(path, "r");

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

				c = 0;							//zera o contador de colunas para cada linha do arquivo
				subString = strtok(linha, ";"); //divide a linha pelo ;
				distancia = atof(subString);

				while (subString != NULL, c < grafo->numero_vertices + 1)
				{

					if (c != 0)
						inserir_aresta(grafo, l, c, distancia);

					subString = strtok(NULL, ";");
					distancia = atof(subString);

					c++;
				}
				l++; //para cada liha lida... incrementa o contador
			}
		}
		fclose(arquivo);
	}

	system("pause");
	system("cls");

	return grafo;
}
