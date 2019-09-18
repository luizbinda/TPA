typedef struct Hashing{
    
    struct dadosBancarios** vetor;
    int total;
    int tamanho_hash;
    
} Hashing;

int* colisao;

Hashing* inciarHash(int tam_hash){
    Hashing* hash = (Hashing*) malloc(sizeof(Hashing*));
    hash->tamanho_hash = tam_hash;
    hash->total = 0;
    hash->vetor = NULL;
    return hash;
}

int* inciarVetorColisao( int* vetor, int tamanho_hash){
    vetor = (int*) malloc(sizeof(int*) * tamanho_hash);
    int i;
    for (i = 0; i < tamanho_hash; i++){
        vetor[i] = 0;
    }
    return vetor;
}

Hashing* inciarVetor(Hashing* hash){
    hash->vetor = (dadosBancarios**) malloc(sizeof(dadosBancarios*) * hash->tamanho_hash);
    int i;
    for (i = 0; i < hash->tamanho_hash; i++){
        hash->vetor[i] = NULL;
    }
    return hash;
}

int calcularPosicaoDivisao( int tamanho_hash, int valor){
    return valor % tamanho_hash;
}

int calcularPosicaoDobra(int valor){
    char* s_valor = (char*) malloc(sizeof 10);
    itoa(valor, s_valor, 10);

    char *s_num1 = (char*) malloc(sizeof 3);
    s_num1[0] = s_valor[0];
    s_num1[1] = s_valor[1];
    s_num1[2] = '\0';

    char *s_num2 = (char*) malloc(sizeof 3);
    s_num2[0] = s_valor[3];
    s_num2[1] = s_valor[2];
    s_num2[2] = '\0';

    int i_num1 = atoi(s_num1);
    int i_num2 = atoi(s_num2);
    int i_soma = i_num1 + i_num2;
   
    if ( i_soma >= 100)
        i_soma -= 100;

    char* s_soma = (char*) malloc(sizeof 3);
    itoa(i_soma, s_soma, 10);

    s_valor[0] = '0';
    s_valor[1] = '0';
    s_valor[2] = s_soma[0];
    s_valor[3] = s_soma[1];

    valor = atoi(s_valor);

    free(s_num1);
    free(s_num2);
    free(s_soma);
    free(s_valor);
   
    return valor;
}

dadosBancarios* pesquisarHashAberta(Hashing* hash, int pesquisado){

    int pos = calcularPosicaoDivisao(hash->tamanho_hash, pesquisado);

    if (hash->vetor[pos] == NULL)
        return NULL;

    else if (hash->vetor[pos]->excluido != 1 && hash->vetor[pos]->id == pesquisado)
        return hash->vetor[pos];
    
    else if (hash->vetor[pos]->excluido == 1 && hash->vetor[pos]->id == pesquisado)
        return hash->vetor[pos];
    
    else{
        while (pos < hash->tamanho_hash - 1){
            pos++;
            if (hash->vetor[pos] == NULL)
                return NULL;

            else if (hash->vetor[pos]->excluido != 1 && hash->vetor[pos]->id == pesquisado)
                return hash->vetor[pos];

            else if (hash->vetor[pos]->excluido == 1 && hash->vetor[pos]->id == pesquisado)
                return hash->vetor[pos];
            
        }
        pos = 0;
        while (pos < hash->tamanho_hash - 1){
            pos++;
            if (hash->vetor[pos] == NULL)
                return NULL;
            
            else if (hash->vetor[pos]->excluido != 1 && hash->vetor[pos]->id == pesquisado)
                return hash->vetor[pos];

            else if (hash->vetor[pos]->excluido == 1 && hash->vetor[pos]->id == pesquisado)
                return hash->vetor[pos];
            
        }
    }
}

