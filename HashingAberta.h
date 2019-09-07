typedef struct hashingAberta{
    
    struct dadosBancarios** vetor;
    int total;
    int tamanho_hash;

} hashingAberta;

hashingAberta* inciarHash(int tam_hash){
    hashingAberta* hash = (hashingAberta*) malloc(sizeof(hashingAberta*));
    hash->tamanho_hash = tam_hash;
    hash->total = 0;
    hash->vetor = NULL;
    return hash;
}

hashingAberta* inciarVetor(hashingAberta* hash){
    hash->vetor = (dadosBancarios**) malloc(sizeof(dadosBancarios*) * hash->tamanho_hash);
    int i;
    for (i = 0; i < hash->tamanho_hash; i++){
        hash->vetor[i] = NULL;
    }
    return hash;
}

int calcularPosicao( int tamanho_hash, int valor){
    return valor%tamanho_hash;
}

hashingAberta* preencherHash(hashingAberta* hash, dadosBancarios* dados){
    int pos = calcularPosicao(hash->tamanho_hash, dados->id);
    if (hash->vetor[pos] == NULL)
        hash->vetor[pos] = dados;
    else if (hash->vetor[pos]->excluido == 1)
        hash->vetor[pos] = dados;
    else{
        int inserido = 0;
        while (pos < hash->tamanho_hash){
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
            while (pos < hash->tamanho_hash){
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
        }
    }
    return hash;
}

hashingAberta* carregarArquivos( hashingAberta* hash, int op){
    
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
                preencherHash(hash, novo);		
            }
        }
    }
    else {  
        dadosBancarios* novo = iniciarlista();
        preencherDadosManual(novo);
        preencherHash(hash, novo);		
    }
    return hash;
}

void listarHash(hashingAberta* hash){
    int i;
    for (i = 0; i < hash->tamanho_hash; i++){
        if(hash->vetor[i] != NULL){
            printf("\tid: %i - nome: %s - saldo: %.2f\n",hash->vetor[i]->id, hash->vetor[i]->nome, hash->vetor[i]->saldo );
        }
    }
}


