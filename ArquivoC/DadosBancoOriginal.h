typedef struct dadosBancarios{
    int id;
    char nome[50];
    float saldo;
    struct dadosBancarios *prox;

} dadosBancarios;

dadosBancarios* iniciarlista(){
	dadosBancarios* dado = (dadosBancarios*)malloc(sizeof(dadosBancarios));
	
	dado->id = 0;
	dado->nome[0] = '\0';
	dado->saldo = 0;
	dado->prox = NULL;
	return dado;
}

void preencherDados(char* minhaString, dadosBancarios* lista) {
	int i;
	int j = 0;
	char aux[100];
	int cont = 0;
	int auxj = 0;
    for ( i = 0; i <= strlen(minhaString); i++)
    {
        if (minhaString[i] == '|' || i == strlen(minhaString)){
            for(j; j < i ; j++){
            	if(minhaString[j] == ',')
            		aux[auxj] = '.';
            
            	if(minhaString[j] != '|' && minhaString[j] != '.'){
            		aux[auxj] = minhaString[j];
            		auxj++;
            		aux[auxj] = '\0';
				}
			}
			if(cont == 0){
				lista->id = atoi(aux);
				//printf("id: %i\n",lista->id);
			}
				
			if(cont == 1){
				strcpy(lista->nome , aux);
			//	printf("nome: %s\n",lista->nome);
			}
				
			if(cont == 2){
				lista->saldo = atof(aux);
				//printf("saldo: %f\n" ,lista->saldo);
			}
			auxj = 0;
			cont++;			
        }
    }
}

dadosBancarios* carregarArquivos( dadosBancarios* lista){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");

    if (ponteiro_arquivo == NULL)
    	printf("ERRO! O arquivo não foi aberto!\n");
    
	else{    	
		char conteudo[100];
        printf("Carregando arquivos...\n");
        while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
            //printf("conteudo: %s", conteudo);        
		
        	dadosBancarios* novo = iniciarlista();
        	preencherDados(conteudo, novo);
        	
        	if(lista->nome[0] == '\0')
        		lista = novo;
        	else{
        		dadosBancarios* aux = lista;
        		
        		while(aux->prox != NULL){
        			aux = aux->prox;
				}
				aux->prox = novo;	
			}       
        }
	}
	return lista;
}

void imprimeLista(dadosBancarios* lista){
	dadosBancarios* atual = lista;

	printf("\n\n\n\t\t\t===|LISTA DADOS|===\n\n");
	while(atual != NULL){
	   printf("\tid: %i - nome: %s - saldo: %.2f\n",atual->id, atual->nome, atual->saldo );
	   atual = atual->prox;
	}
	printf("\n\n");
	system("PAUSE");
}

