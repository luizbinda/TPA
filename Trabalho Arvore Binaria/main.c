#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "DadosBancoOriginal.h"
#include "Arvore.h"

int main(){
   	raiz = NULL;
	Hashing* hash;
	hash = iniciarHash();
	hash = iniciarVetorHash(hash, 50);
	raiz = carregarArquivos(raiz, hash);

	int op = -1;
	int valor;
    while (op != 0){
        printf( "1 - Inserir novo elemento\n"
                "2 - Excluir elemento\n"
                "3 - Buscar elemento\n"
                "4 - Imprimir em ordem Crescente e Decrescente\n"
                "5 - Imprimir total de nodos\n"
                "6 - Imprimir altura da arvore\n"
                "7 - Imprimir nivel de um nodo\n"
                "8 - Estritamente Binaria e Completa\n"
                "0 - Sair\n");
        scanf("%d",&op);
		switch (op){
			case 1:{
				system("cls");
				dadosBancarios* novo = iniciarlista();
				printf("Digite o numero que deseja inserir: ");
				scanf("%d", &valor);
				system("cls");
				novo->id = valor;
				raiz = inserirNodo(raiz, novo);
				hash = inserirHash(hash, buscarValor(raiz, novo->id), calcularHashPosDivisao(novo->id,50));
				
				system("pause");
				system("cls");
				break;
			}
			case 2:{
				system("cls");
				printf("Digite o numero que deseja Excluir: ");
				scanf("%d", &valor);
				system("cls");
				removerNodo(raiz, valor);

				system("pause");
				system("cls");
				break;			
			}
			case 3:{
				// pegando valor a ser procurado
				system("cls");
				printf("Digite o numero que deseja Buscar: ");
				scanf("%d", &valor);
				system("cls");
				
				// contando tempo pela busca na arvore
				double inicio_buscar_arvore = (double)clock();
				Nodo* aux = buscarValor(raiz, valor);
				double fim_buscar_arvore = (double)clock();
				double total_tempo_arvore = (double) (inicio_buscar_arvore - fim_buscar_arvore) / CLOCKS_PER_SEC;
				
				// Verificando se enconrou o numero pesquisado
				if(aux != NULL){
					printf("Arvore tempo: %d --Id: %d  Saldo: %f  Nome: %s\n", total_tempo_arvore, aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);

					// contando tempo e buscando valor na hash
					double inicio_buscar_hash = (double)clock();
					aux = pesquisarHash(hash, valor, calcularHashPosDivisao(valor, 50));
					double fim_buscar_hash = (double)clock();
					double total_tempo_hash = (double) (inicio_buscar_hash - fim_buscar_hash) / CLOCKS_PER_SEC;
					printf("Hash tempo : %d -- Id: %d  Saldo: %f  Nome: %s\n", total_tempo_hash, aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);
					printf("tempo ini Arvore %d -- tempo fim Hash %d \n", inicio_buscar_arvore, fim_buscar_arvore);
					printf("tempo ini Hash %d -- tempo fim Arvore %d \n", inicio_buscar_hash, fim_buscar_hash);
					printf("difrenca entre tempos: %d \n",total_tempo_arvore - total_tempo_hash);
				
				}
				else
					printf("Nodo não encontrado\n");
				
				system("pause");
				system("cls");
				break;
			}
			case 4:{
				system("cls");
				percorrerArvoreEmOrdemCrescente(raiz);
				system("pause");
				system("cls");
				/*
				percorrerArvoreEmOrdemDecrescente(raiz);
				system("pause");
				system("cls");
				listarHashFechada(hash, 50);

				system("pause");
				system("cls");
				*/
				break;
			}
			case 5:{
				system("cls");
				printf("total de Nodos: %d\n", calcularTotalNodos(raiz));	

				system("pause");
				system("cls");
				break;
			}
			case 6:{
				system("cls");
				printf("Altura: %d\n", calcularAltura(raiz));

				system("pause");
				system("cls");
				break;
			}
			case 7:{
				system("cls");
				printf("Digite o numero que deseja Buscar: ");
				scanf("%d", &valor);
				system("cls");
				calcularNivel(raiz, valor, 0);			
				Nodo* aux = buscarValor(raiz, valor);
				if(aux != NULL)
					printf("Nivel: %d\n", aux->nivel);
				else
					printf("Nodo não encontrado\n");

				system("pause");
				system("cls");
				break;
			}
			case 8:{
				system("cls");
				if(estritamenteBinaria(raiz) == 1 && estritamenteBinariaCompleta(raiz) == 1 )
					printf("Estritamente Binaria e Completa\n");
				else if(estritamenteBinaria(raiz) == 1 && estritamenteBinariaCompleta(raiz) == 0)
					printf("Estritamente Binaria e incompleta\n");
				else
					printf("Nao eh Estritamente Binaria\n");

				system("pause");
				system("cls");
				break;
			}
		}
	}
	return 0;
}
