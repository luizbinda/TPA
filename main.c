#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "DadosBancoOriginal.h"
#include "ArvoreAVL.h"

int getNum(){
	int num;
	printf("Digite um numero: ");
	scanf("%d", &num);
	return num;
}

int main(){
   	raiz = NULL; 

	int op = -1;
	int valor;
    while (op != 0){
        printf( "1 - (Arvore) Inserir novo elemento\n"
                "2 - (Arvore) Excluir elemento\n"
                "3 - (Arvore) Buscar elemento\n"
				"4 - (Vetor) Inserir Arquivos\n"
                "5 - (Vetor) Inserir novo elemento\n"
                "6 - (Vetor) Excluir elemento\n"
                "7 - (Vetor) Buscar elemento\n"
                "8 - (Arvore) Inserir Arquivos\n"
                "0 - Sair\n");
        scanf("%d",&op);
		switch (op){			
			case 1:{
				system("cls");
				dadosBancarios* novo = iniciarlista();
				system("cls");
				novo->id = getNum();
				raiz = inserirNodo(raiz, novo);
				system("pause");
				system("cls");
				break;
			}
			case 2:{
				system("cls");
				removerNodo(&raiz, getNum());
				system("pause");
				system("cls");
				break;			
			}
			case 3:{
				// pegando valor a ser procurado
				system("cls");				
				Nodo* aux = buscarValor(raiz, getNum());
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
				raiz = carregarArquivos(raiz, hash);
				system("pause");
				system("cls");
				break;
			}
			case 5:{
				system("cls");
				removerNodo(&raiz, getNum());
				system("pause");
				system("cls");
				break;			
			}
			case 6:{
				// pegando valor a ser procurado
				system("cls");				
				Nodo* aux = buscarValor(raiz, getNum());
				// Verificando se enconrou o numero pesquisado
				if(aux != NULL)
					printf("Id: %d  Saldo: %f  Nome: %s\n", aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);
				else
					printf("Nodo não encontrado\n");
				
				system("pause");
				system("cls");
				break;
			}
			case 7:{
				system("cls");
				printf("Altura: %d\n", calcularAltura(raiz));

				system("pause");
				system("cls");
				break;
			}
			case 8:{
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
			case 9:{
				system("cls");
				percorrerArvoreEmOrdemCrescente(raiz);
				system("pause");
				system("cls");
				
				percorrerArvoreEmOrdemDecrescente(raiz);
				system("pause");
				system("cls");
				break;
			}

		}
	}
	return 0;
}
