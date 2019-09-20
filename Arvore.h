typedef struct Nodo {
    dadosBancarios* cliente;
    struct Nodo* pai;
    struct Nodo* esquerda;
    struct Nodo* direita;
    int nivel, altura;
    // Hashing parametros
    int exluido_hash;
    struct Nodo* prox;
}Nodo;

typedef struct Hashing {
    Nodo** vetor;
    int total;
}Hashing;

Nodo* raiz;
Hashing* hash;


Nodo* criarNodo(dadosBancarios* cliente);
Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente);
Nodo* removerNodo(Nodo* nodo, int valor_exluido);
void percorrerArvoreEmOrdemCrescente(Nodo* nodo);
void percorrerArvoreEmOrdemDecrescente(Nodo* nodo);
Nodo* buscarValor(Nodo* nodo, int valor_procurado);
Nodo* carregarArquivos(Nodo* nodo, Hashing* hash);
int calcularAltura(Nodo* nodo);
void calcularNivel(Nodo* nodo, int valor_procurado, int nivel_atual);
int calcularTotalNodos(Nodo* nodo);
int estritamenteBinaria(Nodo* nodo);
Hashing* iniciarHash();
Hashing* iniciarVetorHash(Hashing* hash, int tamanho_hash);
int calcularHashPos(Hashing* raiz, int valor, int total);
int calcularHashPosDivisao(int valor, int total);
Hashing* inserirHash(Hashing* hash, Nodo* dados, int pos);
Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos);

Nodo* criarNodo(dadosBancarios* cliente){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->cliente = cliente;
    novo->pai = NULL;
	novo->direita = NULL;
	novo->esquerda = NULL;
    novo->nivel = 0;
    novo->altura = 0;
    // Hashing parametros
    novo->prox = NULL;
    novo->exluido_hash = 0;
	return novo;
}

Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente){
    if(nodo == NULL)
        nodo = criarNodo(cliente);
    else if ( cliente->id < nodo->cliente->id){
        nodo->esquerda = inserirNodo(nodo->esquerda, cliente);
        nodo->esquerda->pai = nodo;
    } 
    else {
        nodo->direita = inserirNodo(nodo->direita, cliente);
        nodo->direita->pai = nodo;
    }
    
    return nodo;
}

Nodo* removerNodo(Nodo* nodo, int valor_exluido){
    if(nodo == NULL)
        return NULL;
    else if (nodo->cliente->id > valor_exluido) 
        nodo->esquerda = removerNodo(nodo->esquerda, valor_exluido);
    else if( nodo->cliente->id < valor_exluido)
        nodo->direita = removerNodo(nodo->direita, valor_exluido);
    else {
        if(nodo->direita == NULL && nodo->esquerda == NULL){
            //free(nodo);
            nodo = NULL;
        }            
        else if(nodo->esquerda == NULL){
            Nodo* temporario = nodo;
            nodo->direita->pai = nodo->pai;
            nodo = nodo->direita;
            //free(temporario);
        }
        else if(nodo->direita == NULL){
            Nodo* temporario = nodo;
            nodo->esquerda->pai = nodo->pai;
            nodo = nodo->esquerda;
            //free(temporario);
        }
        else{
            Nodo* temporario = nodo->esquerda;
            while (temporario->direita != NULL )
                temporario = temporario->direita;
            //Trocando os dados entre os nodos ...
            nodo->cliente = temporario->cliente;
            temporario->cliente->id = valor_exluido;            
            
            nodo->esquerda = removerNodo(nodo->esquerda, valor_exluido);
        }
    }
}

void percorrerArvoreEmOrdemCrescente(Nodo* nodo){
    if(nodo != NULL){
        percorrerArvoreEmOrdemCrescente(nodo->esquerda);
        printf("\t-%d-\n", nodo->cliente->id);
        percorrerArvoreEmOrdemCrescente(nodo->direita);    
    }
}

void percorrerArvoreEmOrdemDecrescente(Nodo* nodo){
    if(nodo != NULL){
        percorrerArvoreEmOrdemDecrescente(nodo->direita);
        printf("\t-%d-\n", nodo->cliente->id);
        percorrerArvoreEmOrdemDecrescente(nodo->esquerda);    
    }
}

Nodo* buscarValor(Nodo* nodo, int valor_procurado){
    if(nodo == NULL)
        return NULL;
    else if(nodo->cliente->id == valor_procurado)
        return nodo;
    else if(nodo->cliente->id > valor_procurado)
        buscarValor(nodo->esquerda, valor_procurado);
    else
        buscarValor(nodo->direita, valor_procurado);
}

Nodo* carregarArquivos(Nodo* raiz, Hashing* hash){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");

    char conteudo[100];
    while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
        dadosBancarios* novo = iniciarlista();
        preencherDados(conteudo, novo);   
        raiz = inserirNodo(raiz, novo);
        hash = inserirHash(hash, buscarValor(raiz, novo->id), calcularHashPosDivisao(novo->id,50));
    }
    
    return raiz;
}

