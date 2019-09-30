#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "DadosBancoOriginal.h"
#include "ArvoreAVL.h"

int main(){
   	raiz = NULL;
	hash = iniciarHash();
	hash = iniciarVetorHash(hash, TAMVET);
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
                "8 - Verificar Arvore Estritamente Binaria e Completa\n"
                "9 - Verificar Espelhamento\n"
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
				hash = inserirHash(hash, buscarValor(raiz, novo->id), calcularHashPosDivisao(novo->id,TAMVET));
				
				system("pause");
				system("cls");
				break;
			}
			case 2:{
				system("cls");
				printf("Digite o numero que deseja Excluir: ");
				scanf("%d", &valor);
				system("cls");
				hash = excluirHash(hash, valor);
				removerNodo(&raiz, valor);
				
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
					printf("Arvore tempo: %lf --Id: %d  Saldo: %f  Nome: %s\n", total_tempo_arvore, aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);

					// contando tempo e buscando valor na hash
					double inicio_buscar_hash = (double)clock();
					aux = pesquisarHash(hash, valor, calcularHashPosDivisao(valor, TAMVET));
					double fim_buscar_hash = (double)clock();
					double total_tempo_hash = (double) (inicio_buscar_hash - fim_buscar_hash) / CLOCKS_PER_SEC;
					printf("Hash tempo : %lf -- Id: %d  Saldo: %f  Nome: %s\n", total_tempo_hash, aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);
					printf("tempo ini Arvore %lf -- tempo fim Hash %lf \n", inicio_buscar_arvore, fim_buscar_arvore);
					printf("tempo ini Hash %lf -- tempo fim Arvore %lf \n", inicio_buscar_hash, fim_buscar_hash);
					printf("difrenca entre tempos: %lf \n",total_tempo_arvore - total_tempo_hash);
				
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
				
				percorrerArvoreEmOrdemDecrescente(raiz);
				system("pause");
				system("cls");
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
				Nodo* aux = buscarValor(raiz, valor);
				if(aux != NULL){
					calcularNivel(raiz, valor, 0);			
					printf("Nivel: %d\n", aux->nivel);
				}
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
			case 9:{
				system("cls");
				Hashing* arvore_invertida;
				arvore_invertida = iniciarHash();
				arvore_invertida = iniciarVetorHash(arvore_invertida, TAMVET);
				arvore_invertida = carregarArvoreInvertida(raiz, arvore_invertida);

				if (verificarEspelhamento(raiz, arvore_invertida, 0) == 1)
					printf("Arvore espelhada!\n");
				else
					printf("Arvore Nao espelhada!\n");
				
				free(arvore_invertida);
				
				system("pause");
				system("cls");

				break;
			}
		}
	}
	return 0;
}
