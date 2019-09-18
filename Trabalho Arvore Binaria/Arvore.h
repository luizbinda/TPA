typedef struct Nodo {
    int valor;
    struct Nodo* esquerda;
    struct Nodo* direita;
    struct Nodo* pai;
}Nodo;

Nodo* raiz;

Nodo* iniciarArvore();
Nodo* criarNodo(int valor);
Nodo* inserirNodo(Nodo* nodo, int novo_valor);
Nodo* removerNodo(Nodo* nodo, int valor_exluido);
void percorrerArvoreEmOrdem(Nodo* nodo);
void percorrerArvorePreOrdem(Nodo* nodo);
void percorrerArvorePosOrdem(Nodo* nodo);
Nodo* buscarValor(Nodo* nodo, int valor_procurado);

Nodo* iniciarArvore(){
    return NULL;
}

Nodo* criarNodo(int valor){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->valor = valor;
	novo->direita = NULL;
	novo->esquerda = NULL;
	novo->pai = NULL;
	return novo;
}

Nodo* inserirNodo(Nodo* nodo, int novo_valor){
    if(nodo == NULL)
        nodo = criarNodo(novo_valor);
    else if ( novo_valor < nodo->valor) {
        nodo->esquerda = inserirNodo(nodo->esquerda, novo_valor);
        nodo->esquerda->pai = nodo;
    }
    else if ( novo_valor < nodo->valor) {
        nodo->direita = inserirNodo(nodo->direita, novo_valor);
        nodo->direita->pai = nodo;
    }
    return nodo;
}

Nodo* removerNodo(Nodo* nodo, int valor_exluido){
    if(nodo == NULL)
        return NULL;
    else if (nodo->valor > valor_exluido) 
        nodo->esquerda = removerNodo(nodo->esquerda, valor_exluido);
    else if( nodo->valor < valor_exluido)
        nodo->direita = removerNodo(nodo->direita, valor_exluido);
    else {
        if(nodo->direita == NULL && nodo->esquerda == NULL){
            free(nodo);
            nodo = NULL;
        }            
        else if(nodo->esquerda == NULL){
            Nodo* temporario = nodo;
            nodo->direita->pai = nodo->pai;
            nodo = nodo->direita;
            free(temporario);
        }
        else if(nodo->esquerda == NULL){
            Nodo* temporario = nodo;
            nodo->esquerda->pai = nodo->pai;
            nodo = nodo->esquerda;
            free(temporario);
        }
        else{
            Nodo* temporario = nodo->esquerda;
            while (temporario->direita != NULL )
                temporario = temporario->direita;
            
            nodo->valor = temporario->valor;
            temporario->valor = valor_exluido;

            nodo->esquerda = removerNodo(nodo->esquerda, valor_exluido);
        }
    }   
}

void percorrerArvoreEmOrdem(Nodo* nodo){
    if(nodo != NULL){
        percorrerArvoreEmOrdem(nodo->esquerda);
        printf("\t-%d-\n", nodo->valor);
        percorrerArvoreEmOrdem(nodo->direita);    
    }
}

void percorrerArvorePreOrdem(Nodo* nodo){
    if (nodo != NULL){
        printf("\t-%d-", nodo->valor);
		percorrerArvorePreOrdem(nodo->esquerda);
		percorrerArvorePreOrdem(nodo->direita);
    }
}

void percorrerArvorePosOrdem(Nodo* nodo){
    if (nodo != NULL){
		percorrerArvorePosOrdem(nodo->esquerda);
		percorrerArvorePosOrdem(nodo->direita);
        printf("\t-%d-", nodo->valor);
    } 
}

Nodo* buscarValor(Nodo* nodo, int valor_procurado){
    if(nodo == NULL)
        return NULL;
    else if(nodo->valor == valor_procurado)
        return nodo;
    else if(nodo->valor > valor_procurado)
        buscarValor(nodo->esquerda, valor_procurado);
    else
        buscarValor(nodo->direita, valor_procurado);
}
