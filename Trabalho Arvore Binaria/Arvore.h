typedef struct Nodo {
    dadosBancarios* cliente;
    struct Nodo* esquerda;
    struct Nodo* direita;
    struct Nodo* pai;
    int nivel, altura;
}Nodo;

Nodo* raiz;

Nodo* criarNodo(dadosBancarios* cliente);
Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente);
Nodo* removerNodo(Nodo* nodo, int valor_exluido);
void percorrerArvoreEmOrdemCrescente(Nodo* nodo);
void percorrerArvoreEmOrdemDecrescente(Nodo* nodo);
Nodo* buscarValor(Nodo* nodo, int valor_procurado);
Nodo* carregarArquivos(Nodo* nodo);

Nodo* criarNodo(dadosBancarios* cliente){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->cliente = cliente;
	novo->direita = NULL;
	novo->esquerda = NULL;
	novo->pai = NULL;
    novo->nivel = 0;
    novo->altura = 0;
	return novo;
}

Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente){
    if(nodo == NULL)
        nodo = criarNodo(cliente);
    else if ( cliente->id < nodo->cliente->id) {
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
            free(nodo);
            nodo = NULL;
        }            
        else if(nodo->esquerda == NULL){
            Nodo* temporario = nodo;
            nodo->direita->pai = nodo->pai;
            nodo = nodo->direita;
            free(temporario);
        }
        else if(nodo->direita == NULL){
            Nodo* temporario = nodo;
            nodo->esquerda->pai = nodo->pai;
            nodo = nodo->esquerda;
            free(temporario);
        }
        else{
            Nodo* temporario = nodo->esquerda;
            while (temporario->direita != NULL ){
                temporario = temporario->direita;
            }            
            nodo->cliente->id = temporario->cliente->id;
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

Nodo* carregarArquivos(Nodo* raiz){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");

    char conteudo[100];
    while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
        dadosBancarios* novo = iniciarlista();
        preencherDados(conteudo, novo);   
        raiz = inserirNodo(raiz, novo);
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

int calcularNivel(Nodo* nodo, int valor_procurado, int nivel_atual){
    if(nodo->cliente->id == valor_procurado)
        nodo->nivel = nivel_atual;
    else if(nodo->cliente->id > valor_procurado){
        calcularNivel(nodo->esquerda, valor_procurado, ++nivel_atual);
    }
    else{
        calcularNivel(nodo->direita, valor_procurado, ++nivel_atual);
    }
}

int estritamente_bin(Nodo* nodo){
    if(!nodo->direita && !nodo->esquerda)
        return 1;

    if(nodo->direita && nodo->esquerda)
        return estritamente_bin(nodo->esquerda) && estritamente_bin(nodo->direita);

    return 0;
}


int contarNodos(Nodo* nodo, int num_nodo){
    if(nodo != NULL){
        num_nodo = contarNodos(nodo->esquerda, num_nodo);
        num_nodo = contarNodos(nodo->direita, num_nodo);    
    }
    return num_nodo;
}