#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dadosBancariosOriginal{
    int id;
    char nome[50];
    float saldo;
    struct dadosBancariosOriginal *prox;

} dadosBancariosOriginal;


typedef struct dadosOrdenadosNome{
	struct dadosBancariosOriginal *cliente;
	struct dadosBancariosOriginal *prox;
}dadosOrdenadosNome;


dadosBancariosOriginal *iniciarlista(){
	dadosBancariosOriginal *dado = (dadosBancariosOriginal*)malloc(sizeof(dadosBancariosOriginal));
	
	dado->id = 0;
	dado->nome[0] = '\0';
	dado->saldo = 0;
	dado->prox = NULL;
	return dado;
}

void preencherDados(char *minhaString, dadosBancariosOriginal *lista) {
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

dadosBancariosOriginal *carregarArquivos( dadosBancariosOriginal *lista){
    FILE *ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");

    if (ponteiro_arquivo == NULL)
    	printf("ERRO! O arquivo não foi aberto!\n");
    
	else{    	
        printf("O arquivo foi aberto com sucesso!\n");
        while(!feof(ponteiro_arquivo)){
            
			char conteudo[100];
            fgets(conteudo, 100, ponteiro_arquivo);
            printf("conteudo: %s", conteudo);        
		
        	dadosBancariosOriginal *novo = iniciarlista();
        	preencherDados(conteudo, novo);
        	
        	if(lista->nome[0] == '\0')
        		lista = novo;
        	else{
        		dadosBancariosOriginal *aux = lista;
        		
        		while(aux->prox != NULL){
        			aux = aux->prox;
				}
				aux->prox = novo;	
			}      
        }
	}
	return lista;
}

void imprimeLista(dadosBancariosOriginal *lista){
	dadosBancariosOriginal *atual = lista;

	printf("\n\n\n\t\t\t===|LISTA DADOS|===\n\n");
	while(atual != NULL){
	   printf("\tid: %i - nome: %s - saldo: %f\n",atual->id, atual->nome, atual->saldo );
	   atual = atual->prox;
	}
	printf("\n\n");
	system("PAUSE");
}

dadosOrdenadosNome *iniciarlistaNome(){
	dadosOrdenadosNome *dado = (dadosOrdenadosNome*)malloc(sizeof(dadosOrdenadosNome));
	
	dado->cliente = NULL;
	dado->prox = NULL;
	return dado;
}

dadosOrdenadosNome *preencherListaOrdenadaNome(dadosBancariosOriginal *listaOriginal){
	dadosBancariosOriginal *aux = listaOriginal;
	dadosOrdenadosNome *listaNome = iniciarlistaNome();
	
	listaNome->cliente = listaOriginal;
	
	while(aux->prox != NULL){
		listaNome->prox = aux;
		aux = aux->prox;		
	}
		
	
}

int main(){
	
	dadosBancariosOriginal *lista = iniciarlista(); 
	lista = carregarArquivos(lista);
	imprimeLista(lista);
	return 0;
}
	
