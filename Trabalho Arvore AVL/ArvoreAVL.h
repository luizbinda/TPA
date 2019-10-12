#define TAMVET 50000

typedef struct Nodo {
    dadosBancarios* cliente;
    struct Nodo* esquerda;
    struct Nodo* direita;
    struct Nodo* pai;
    int nivel, altura, fator_balanceamento;

}Nodo;

Nodo* raiz;

Nodo* criarNodo(dadosBancarios* cliente);
Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente);
Nodo* removerNodo(Nodo** nodo, int valor_exluido);
void percorrerArvoreEmOrdemCrescente(Nodo* nodo);
Nodo* buscarValor(Nodo* nodo, int valor_procurado);
Nodo* carregarArquivos(Nodo* nodo);
int calcularAltura(Nodo* nodo);
Nodo* rotacaoParaDireita(Nodo* nodo);
Nodo* rotacaoParaEsquerda(Nodo* nodo);
Nodo* balancearArvore(Nodo *nodo);
Nodo* percorrerArvoreBalanceando(Nodo* nodo);

Nodo* criarNodo(dadosBancarios* cliente){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->cliente = cliente;
	novo->direita = NULL;
	novo->esquerda = NULL;
	novo->pai = NULL;
    novo->nivel = 0;
    novo->altura = 0;
    novo->fator_balanceamento = 0; 
	return novo;
}

Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente){
    Nodo* aux;

    if(nodo == NULL){

        nodo = criarNodo(cliente);
        aux = nodo;
        
    }
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

Nodo* removerNodo(Nodo** nodo, int valor_exluido){
    if((*nodo) == NULL)
        return NULL;
    else if ((*nodo)->cliente->id > valor_exluido) 
        (*nodo)->esquerda = removerNodo(&(*nodo)->esquerda, valor_exluido);
    else if( (*nodo)->cliente->id < valor_exluido)
        (*nodo)->direita = removerNodo(&(*nodo)->direita, valor_exluido);
    else {
        if((*nodo)->direita == NULL && (*nodo)->esquerda == NULL){
            free((*nodo));
            (*nodo) = NULL;
        }            
        else if((*nodo)->esquerda == NULL){
            Nodo* temporario = (*nodo);

            (*nodo)->direita->pai = (*nodo)->pai;
            (*nodo) = (*nodo)->direita;
            free(temporario);
        }
        else if((*nodo)->direita == NULL){
            Nodo* temporario = (*nodo);    

            (*nodo)->esquerda->pai = (*nodo)->pai;
            (*nodo) = (*nodo)->esquerda;
            free(temporario);
        }
        else{
            Nodo* temporario = (*nodo)->esquerda;
            while (temporario->direita != NULL )
                temporario = temporario->direita;
            //Trocando os dados entre os nodos...
            dadosBancarios* aux = (*nodo)->cliente;
            (*nodo)->cliente = temporario->cliente;
            temporario->cliente = aux;         
            
            (*nodo)->esquerda = removerNodo(&(*nodo)->esquerda, valor_exluido);
        }
    }    
    return (*nodo);
}

void percorrerArvoreEmOrdemCrescente(Nodo* nodo){
    if(nodo != NULL){
        percorrerArvoreEmOrdemCrescente(nodo->esquerda);
        printf("\t-%d-\n", nodo->cliente->id);
        percorrerArvoreEmOrdemCrescente(nodo->direita);    
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
        raiz = percorrerArvoreBalanceando(raiz);

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

Nodo* rotacaoParaDireita(Nodo* nodo) {
    // Fazendo a movimentação necessária
    Nodo* nodo_esquerda = nodo->esquerda;
    nodo->esquerda = nodo_esquerda->direita;
    nodo_esquerda->direita = nodo;

    // Acertando os pais
    if (nodo->esquerda)
        nodo->esquerda->pai = nodo;
    nodo_esquerda->pai = nodo->pai;
    nodo->pai = nodo_esquerda;

    // Caso o nodo for a raiz global, atualiza-se o valor da raiz global
    if (nodo == raiz)
        raiz = nodo_esquerda;

    // Ligando os ponteiros do pai da nova raiz da sub-arvore corretamente
    if (nodo_esquerda->pai)
        if (nodo_esquerda->cliente->id < nodo_esquerda->pai->cliente->id)
            nodo_esquerda->pai->esquerda = nodo_esquerda;
        else
            nodo_esquerda->pai->direita = nodo_esquerda;


    // Atualizando os fatores de balanceamento
    nodo_esquerda->fator_balanceamento = calcularAltura(nodo_esquerda->direita) - calcularAltura(nodo_esquerda->esquerda);
    nodo->fator_balanceamento = calcularAltura(nodo->direita) - calcularAltura(nodo->esquerda);

    return nodo_esquerda;
}

Nodo* rotacaoParaEsquerda(Nodo* nodo) {
    // Fazendo a movimentação necessária
    Nodo* nodo_direita = nodo->direita;
    nodo->direita = nodo_direita->esquerda;
    nodo_direita->esquerda = nodo;
    
    // Acertando os pais
    if (nodo->direita)
        nodo->direita->pai = nodo;
    nodo_direita->pai = nodo->pai;
    nodo->pai = nodo_direita;

    // Caso o nodo for a raiz global, atualiza-se o valor da raiz global
    if (nodo == raiz)
        raiz = nodo_direita;
    
    // Ligando os ponteiros do pai da nova raiz da sub-arvore corretamente
    if (nodo_direita->pai)
        if (nodo_direita->cliente->id < nodo_direita->pai->cliente->id)
            nodo_direita->pai->esquerda = nodo_direita;
        else
            nodo_direita->pai->direita = nodo_direita;
    
    // Atualizando os fatores de balanceamento
    nodo_direita->fator_balanceamento = calcularAltura(nodo_direita->direita) - calcularAltura(nodo_direita->esquerda);
    nodo->fator_balanceamento = calcularAltura(nodo->direita) - calcularAltura(nodo->esquerda);

    return nodo_direita;
} 

Nodo* balancearArvore(Nodo *nodo) {
    // Desbalanceada para a esquerda
    if (nodo->fator_balanceamento < -1) {
        // Caso o nó à esquerda tenha somente filho à direita
        if(nodo->esquerda->fator_balanceamento > 0)
            nodo->esquerda = rotacaoParaEsquerda(nodo->esquerda);

        return rotacaoParaDireita(nodo);
    }
    // Desbalanceada para a direta
    else if (nodo->fator_balanceamento > 1) {
        // Caso o nó à direita tenha somente filho à esquerda
        if (nodo->direita->fator_balanceamento < 0)
            nodo->direita = rotacaoParaDireita(nodo->direita);

        return rotacaoParaEsquerda(nodo);
    }

    return nodo;
}

Nodo* percorrerArvoreBalanceando(Nodo* nodo){
    if(nodo != NULL){
        percorrerArvoreBalanceando(nodo->esquerda);
        percorrerArvoreBalanceando(nodo->direita); 
        nodo->fator_balanceamento = calcularAltura(nodo->direita) - calcularAltura(nodo->esquerda); 
        if (nodo->fator_balanceamento > 1 || nodo->fator_balanceamento < -1)
        nodo = balancearArvore(nodo);    
    }
    return nodo;
}
 