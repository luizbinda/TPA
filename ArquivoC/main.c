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
	
	
	dadosOrdeNome *listaNome = iniciarlistaNome();
	listaNome = preencherListaOrdenadaNome(lista, listaNome);
	double tempoInicialBuble = (double)clock();
	listaNome = ordenarDadosbubble_sort(listaNome);
	double tempoFinalBuble = (double)clock();
	double totaltempoBuble = (double) (tempoInicialBuble - tempoFinalBuble) / CLOCKS_PER_SEC;
	printf("Inicial buble: %.2lf\nFinal buble: %.2lf\nTotal buble: %.2lf\n\n",tempoInicialBuble, tempoFinalBuble, totaltempoBuble );
	imprimeListaNome(listaNome);

	dadosOrdeSaldo *listaSaldo = iniciarlistaSaldo();
	listaSaldo = preencherListaOrdenadaSaldo(lista, listaSaldo);
	clock_t tempoInicialQuick = clock();
	ordenarDadosquickSort(listaSaldo, tamListaSaldo(listaSaldo));
	clock_t tempoFinalQuick = clock();
	double totaltempoQuick = (double) (tempoInicialQuick - tempoFinalQuick) / CLOCKS_PER_SEC;
	printf("Inicial quick: %.2lf\nFinal quick: %.2lf\nTotal quick: %.2lf\n",tempoInicialQuick, tempoFinalQuick, totaltempoQuick );
	
	gerarAquivoNome(listaNome);
	gerarAquivoSaldo(listaSaldo);
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
