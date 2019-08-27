typedef struct dadosOrdenados{
	dadosBancarios *cliente;
	struct dadosOrdenados *prox;
}dadosOrdenados;

dadosOrdenados* iniciarlistaOrdenado(){
	dadosOrdenados* dado = (dadosOrdenados*)malloc(sizeof(dadosOrdenados));
	dado->cliente = NULL;
	dado->prox = NULL;
	return dado;
}

dadosOrdenados *preencherListaOrdenada(dadosBancarios* listaOriginal, dadosOrdenados* listaNome){
	
	dadosBancarios* auxOriginal = listaOriginal;
	listaNome->cliente = auxOriginal;
	dadosOrdenados* auxNome = listaNome;
		
	while(auxOriginal->prox != NULL){
		auxOriginal = auxOriginal->prox;
		auxNome->prox = iniciarlistaOrdenado();
		auxNome = auxNome->prox;
		auxNome->cliente = auxOriginal;		
	}
	
	return listaNome;	
	
}

void imprimeListaNome(dadosOrdenados* lista){
	dadosOrdenados* atual = lista;

	printf("\n\n\n\t\t\t===|LISTA DADOS NOME|===\n\n");
	while(atual != NULL){
	   printf("\tid: %i - nome: %s - saldo: %.2f\n",atual->cliente->id, atual->cliente->nome, atual->cliente->saldo );
	   atual = atual->prox;
	}
	printf("\n\n");
	
}

int tamListaOrdenada(dadosOrdenados* lista){
	dadosOrdenados* atual = lista;
	int cont =0;

	while(atual != NULL){
		cont++;
	   	atual = atual->prox;
	}
	return cont;
}
/* 
	COMPLEXIBILIDADE DA FUNÇÃO tamListaOrdenada
	45 => 2Trec + Tarm
    46=> Trec + Tarm
    48 => 2Trec + T>
    49 => 2Trec + Tarm
    50 => 2Trec + tarm
    52 => Trec + Tret
    RESULTADO => 8Trec + 4Tarm + 1Tret + (2Trec + T>)*n
*/

dadosOrdenados *ordenarDadosbubble_sort(dadosOrdenados* first){ 

	int i, j;
	int tamFirst = tamListaOrdenada(first);
	dadosOrdenados* aux1;
	dadosOrdenados* aux2;
     
	for(i = 1; i < tamFirst; ++i ) {
		aux1 = first;
		aux2 = aux1->prox;

        for(j = 0; j < tamFirst - 1; ++j) {
            if(strcmp(aux1->cliente->nome, aux2->cliente->nome) > 0 ) {
                dadosBancarios* auxTroca = aux1->cliente;
                aux1->cliente = aux2->cliente;
                aux2->cliente = auxTroca;
            }
			aux1 = aux2;
			aux2 = aux2->prox;
        }
    }
    return first;  
}
/*
    COMPLEXIBILIDADE DA FUNÇÃO ordenarDadosbubble_sort
    96 => 2Tarm
    98.1 => 3Trec + T- + 2Tarm+ Tchamada(10Trec + 4Tarm + 1Tret)
    98.2 => (2Trec + T>) * (n+1)
    98.3 => (2Trec + Tarm)*n
    99.1 => 2Trec +Tarm
    99.2 => (2Trec + T<) * n
    99.3 => (2Trec +Tarm) * (n-1)
    100 => 8Trec + T> + 3Tret + 3Tarm + 2Tchamada(12Trec + 4Tarm + 3Tret + T- + (2Trec + T<)*n + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n)) + Tchamada(strcmp?)
    101 => 5Trec + 2Tarm  + T- + Tret + Tchamada(12Trec + 4Tarm + 3Tret + T- + (2Trec + T<)*n + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n))
    102 => 7Trec + 3Tarm + 2Tret + 2Tchamada(12Trec + 4Tarm + 3Tret + T- + (2Trec + T<)*n + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n))
    103 => 4Trec + 2Tarm + 1Tret + Tchamada(12Trec + 4Tarm + 3Tret + T- + (2Trec + T<)*n + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n))
    108 Trec + Tret  
    RESULTADO PIOR CASO=> 14Tarm + 29Trec + 2T- + 8Tret + Tchamada(10Trec + 4Tarm + 1Tret) + 2T> + (2Trec + T>) * n + (2Trec + Tarm)*n + (2Trec + T<) * n + (2Trec +Tarm) * n + 6Tchamada(12Trec + 4Tarm + 3Tret + T- + (2Trec + T<)*n + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n)) 
	RESULTADO MELHOR CASO=> 7Tarm + 13Trec + 1T- + 4Tret + Tchamada(10Trec + 4Tarm + 1Tret) + 2T> + (2Trec + T>) * n + (2Trec + Tarm)*n + (2Trec + T<) * n + (2Trec +Tarm) * n + 2Tchamada(3Trec + T- + 2Tret + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n)) 
 */