dadosBancarios* pesquisarHashFechada(Hashing* hash, int pesquisado){
    int pos = calcularPosicaoDivisao(hash->tamanho_hash, pesquisado);
    if (hash->vetor[pos] == NULL)
        return NULL;
    else if (hash->vetor[pos]->excluido == 1)
        return hash->vetor[pos];
    else{
        dadosBancarios* aux = hash->vetor[pos];
        while (aux != NULL ){
            if (aux->id == pesquisado)
                return aux;           
            aux = aux->prox;
        }
    }
    return NULL;
}

Hashing* preencherHashAberta(Hashing* hash, dadosBancarios* dados, int tipo_hash){
    int pos;

    if (tipo_hash == 1)  
        pos = calcularPosicaoDivisao(hash->tamanho_hash, dados->id);
    if (tipo_hash == 2){
        pos = dados->id;
        
        while ( pos > hash->tamanho_hash - 1)
            pos = calcularPosicaoDobra(pos);    

    }
        
    
    if (hash->vetor[pos] == NULL)
        hash->vetor[pos] = dados;
    else if (hash->vetor[pos]->excluido == 1)
        hash->vetor[pos] = dados;
    else{
        colisao[pos]++;
        int inserido = 0;
        while (pos < hash->tamanho_hash - 1){
            pos++;
            if (hash->vetor[pos] == NULL){
                hash->vetor[pos] = dados;
                inserido = 1;
                break;
            }
            else if (hash->vetor[pos]->excluido == 1){
                hash->vetor[pos] = dados;
                inserido = 1;
                break;
            }
        }
        if (inserido == 0){
            pos = 0;
            while (pos < hash->tamanho_hash - 1){
                pos++;
                if (hash->vetor[pos] == NULL){
                hash->vetor[pos] = dados;
                break;
                }
                else if (hash->vetor[pos]->excluido == 1){
                    hash->vetor[pos] = dados;
                    break;
                }
            }
        }
    }
    return hash;
}

Hashing* preencherHashFechada(Hashing* hash, dadosBancarios* dados){
    
    int pos = calcularPosicaoDivisao(hash->tamanho_hash, dados->id);
    if (hash->vetor[pos] == NULL)
        hash->vetor[pos] = dados;
    else if (hash->vetor[pos]->excluido == 1){
        dados->prox = hash->vetor[pos]->prox;
        hash->vetor[pos] = dados;
    }        
    else{
        colisao[pos]++;
        dadosBancarios* aux = hash->vetor[pos];
        while (aux->prox != NULL ){
            if (aux->prox->excluido == 1)
                break;            
            aux = aux->prox;
        }
        if (aux->prox != NULL)
            dados->prox = aux->prox->prox;
                           
        aux->prox = dados;
   
    }
    return hash;
}

Hashing* expandirHash(Hashing* hash, int tipo_hash){

    Hashing* novaHash = inciarHash(hash->tamanho_hash * 2);
    novaHash = inciarVetor(novaHash);
    int i;
    for (i = 0; i < hash->tamanho_hash; i++){
        if (hash->vetor[i] != NULL ) {
            preencherHashAberta(novaHash, hash->vetor[i], tipo_hash);
            novaHash->total++;
        }      
    }
    free(hash);   
    return novaHash;
}

