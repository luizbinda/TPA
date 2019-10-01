#define TAMVET 500

typedef struct Nodo {
    dadosBancarios* cliente;
    struct Nodo* esquerda;
    struct Nodo* direita;
    struct Nodo* pai;
    int nivel, altura, fator_balanceamento;
    // Hashing parametros
    int exluido_hash;
    struct Nodo* prox;
}Nodo;

typedef struct Hashing {
    Nodo** vetor;
}Hashing;

Nodo* raiz;
Hashing* hash;

Nodo* criarNodo(dadosBancarios* cliente);
Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente);
Nodo* removerNodo(Nodo** nodo, int valor_exluido);
void percorrerArvoreEmOrdemCrescente(Nodo* nodo);
void percorrerArvoreEmOrdemDecrescente(Nodo* nodo);
Nodo* buscarValor(Nodo* nodo, int valor_procurado);
Nodo* carregarArquivos(Nodo* nodo, Hashing* hash);
int calcularAltura(Nodo* nodo);
void calcularNivel(Nodo* nodo, int valor_procurado, int nivel_atual);
Nodo* rotacaoParaDireita(Nodo* nodo);
Nodo* rotacaoParaEsquerda(Nodo* nodo);
Nodo* balancearArvore(Nodo *nodo);

//Hashing
Hashing* iniciarHash();
Hashing* iniciarVetorHash(Hashing* hash, int tamanho_hash);
int calcularHashPos(Hashing* raiz, int valor, int total);
int calcularHashPosDivisao(int valor, int total);
Hashing* inserirHash(Hashing* hash, Nodo* dados, int pos);
Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos);
Hashing* excluirHash(Hashing* hash, int id_exluido);
void listarHashFechada(Hashing* hash, int tamanho_hash);
Hashing* carregarArvoreInvertida(Nodo* raiz, Hashing* arvore_invertida);

Nodo* criarNodo(dadosBancarios* cliente){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->cliente = cliente;
	novo->direita = NULL;
	novo->esquerda = NULL;
	novo->pai = NULL;
    novo->nivel = 0;
    novo->altura = 0;
    novo->fator_balanceamento = 0; 
    // Hashing parametros
    novo->prox = NULL;
    novo->exluido_hash = 0;
	return novo;
}

Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente){
    if(nodo == NULL){

        nodo = criarNodo(cliente);
        Nodo* aux = nodo;
        // Percorrendo a árvore para cima a partir do novo elemento inserido
        while (aux != NULL) {
            aux->fator_balanceamento = calcularAltura(aux->direita) - calcularAltura(aux->esquerda);
            
            if (aux->fator_balanceamento > 1 || aux->fator_balanceamento < -1)
                aux = balancearArvore(aux);
        
            aux = aux->pai;
        }
        
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
        //hash = inserirHash(hash, buscarValor(raiz, novo->id), calcularHashPosDivisao(novo->id,50));
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

Nodo* rotacaoParaDireita(Nodo* nodo) {
    // Fazendo a movimentação necessária
    Nodo* nodo_esquerda = nodo->esquerda;
    nodo->esquerda = nodo_esquerda->direita;
    nodo_esquerda->direita = nodo;

    // Caso o nodo for a raiz global, atualiza-se o valor da raiz global
    if (nodo == raiz)
        raiz = nodo_esquerda;

    // Atualizando os fatores de balanceamento
    nodo_esquerda->fator_balanceamento = calcularAltura(nodo_esquerda->direita) - calcularAltura(nodo_esquerda->esquerda);
    nodo->fator_balanceamento = calcularAltura(nodo->direita) - calcularAltura(nodo->esquerda);

    return nodo_esquerda;
}

Nodo* rotacaoParaEsquerda(Nodo* nodo) {
    // Fazendo a movimentação necessária
    Nodo* nodo_direita = nodo->esquerda;
    nodo->esquerda = nodo_direita->esquerda;
    nodo_direita->esquerda = nodo;

    // Caso o nodo for a raiz global, atualiza-se o valor da raiz global
    if (nodo == raiz)
        raiz = nodo_direita;

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

        nodo = rotacaoParaDireita(nodo);
    }
    // Desbalanceada para a direta
    else if (nodo->fator_balanceamento > 1) {
        // Caso o nó à direita tenha somente filho à esquerda
        if (nodo->direita->fator_balanceamento < 0)
            nodo->direita = rotacaoParaDireita(nodo->direita);

        nodo = rotacaoParaEsquerda(nodo);
    }

    return nodo;
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Hashing* iniciarHash(){
    Hashing* hash = (Hashing*) malloc(sizeof(Hashing*));
    hash->vetor = NULL;
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
        if (raiz->vetor[total]->cliente->id < valor )
            total = calcularHashPos(raiz, valor, (1 + total * 2));

        else if (raiz->vetor[total]->cliente->id > valor )
            total = calcularHashPos(raiz, valor, (2 + total * 2));
    }
    return total;
}

int calcularHashPosDivisao(int valor, int total){
    return valor % total;
}


Hashing* carregarArvoreInvertida(Nodo* raiz, Hashing* arvore_invertida){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini2.txt", "r");
    char conteudo[100];
    while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
        dadosBancarios* novo = iniciarlista();
        preencherDados(conteudo, novo);
        Nodo* novo_nodo = criarNodo(novo);
        //arvore_invertida = inserirHash(arvore_invertida, novo_nodo, calcularHashPos(arvore_invertida, novo->id, 0));
    }
    return arvore_invertida;
}

