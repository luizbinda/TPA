typedef struct dadosOrdeNome{
	dadosBancarios *cliente;
	struct dadosOrdeNome *prox;
}dadosOrdeNome;

dadosOrdeNome *iniciarlistaNome(){
	dadosOrdeNome *dado = (dadosOrdeNome*)malloc(sizeof(dadosOrdeNome));
	
	dado->cliente = NULL;
	dado->prox = NULL;
	return dado;
}

dadosOrdeNome *preencherListaOrdenadaNome(dadosBancarios *listaOriginal, dadosOrdeNome *listaNome){
	
	dadosBancarios *auxOriginal = listaOriginal;
	listaNome->cliente = auxOriginal;
	dadosOrdeNome *auxNome = listaNome;
		
	
	while(auxOriginal->prox != NULL){
		auxOriginal = auxOriginal->prox;
		auxNome->prox = iniciarlistaNome();
		auxNome = auxNome->prox;
		auxNome->cliente = auxOriginal;		
	}
	
	return listaNome;	
	
}

void imprimeListaNome(dadosOrdeNome *lista){
	dadosOrdeNome *atual = lista;

	printf("\n\n\n\t\t\t===|LISTA DADOS NOME|===\n\n");
	while(atual != NULL){
	   printf("\tid: %i - nome: %s - saldo: %.2f\n",atual->cliente->id, atual->cliente->nome, atual->cliente->saldo );
	   atual = atual->prox;
	}
	printf("\n\n");
	
}

int tamListaNome(dadosOrdeNome *lista){
	dadosOrdeNome *atual = lista;
	int cont =0;

	while(atual != NULL){
		cont++;
	   atual = atual->prox;
	}
	return cont;
}
/* 
	COMPLEXIBILIDADE DA FUNÇÃO tamListaNome
	45 => 2Trec + Tarm
    46=> Trec + Tarm
    48 => 2Trec + T>
    49 => 2Trec + Tarm
    50 => 2Trec + tarm
    52 => Trec + Tret
    RESULTADO => 8Trec + 4Tarm + 1Tret + (2Trec + T>)*n
*/
dadosOrdeNome* ptrElement ( dadosOrdeNome* first, long int pos ){
         
       if( pos > tamListaNome( first ) - 1 ) {
           return NULL;
       }
       
       long int count = 0;
       dadosOrdeNome *aux = first;
       
       while ( count < pos ) {
             aux = aux->prox;
             count++;
       }
       
       return aux;
}
/*
    COMPLEXIBILIDADE DA FUNÇÃO ptrElement
	66 => 3Trec + T- + Tret + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n)
    67 => Tret + Trec
    70 => Tarm + Trec
    71 => Tarm + Trec
    73 => (2Trec + T<)*n
    74 => 2Trec + Tarm
    75 2Trec + Tarm
    78 => Trec + Tret
    RESULTADO PIOR CASO => 12Trec + 4Tarm + 3Tret + T- + (2Trec + T<)*n + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n)
    RESULTADO MELHOR CASO => 3Trec + T- + 2Tret + Tchamada(8Trec + 4Tarm + 1Tret + (2Trec + T>)*n)
 */

dadosOrdeNome *ordenarDadosbubble_sort(dadosOrdeNome* first){ 

	int i, j;
     
     for( i = tamListaNome( first ) - 1; i >= 0; i-- ) {
          for( j = 1; j <= i; j++ ) {
               if( strcmp( ptrElement( first, j - 1 )->cliente->nome, ptrElement( first, j )->cliente->nome) > 0 ) {
                    dadosBancarios *aux = ptrElement( first, j - 1 )->cliente;
                    ptrElement( first, j - 1 )->cliente = ptrElement( first, j )->cliente;
                    ptrElement( first, j )->cliente = aux;
               }
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

char* transformaSaldoNome( char* char_saldo){
	
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

void gerarAquivoNome(dadosOrdeNome* lista){
	FILE *arquivo;
	char nomearq[50] = "ArquivoNome.CSV ";

	if (!(arquivo = fopen(nomearq,"w")))
	{     
		printf("Erro! Impossivel abrir o arquivo!\n");
		exit(1);
	}
	dadosOrdeNome* aux = lista;
	while (aux != NULL)
	{			
		char char_saldo[50];
		sprintf(char_saldo, "%.0f", aux->cliente->saldo);
		strcpy(char_saldo, transformaSaldoNome(char_saldo));

		fprintf(arquivo,"%i|%s|%s,00\n", aux->cliente->id, aux->cliente->nome, char_saldo);
		aux = aux->prox;
	}
	fclose(arquivo);
}