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
	system("PAUSE");
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

void gerarAquivoNome(dadosOrdeNome* lista){
	FILE *arquivo;
	char nomearq[50] = "ArquivoNome.CSV ";
	if (!(arquivo = fopen(nomearq,"w"))) /* Caso ocorra algum erro na abertura do arquivo..*/
	{                            /* o programa aborta automaticamente */
			printf("Erro! Impossivel abrir o arquivo!\n");
			exit(1);
	}
	/* Se nao houve erro, imprime no arquivo, fecha ...*/
	dadosOrdeNome* aux = lista;
	while (aux->prox != NULL)
	{
		fprintf(arquivo,"%i|%s|%0.f,00\n", aux->cliente->id, aux->cliente->nome, aux->cliente->saldo);
		aux = aux->prox;
	}
	fclose(arquivo);
}