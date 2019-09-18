#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DadosBancoOriginal.h"
#include "Arvore.h"

int main(){
   	raiz = NULL;
	raiz = carregarArquivos(raiz);
	raiz->altura = calcularAltura(raiz);

	int op = -1;
	int valor;
    while (op != 0){
        printf( "1 - Inserir novo elemento\n"
                "2 - Exluir elemento\n"
                "3 - Buscar elemento\n"
                "4 - Imprimir em ordem Crescente\n"
                "5 - Imprimir em ordem Decrescente\n"
                "6 - Imprimir altura da arvore\n"
                "7 - Imprimir nivel de um nodo\n"
                "8 - Estritamente Binaria\n"
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
				raiz->altura = calcularAltura(raiz);
				system("pause");
				system("cls");
				break;
			}
			case 2:{
				system("cls");
				printf("Digite o numero que deseja inserir: ");
				scanf("%d", &valor);
				system("cls");
				removerNodo(raiz, valor);
				break;	
			}
			case 3:{
				system("cls");
				printf("Digite o numero que deseja inserir: ");
				scanf("%d", &valor);
				system("cls");
				Nodo* aux = buscarValor(raiz, valor);
				if(aux != NULL)
					printf("Id: %d  Saldo: %f  Nome: %s\n", aux->cliente->id, aux->cliente->saldo, aux->cliente->nome);
				else
					printf("Nodo não encontrado\n");
				break;

			}
			case 4:{
				system("cls");
				percorrerArvoreEmOrdemCrescente(raiz);
				system("pause");
				system("cls");

				break;
			}
			case 5:{
				system("cls");
				int numNodo = contarNodos(raiz, 0);
				printf("Nodos: %d\n", numNodo);
				system("pause");
				system("cls");
				break;
			}
			case 6:{
				system("cls");
				printf("Altura: %d\n", raiz->altura);
				system("pause");
				system("cls");
				break;
			}
			case 7:{
				system("cls");
				printf("Digite o numero que deseja inserir: ");
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
				if(estritamente_bin(raiz) == 1)
					printf("Estritamente Binaria\n");
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