Hashing* carregarArquivos( Hashing* hash, int op, int tipo_hash){
    
    if(op == 1){
        FILE* ponteiro_arquivo;
        ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");

        if (ponteiro_arquivo == NULL)
            printf("ERRO! O arquivo não foi aberto!\n");
        
        else{    	
            char conteudo[100];
            printf("Carregando arquivos...\n");
            while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
            
                dadosBancarios* novo = iniciarlista();
                preencherDados(conteudo, novo);

                if (tipo_hash == 1 || tipo_hash == 2){
                    preencherHashAberta(hash, novo, tipo_hash);  
                    hash->total++;  
                    if (hash->total > hash->tamanho_hash * 0.7)
                        hash = expandirHash(hash, tipo_hash);  
                }
                else if (tipo_hash == 3){
                    hash = preencherHashFechada(hash, novo);
                    hash->total++;
                }
            }
        }
    }
    else {  
        dadosBancarios* novo = iniciarlista();

        printf("Insira o ID da conta: ");
        scanf("%i", &novo->id);

        dadosBancarios* aux;
         if (tipo_hash == 1 || tipo_hash == 2)      
            aux = pesquisarHashAberta(hash, novo->id);
        
        if (tipo_hash == 3)       
            aux = pesquisarHashFechada(hash, novo->id);

        if (aux == NULL || aux->excluido == 1){
            printf("Insira o Nome da conta: ");
            scanf("%s", &novo->nome);

            printf("Insira o saldo da conta: ");
            scanf("%f", &novo->saldo);

            if (tipo_hash == 1){
                preencherHashAberta(hash, novo, tipo_hash);  
                hash->total++;  
                if (hash->total > hash->tamanho_hash * 0.7)
                    hash = expandirHash(hash, tipo_hash);  
            }
            else if (tipo_hash == 3){
                hash = preencherHashFechada(hash, novo);
                hash->total++;
            }		
        }
        else
            printf("Ja existe um cliente com esse id!\nTente novamente...\n");
                    
    }
    return hash;
}

void listarHashAberta(Hashing* hash){
    int i;
    for (i = 0; i < hash->tamanho_hash; i++){

        if(hash->vetor[i] != NULL && hash->vetor[i]->excluido == 0)
            printf("\tid: %i - nome: %s - saldo: %.2f\n",hash->vetor[i]->id, hash->vetor[i]->nome, hash->vetor[i]->saldo);
        
    }
}

void listarHashFechada(Hashing* hash){
    int i;
    dadosBancarios* aux; 
    for (i = 0; i < hash->tamanho_hash; i++){
        aux = hash->vetor[i];
        while (aux != NULL) {
           if(aux->excluido == 0)
                printf("\tid: %i - nome: %s - saldo: %.2f\n",aux->id, aux->nome, aux->saldo);
            
            aux = aux->prox;
        }   
    }
}

Hashing* excluirHash(Hashing* hash, int id_exluido, int tipo_hash){
    dadosBancarios* aux;

    if (tipo_hash == 1)    
        aux = pesquisarHashAberta(hash, id_exluido);
    if (tipo_hash == 3)
        aux = pesquisarHashAberta(hash, id_exluido);
    
    if (aux == NULL)
        printf("O id que deseja excluir nao existe...\n");	
                    
    else if ( aux->excluido == 1)
        printf("O id pesquisado ja foi excluido!\n");

    else{
        aux->excluido = 1;
        hash->total--;
    }

    return hash;
}

int listarColisao(Hashing* hash){
    int i;
    int cont = 0;
    for (i = 0; i < hash->tamanho_hash; i++){
        if(colisao[i] != 0 ){
            printf("\tpos: %i - qtde: %i\n", i, colisao[i]);
            cont++;
        }
    }
    return cont;
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

void gerarAquivoHash(Hashing* hash, char nomearq[50]){
	FILE* arquivo;
	
	if (!(arquivo = fopen(nomearq,"w"))){     
		printf("Erro! Impossivel abrir o arquivo!\n");
		exit(1);
	}

    fprintf(arquivo,"Total de Elementos: %i;Total de Colisoes: %i;\n", hash->total, listarColisao(hash));
    fprintf(arquivo,"ID;NOME;SALDO;COLISOES\n", hash->total, listarColisao(hash));
    int i;
    dadosBancarios* aux;
	for(i = 0; i < hash->tamanho_hash; i++){
        aux = hash->vetor[i];
        while (aux != NULL){
            char char_saldo[50];
            sprintf(char_saldo, "%.0f", aux->saldo);
            strcpy(char_saldo, transformaSaldo(char_saldo));

            fprintf(arquivo,"%i;%s;%s,00;%i\n", aux->id, aux->nome, char_saldo, colisao[i]);
            aux = aux->prox;
        }
               					
	}
    
	fclose(arquivo);
}
