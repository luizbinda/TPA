#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DadosBancoOriginal.h"
#include "HashingAberta.h"

int main(){
    hashingAberta* hash = inciarHash(500);
    hash = inciarVetor(hash);
    int op = -1;
    while (op != 0){
        printf("1 - Carregar Arquirvos para Hash\n"
                "2 - Inserir Dados na Hash\n"
                "3 - Listar Hahs \n"
                "0 - Sair\n");
        scanf("%i",&op);
		system("CLS");	
		switch (op){
		case 1: 
			hash  = carregarArquivos(hash, 1);
			system("PAUSE");
			system("CLS");
			break;
		case 2:
			hash  = carregarArquivos(hash, 0);
			system("PAUSE");
			system("CLS");
			break;
        case 3:
            listarHash(hash);
            system("PAUSE");
			system("CLS");
            break;
		case 0:
			printf("Finalizado...\n");
			break;
		default:
			printf("Opcao invalida!!\n");
			system("PAUSE");
			system("CLS");
			break;
   		 }
	}
	return 0;
}
