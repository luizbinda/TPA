#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DadosBancoOriginal.h"
#include "Arvore.h"

void menu(){

}


int main(){
   	raiz = iniciarArvore(); 
	int op = -1;
	int valor;
    while (op != 0){
        printf( "1 - Inserir novo elemento\n"
                "2 - Exluir elemento\n"
                "3 - Buscar elemento\n"
                "4 - Imprimir em ordem\n"
                "0 - Sair\n");
        scanf("%i",&op);
		switch (op){
			case 1:{
				printf("Digite o numero que deseja inserir: ");
				scanf("%i", &valor);
				raiz = inserirNodo(&raiz, valor);
				system("pause");
				system("cls");
				break;
			}
			case 2:{
				printf("Digite o numero que deseja inserir: ");
				scanf("%d", &valor);
				removerNodo(raiz, valor);
				break;	
			}
			case 3:{
				printf("Digite o numero que deseja inserir: ");
				scanf("%d", &valor);
				buscarValor(raiz, valor);
				break;

			}
			case 4:{
				percorrerArvoreEmOrdem(raiz);
				system("pause");
				system("cls");

				break;
			}
		}
	}
	return 0;
}
