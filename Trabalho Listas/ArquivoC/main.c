#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "DadosBancoOriginal.h"
#include "DadosOrdenados.h"

int main(){

	dadosBancarios* lista = iniciarlista(); 
	lista = carregarArquivos(lista);
	dadosOrdenados* listaNome;
	dadosOrdenados* listaSaldo;
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
			listaNome = iniciarlistaOrdenado();
			listaNome = preencherListaOrdenada(lista, listaNome);
			double tempoInicialBuble = (double)clock();
			listaNome = ordenarDadosbubble_sort(listaNome);
			double tempoFinalBuble = (double)clock();
			double totaltempoBuble = (double) (tempoInicialBuble - tempoFinalBuble) / CLOCKS_PER_SEC;
			printf("Inicial buble: %.2lf\nFinal buble: %.2lf\nTotal buble: %.2lf\n\n",tempoInicialBuble, tempoFinalBuble, totaltempoBuble );
			gerarAquivoOrdenado(listaNome, "ArquivoNome.CSV");
			system("PAUSE");
			system("CLS");
			break;
		case 2:
			listaSaldo = iniciarlistaOrdenado();
			listaSaldo = preencherListaOrdenada(lista, listaSaldo);
			double tempoInicialQuick =(double) clock();
			ordenarDadosquickSort(listaSaldo, tamListaOrdenada(listaSaldo));
			double tempoFinalQuick =(double) clock();
			double totaltempoQuick = (double) (tempoInicialQuick - tempoFinalQuick) / CLOCKS_PER_SEC;
			printf("Inicial quick: %.2lf\nFinal quick: %.2lf\nTotal quick: %.2lf\n",tempoInicialQuick, tempoFinalQuick, totaltempoQuick );
			gerarAquivoOrdenado(listaSaldo, "ArquivoSaldo.CSV");
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
