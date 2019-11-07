
typedef struct grafoBairros
{
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
				if (c == 0)
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
				 //printf("linha: %d\n", l);
		}
	}
	fclose(arquivo); //fecha o arquivo

	grafoBairros *novo_grafo = iniciarGrafo(l); //cria a estrutura para montar o grafo

	//system("pause");
	//system("cls");

	return novo_grafo; //cria a estrutura para montar o grafo
}

void inserir_aresta(grafoBairros *grafo, int origem, int destino, float distancia)
{

	printf("\n Linha: %d", origem);
	printf("\n Coluna: %d", destino);
	printf("\n Distancia: %f", distancia);
	//system("pause");

	if (grafo != NULL && origem <= grafo->numero_vertices && destino <= grafo->numero_vertices && distancia >= 0)
	{
		grafo->distancias[origem][destino - 1] = distancia;
	}
}

grafoBairros *lerArquivoDistancias(grafoBairros *grafo, char *path)
{
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
				//distancia = atof(subString);

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

	//system("pause");
	//system("cls");

	return grafo;
}

int verifica_conexo(grafoBairros *grafo)
{ //VERIFICA SE TODOS OS VERTICES S�O CONECTADOS

	int linha, coluna;
	int contador = 0;

	if (grafo != NULL)
	{ //VERIFICA SE O GRAFO � VALIDO

		for (linha = 0; linha < grafo->numero_vertices; linha++)
		{ //PERCORRE TODOS OS VERTICES DO GRAFO (MATRIZ)
			contador = 0;
			for (coluna = 0; coluna < grafo->numero_vertices; coluna++)
			{ //PERCORRE TODOS OS VIZINHOS DO VERTICE ATUAL
				if (grafo->distancias[linha][coluna] != 0)
				{				//SE O VERTICE POSSUI UMA CONEXÇÃO
					contador++; //INCREMENTA COTADOR
				}
			}

			if (contador == 0)
			{ //SE O CONTADOR CONTINUAR 0... VERTICE ATUAL N�O POSSUI CONEX�ES
				return 0;
			}
		}
	}

	return 1; //SE PERCCOREU TODOS OS VERTICE... TODOS POSSUEM CONEX�ES
}

int verifica_completo(grafoBairros *grafo)
{ //VERIFICA SE TODOS OS VERTICES S�O ADJACENTES

	int linha, coluna;
	int contador = 0;

	if (grafo != NULL)
	{ //VERIFICA SE O GRAFO É VALIDO

		for (linha = 0; linha < grafo->numero_vertices; linha++)
		{ //PERCORRE TODOS OS VERTICES DO GRAFO (MATRIZ)
			contador = 0;
			for (coluna = 0; coluna < grafo->numero_vertices; coluna++)
			{ //PERCORRE TODOS OS VIZINHOS DO VERTICE ATUAL
				if (grafo->distancias[linha][coluna] != 0)
				{				//SE O VERTICE POSSUI UMA CONEX�O
					contador++; //INCREMENTA COTADOR
				}
			}

			if ((grafo->numero_vertices - contador) > 1)
			{ //SE O RESULTADO FOR MAIOR QUE 1... ALGUM VERTICE NÃO POSSUI CONEXÃO COM TODOS OS OUTROS
				return 0;
			}
		}
	}

	return 1;
}

int verifica_regular(grafoBairros *grafo)
{ //VERTICES COM MESMO NUMERO DE ARESTAS

	int linha, coluna;
	int contador_1 = 0;
	int contador_2 = 0;

	if (grafo != NULL)
	{ //VERIFICA SE O GRAFO E VALIDO
		//PRIMEIRO VERTICE
		for (coluna = 0; coluna < grafo->numero_vertices; coluna++)
		{ //PERCORRE TODOS AS CONEXÕES DO PRIMEIRO VERTICE
			if (grafo->distancias[0][coluna] != 0)
			{				  //SE O VERTICE POSSUI UMA CONEXÃO
				contador_1++; //INCREMENTA COTADOR
			}
		}

		//A PARTIR DO SEGUNDO VERTICE
		for (linha = 1; linha < grafo->numero_vertices; linha++)
		{ //PERCORRE TODOS OS VERTICES A PARTIR DO SEGUNDO
			contador_2 = 0;
			for (coluna = 0; coluna < grafo->numero_vertices; coluna++)
			{ //PERCORRE TODOS OS VIZINHOS DO VERTICE ATUAL
				if (grafo->distancias[linha][coluna] != 0)
				{				  //SE O VERTICE POSSUI UMA CONEXÃO
					contador_2++; //INCREMENTA COTADOR
				}
			}

			if (contador_1 != contador_2)
			{ //SE O NUMERO DE CONXÕES FOR DIFERENTE... O GRAFO NÃO É REGULAR
				return 0;
			}
		}
	}

	return 1; //SE O NUMERO DE CONEXÕES DE TODOS OS VERTICES FOREM IGUAIS
}

int verifica_hamiltoniano(grafoBairros *grafo)
{ //PASSAR POR TODOS OS VERTICES SEM REPETIR

	int linha, coluna, i;
	int visitados[grafo->numero_vertices]; //vetor de vertices visitados

	for (i = 0; i < grafo->numero_vertices; i++)
	{					   //inicialmente todos os vertices ainda nao foram visitados
		visitados[i] = -1; //marca todos os vertices como nao visitados
	}
	visitados[i] = 1; //marca o vertice 0 como inicial

	if (grafo != NULL)
	{ //VERIFICA SE O GRAFO E VALIDO

		for (linha = 0; linha < grafo->numero_vertices; linha++)
		{ //PERCORRE TODOS OS VERTICES DO GRAFO (MATRIZ)
			if (visitados[i] != -1)
			{
				for (coluna = 0; coluna < grafo->numero_vertices; coluna++)
				{ //PERCORRE TODOS OS VIZINHOS DO VERTICE ATUAL
					if (visitados[coluna] == -1 && grafo->distancias[linha][coluna] > 0)
					{
						visitados[coluna] = 1;
					}
				}
			}
		}
	}

	for (i = 0; i < grafo->numero_vertices; i++)
	{
		if (visitados[i] == -1)
		{
			return 0;
		}
	}

	return 1;
}