int calcularAltura(Nodo* nodo){
	int esq, dir;
	if( nodo != NULL){
		esq = calcularAltura(nodo->esquerda);
		dir = calcularAltura(nodo->direita);
		if(esq > dir)
			return esq + 1;
		else
			return dir +1;
	}
	return 0;
}

void calcularNivel(Nodo* nodo, int valor_procurado, int nivel_atual){
    if(nodo->cliente->id == valor_procurado)
        nodo->nivel = nivel_atual;
    else if(nodo->cliente->id > valor_procurado){
        calcularNivel(nodo->esquerda, valor_procurado, ++nivel_atual);
    }
    else{
        calcularNivel(nodo->direita, valor_procurado, ++nivel_atual);
    }
}

int calcularTotalNodos(Nodo* nodo){
    if (nodo == NULL)
        return 0;
    int num_esquerda = calcularTotalNodos(nodo->esquerda);
    int num_direta = calcularTotalNodos(nodo->direita);

    return num_direta + num_esquerda + 1;
    
}

int estritamenteBinaria(Nodo* nodo){
    if(nodo->direita == NULL && nodo->esquerda == NULL)
        return 1;

    if(nodo->direita != NULL && nodo->esquerda != NULL)
        return estritamenteBinaria(nodo->esquerda) && estritamenteBinaria(nodo->direita);
    return 0;
}

int estritamenteBinariaCompleta(Nodo* nodo) {
    
    return estritamenteBinaria(nodo) && calcularAltura(nodo->direita) == calcularAltura(nodo->esquerda); 
}

Hashing* iniciarHash(){
    Hashing* hash = (Hashing*) malloc(sizeof(Hashing*));
    hash->vetor = NULL;
    hash->total = 0;
    return hash;
}

Hashing* iniciarVetorHash(Hashing* hash, int tamanho_hash){
    hash->vetor = (Nodo**) malloc(sizeof(Nodo*) * tamanho_hash);
    int i;
    for (i = 0; i < tamanho_hash; i++){
        hash->vetor[i] = NULL;
    }
    return hash;
}

int calcularHashPos(Hashing* raiz, int valor, int total){

    if (raiz->vetor[total] == NULL )
        return total;
    else {
        if (raiz->vetor[total]->cliente->id > valor )
            total = calcularHashPos(raiz, valor, (1 + total * 2));

        if (raiz->vetor[total]->cliente->id < valor )
            total = calcularHashPos(raiz, valor, (2 + total * 2));
    }
    return total;
}

int calcularHashPosDivisao(int valor, int total){
    return valor % total;
}

Hashing* inserirHash(Hashing* hash, Nodo* dados, int pos){

    if (hash->vetor[pos] == NULL)
        hash->vetor[pos] = dados;
    else if (hash->vetor[pos]->exluido_hash == 1){
        dados->prox = hash->vetor[pos]->prox;
        hash->vetor[pos] = dados;
    }        
    else{
        Nodo* aux = hash->vetor[pos];
        while (aux->prox != NULL ){
            if (aux->prox->exluido_hash == 1)
                break;            
            aux = aux->prox;
        }
        if (aux->prox != NULL)
            dados->prox = aux->prox->prox;
                           
        aux->prox = dados;
    }
    return hash;
}

Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos){
    if (hash->vetor[pos] == NULL)
        return NULL;
    else if (hash->vetor[pos]->exluido_hash == 1)
        return hash->vetor[pos];
    else{
        Nodo* aux = hash->vetor[pos];
        while (aux != NULL ){
            if (aux->cliente->id == pesquisado)
                return aux;           
            aux = aux->prox;
        }
    }
    return NULL;
}

void listarHashFechada(Hashing* hash, int tamanho_hash){
    int i;
    Nodo* aux; 
    for (i = 0; i < tamanho_hash; i++){
        aux = hash->vetor[i];
        while (aux != NULL) {
           if(aux->exluido_hash == 0)
                printf("\tpos[%d] - id: %i\n", i, aux->cliente->id);
            
            aux = aux->prox;
        }   
    }
}

Hashing* carregarArvoreInvertida(Nodo* raiz, Hashing* arvore_invertida){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini2.txt", "r");

    char conteudo[100];
    while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
        dadosBancarios* novo = iniciarlista();
        preencherDados(conteudo, novo);
        Nodo* novo_nodo = criarNodo(novo);
        printf(" pos : %d", calcularHashPos(arvore_invertida, novo->id, 0));
        arvore_invertida = inserirHash(arvore_invertida, novo_nodo, calcularHashPos(arvore_invertida, novo->id, 0));
    }
    return arvore_invertida;
}

