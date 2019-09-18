typedef struct dadosBancarios{
    int id, excluido;
    char nome[50];
    float saldo;
    struct dadosBancarios *prox;

} dadosBancarios;

dadosBancarios* iniciarlista(){
	dadosBancarios* dado = (dadosBancarios*)malloc(sizeof(dadosBancarios));
	dado->excluido = 0;
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
    for (i = 0; i <= strlen(minhaString); i++)
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
			}
				
			if(cont == 1){
				strcpy(lista->nome , aux);
			}
				
			if(cont == 2){
				lista->saldo = atof(aux);
			}
			auxj = 0;
			cont++;			
        }
    }
}


