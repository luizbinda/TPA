#include "structs.h"

typedef struct dadosAdjacencia
{
    int posicao;
    float distancia;
    struct dadosAdjacencia *prox;

} dadosAdjacencia;

typedef struct listaAdjacencia
{
    dadosAdjacencia **dados;

} listaAdjacencia;

typedef struct kruscal
{
    float peso;
    int origem;  //posi��o matriz
    int destino; //posi��o matriz
} T_kruscal;

dadosAdjacencia *iniciarDados()
{
    dadosAdjacencia *dados = (dadosAdjacencia *)malloc(sizeof(dadosAdjacencia));
    dados->posicao = 0;
    dados->distancia = 0;
    dados->prox = NULL;
    return dados;
}

dadosAdjacencia **iniciarDadosListaAdjacencia(int tam_vetor)
{
    dadosAdjacencia **dados = (dadosAdjacencia **)malloc(sizeof(dadosAdjacencia *) * tam_vetor);
    int i;
    for (i = 0; i < tam_vetor; i++)
    {
        dados[i] = iniciarDados();
    }
    return dados;
}

listaAdjacencia *iniciarListaAdjacencia(int tam_vetor)
{
    listaAdjacencia *lista = (listaAdjacencia *)malloc(sizeof(listaAdjacencia));
    lista->dados = iniciarDadosListaAdjacencia(tam_vetor);
    return lista;
}

listaAdjacencia *copiarMatriz(grafoBairros *grafo, listaAdjacencia *lista)
{
    int l, c;

    if (grafo != NULL)
    {
        for (l = 0; l < grafo->numero_vertices; l++)
        {
            for (c = 0; c < grafo->numero_vertices; c++)
            {
                if (grafo->distancias[l][c] != 0)
                {
                    if (lista->dados[l]->distancia == 0)
                    {
                        lista->dados[l]->distancia = grafo->distancias[l][c];
                        lista->dados[l]->posicao = c;
                        //printf("coluna: %i/ distancia: %.2f \n", c, lista->dados[l]->distancia);
                    }
                    else
                    {
                        dadosAdjacencia *aux = lista->dados[l];
                        while (aux->prox != NULL)
                        {
                            aux = aux->prox;
                        }

                        aux->prox = iniciarDados();
                        aux->prox->distancia = grafo->distancias[l][c];
                        aux->prox->posicao = c;
                        //printf("coluna: %i/ distancia: %.2f\n ", c, aux->prox->distancia);
                    }
                }
            }
        }
    }

    return lista;
}

void listarLista(listaAdjacencia *lista, int tam)
{
    int i;
    for (i = 0; i < tam; i++)
    {
        dadosAdjacencia *aux = lista->dados[i];
        printf("\npos: %d\n", i);
        while (aux != NULL)
        {
            printf("%.2f/ ", aux->distancia);
            aux = aux->prox;
        }
    }
}

listaAdjacencia *algoritimo_kruscal(listaAdjacencia *lista, int tam)
{
    listaAdjacencia *kruscal = iniciarListaAdjacencia(tam);
    int i, j = 0, origem;
    int contador = 0;
    dadosAdjacencia *menorPeso;

    int arvore[tam];

    for (i = 0; i < tam; i++)
        arvore[i] = -1;

    dadosAdjacencia **lista_menor_peso = (dadosAdjacencia **)malloc(sizeof(dadosAdjacencia *) * tam);
    for (i = 0; i < tam; i++)
        lista_menor_peso[i] = NULL;

    while (contador != 1)
    {
        contador = 0;
        menorPeso = iniciarDados();
        menorPeso->distancia = 100;
        for (i = 0; i < tam; i++)
        {
            dadosAdjacencia *aux = lista->dados[i];
            while (aux)
            {
                if (menorPeso->distancia > aux->distancia)
                {
                    menorPeso = aux;
                    origem = i;
                }
                aux = aux->prox;
            }
        }

        while (lista_menor_peso[j] != NULL)
            j++;
        lista_menor_peso[j] = menorPeso;

        if (arvore[menorPeso->posicao] == arvore[origem])
        {
            if (kruscal->dados[origem]->distancia == 0)
                kruscal->dados[origem] = menorPeso;
            else
            {
                dadosAdjacencia *aux_kruscal = kruscal->dados[origem];
                while (aux_kruscal->prox != NULL)
                {
                    aux_kruscal = aux_kruscal->prox;
                }
                aux_kruscal->prox = iniciarDados();
                aux_kruscal->prox = menorPeso;
            }

            arvore[menorPeso->posicao] += arvore[origem];
            arvore[origem] = menorPeso->posicao;
        }
        else if (arvore[menorPeso->posicao] != arvore[origem])
        {
        }

        for (i = 0; i < tam; i++)
        {
            if (arvore[i] < 0)
                contador++;
            //printf("arvore[%d]: %d\n", i, arvore[i]);
        }
    }
    return kruscal;
}