dadosOrdenados* ptrElementSaldo ( dadosOrdenados* first, long int pos ){
    
	long int count = 0;
	
	while( count < pos ) {
			first = first->prox;
			count++;
	}
	return first;
}
/*
    COMPLEXIBILIDADE DA FUNÇÃO ptrElement
	66 => Tret + Trec
    68 => (2Trec + T<)*n
    69 => Tarm + Trec
    70 => 2Trec + Tarm + T+
    73 => Trec + Tret
    RESULTADO => 5Trec + 2Tarm + 1Tret + T< + T+ + (2Trec + T<)*n
 */
dadosOrdenados* ordenarDadosquickSort( dadosOrdenados* first, long int tam ) {
     
	long int posesq = 0;
	long int posdir = tam - 1;
	float pivo = ptrElementSaldo( first, tam / 2 )->cliente->saldo;
	
	do{
		while( ptrElementSaldo( first, posesq )->cliente->saldo < pivo ) posesq++;
		while( ptrElementSaldo( first, posdir )->cliente->saldo > pivo ) posdir--;
	
		if( posdir >= posesq ) {
			dadosBancarios* aux = ptrElementSaldo( first, posesq )->cliente;
			ptrElementSaldo( first, posesq )->cliente  = ptrElementSaldo( first, posdir )->cliente;
			ptrElementSaldo( first, posdir )->cliente = aux;
			posdir--;
			posesq++;
		}
	}while( posdir >= posesq );
	
	if( posdir ) {
		ordenarDadosquickSort( first, posdir + 1 );
	}
	
	if( posesq < tam - 1 ) {
		ordenarDadosquickSort( ptrElementSaldo( first, posesq ), tam - posesq );
	}
}
/*
    COMPLEXIBILIDADE DA FUNÇÃO ptrElement
	
    RESULTADO => 5Trec + 2Tarm + 1Tret + T< + T+ + (2Trec + T<)*n

 */


char* transformaSaldo( char* char_saldo){
	
	char saldo[50];	
	int i, j, k;
	int cont = 0;
	j = 0;
	for ( i = strlen(char_saldo) ; i > 0; i--){
		if (j > 2){
			cont++;
			j = 0;
		}	
		j++;	
	}
	k =  strlen(char_saldo) + cont - 1;
	j = 0;
	for ( i =  strlen(char_saldo) - 1 ; i >= 0; i--){
		if ( j > 2){
			saldo[k] = '.';
			k--;
			j = 0;
		}
		saldo[k] = char_saldo[i];
		k--;
		j++;
	}
	saldo[cont + strlen(char_saldo)] = '\0';
	strcpy(char_saldo, saldo);
	return char_saldo;
	
}

void gerarAquivoOrdenado(dadosOrdenados* lista, char nomearq[50]){
	FILE* arquivo;
	
	if (!(arquivo = fopen(nomearq,"w")))
	{     
		printf("Erro! Impossivel abrir o arquivo!\n");
		exit(1);
	}
	dadosOrdenados* aux = lista;
	while (aux != NULL)
	{			
		char char_saldo[50];
		sprintf(char_saldo, "%.0f", aux->cliente->saldo);
		strcpy(char_saldo, transformaSaldo(char_saldo));

		fprintf(arquivo,"%i|%s|%s,00\n", aux->cliente->id, aux->cliente->nome, char_saldo);
		aux = aux->prox;
	}
	fclose(arquivo);
}