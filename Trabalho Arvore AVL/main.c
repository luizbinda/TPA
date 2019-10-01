#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "DadosBancoOriginal.h"
#include "ArvoreAVL.h"

int main(){
   	raiz = NULL;
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
				
				system("pause");
				system("cls");
				break;
			}
			case 2:{
				system("cls");
				printf("Digite o numero que deseja Excluir: ");
				scanf("%d", &valor);
				system("cls");
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
				
				Nodo* aux = buscarValor(raiz, valor);
			
				// Verificando se enconrou o numero pesquisado
				if(aux != NULL)
					printf("Id: %d  Saldo: %f  Nome: %s\n", aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);
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

		}
	}
	return 0;
}
