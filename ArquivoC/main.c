#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DadosBancoOriginal.h"
#include "DadosOrdenadoNome.h"
#include "DadosOrdenadoSaldo.h"

int main(){

	dadosBancarios *lista = iniciarlista(); 
	lista = carregarArquivos(lista);
	dadosOrdeNome *listaNome;
	dadosOrdeSaldo *listaSaldo;
	int op = -1;
	system("CLS");
	while (op != 0)
	{
        printf("1 - Gerar ordenacao por nome\n"
                "2 - Gerar ordenacao por saldo\n"
                "0 - Sair\n");
        scanf("%i",&op);
		system("CLS");	
		
		switch (op)
		{
		case 1: 
			listaNome = iniciarlistaNome();
			listaNome = preencherListaOrdenadaNome(lista, listaNome);
			double tempoInicialBuble = (double)clock();
			listaNome = ordenarDadosbubble_sort(listaNome);
			double tempoFinalBuble = (double)clock();
			double totaltempoBuble = (double) (tempoInicialBuble - tempoFinalBuble) / CLOCKS_PER_SEC;
			printf("Inicial buble: %.2lf\nFinal buble: %.2lf\nTotal buble: %.2lf\n\n",tempoInicialBuble, tempoFinalBuble, totaltempoBuble );
			gerarAquivoNome(listaNome);
			system("PAUSE");
			system("CLS");
			break;
		case 2:
			listaSaldo = iniciarlistaSaldo();
			listaSaldo = preencherListaOrdenadaSaldo(lista, listaSaldo);
			clock_t tempoInicialQuick = clock();
			ordenarDadosquickSort(listaSaldo, tamListaSaldo(listaSaldo));
			clock_t tempoFinalQuick = clock();
			double totaltempoQuick = (double) (tempoInicialQuick - tempoFinalQuick) / CLOCKS_PER_SEC;
			printf("Inicial quick: %.2lf\nFinal quick: %.2lf\nTotal quick: %.2lf\n",tempoInicialQuick, tempoFinalQuick, totaltempoQuick );
			gerarAquivoSaldo(listaSaldo);
			system("PAUSE");
			system("CLS");
			break;
		case 0:
			printf("Finalizando...\n");
			system("PAUSE");
			system("CLS");
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
