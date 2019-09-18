#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DadosBancoOriginal.h"
#include "Hashing.h"

void menu(Hashing* hash, int tipo_hash){
	int op = -1;
    while (op != 0){
        printf( "1 - Inserir Dados na Hash\n"
                "2 - Pesquisar Hash\n"
                "3 - Excluir Hash\n"
                "0 - Sair\n");
        scanf("%i",&op);
		switch (op){
			case 1:
				hash = carregarArquivos(hash, 0, tipo_hash);
				system("PAUSE");
				system("CLS");
				break;
			case 2:{
				int id_pesquisado;
				printf("Insira o id que deseja pesquisar: ");
				scanf("%i", &id_pesquisado);
				system("CLS");
				dadosBancarios* aux;
				if (tipo_hash == 1)						
					aux = pesquisarHashAberta(hash, id_pesquisado);
				if (tipo_hash == 3)	
					aux = pesquisarHashFechada(hash, id_pesquisado);
				
				if (aux == NULL)
					printf("O id pesquisado nao existe...\n");	
				
				else if ( aux->excluido == 1)
					printf("O id pesquisado foi excluido!\n");
				
				else
					printf("\tid: %i - nome: %s - saldo: %.2f\n",aux->id, aux->nome, aux->saldo );

				system("PAUSE");
				system("CLS");
				break;	
			}
			case 3:{
				int id_excluido;
				printf("Insira o id que deseja pesquisar: ");
				scanf("%i", &id_excluido);
				system("CLS");
				hash = excluirHash(hash, id_excluido, tipo_hash);
				system("PAUSE");
				system("CLS");
				break;

			}
			case 7:
				if (tipo_hash == 1)	
					listarHashAberta(hash);
				
				if (tipo_hash == 3)		
					listarHashFechada(hash);				

				printf("total colisao: %i\n", listarColisao(hash));
				printf("tamanho hash: %i\n", hash->tamanho_hash);
				printf("total hash: %i\n", hash->total);
				system("PAUSE");
				system("CLS");
				break;
			
			case 0:
				if (tipo_hash == 1)
					gerarAquivoHash(hash, "HashingAberta.csv");
				if (tipo_hash == 2)
					gerarAquivoHash(hash, "HashingAbertaDobra.csv");
				if (tipo_hash == 3)
					gerarAquivoHash(hash, "HashingFechada.csv");
				
				printf("Finalizado...\n");
				break;	
			default:
				printf("Opcao invalida!!\n");
				system("PAUSE");
				system("CLS");
				break;
		}
	}
}


int main(){
	
	int tipo_hash = -1;
    while (tipo_hash != 0){
		printf( "1 - Hash Aberta por divisao\n"
				"2 - Hash Aberta por Dobra\n"
				"3 - Hash Fechada\n"
				"0 - Sair\n");
		scanf("%i",&tipo_hash);
		system("CLS");

		if (tipo_hash < 1 || tipo_hash > 3)
			printf("Opcao invalida!\n");
		else{
			Hashing* hash = inciarHash(500);
			hash = inciarVetor(hash);
			colisao = inciarVetorColisao(colisao, hash->tamanho_hash);
			hash = carregarArquivos(hash, 1, tipo_hash);
			system("CLS");
			menu(hash, tipo_hash);
			system("CLS");
		}				
		system("CLS");	
		
	}
	return 0;
}
