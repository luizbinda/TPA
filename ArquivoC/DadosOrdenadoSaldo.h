typedef struct dadosOrdeSaldo{
	dadosBancarios *cliente;
	struct dadosOrdeSaldo *prox;
}dadosOrdeSaldo;

dadosOrdeSaldo *iniciarlistaSaldo(){
	dadosOrdeSaldo *dado = (dadosOrdeSaldo*)malloc(sizeof(dadosOrdeSaldo));
	
	dado->cliente = NULL;
	dado->prox = NULL;
	return dado;
}

dadosOrdeSaldo *preencherListaOrdenadaSaldo(dadosBancarios *listaOriginal, dadosOrdeSaldo *listaSaldo){
	
	dadosBancarios *auxOriginal = listaOriginal;
	listaSaldo->cliente = auxOriginal;
	dadosOrdeSaldo *auxSaldo = listaSaldo;
		
	
	while(auxOriginal->prox != NULL){
		auxOriginal = auxOriginal->prox;
		auxSaldo->prox = iniciarlistaSaldo();
		auxSaldo = auxSaldo->prox;
		auxSaldo->cliente = auxOriginal;		
	}
	
	return listaSaldo;	
	
}

void imprimeListaSaldo(dadosOrdeSaldo *lista){
	dadosOrdeSaldo *atual = lista;

	printf("\n\n\n\t\t\t===|LISTA DADOS SALDO|===\n\n");
	while(atual != NULL){
	   printf("\tid: %i - nome: %s - saldo: %.2f\n",atual->cliente->id, atual->cliente->nome, atual->cliente->saldo );
	   atual = atual->prox;
	}
	printf("\n\n");
	system("PAUSE");
}

int tamListaSaldo(dadosOrdeSaldo *lista){
	dadosOrdeSaldo *atual = lista;
	int cont =0;

	while(atual != NULL){
		cont++;
	   atual = atual->prox;
	}
	return cont;
}

dadosOrdeSaldo* ptrElementSaldo ( dadosOrdeSaldo* first, long int pos ){
    
       long int count = 0;
       
       while( count < pos ) {
              first = first->prox;
              count++;
       }
       
       return first;
}

dadosOrdeSaldo* ordenarDadosquickSort( dadosOrdeSaldo *first, long int tam ) {
     
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

void gerarAquivoSaldo(dadosOrdeSaldo* lista){
	FILE *arquivo;
	char nomearq[50] = "ArquivoSaldo.CSV ";

	if (!(arquivo = fopen(nomearq,"w")))
	{     
		printf("Erro! Impossivel abrir o arquivo!\n");
		exit(1);
	}
	dadosOrdeSaldo* aux = lista;
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

