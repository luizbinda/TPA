#define TAMVET 5000

typedef struct Nodo {
    dadosBancarios* cliente;
    struct Nodo* esquerda;
    struct Nodo* direita;
    struct Nodo* pai;
    int nivel, altura, fator_balanceamento;

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
Nodo* buscarValor(Nodo* nodo, int valor_procurado);
Nodo* carregarArquivos(Nodo* nodo);
int calcularAltura(Nodo* nodo);
void calcularNivel(Nodo* nodo, int valor_procurado, int nivel_atual);
Nodo* rotacaoParaDireita(Nodo* nodo);
Nodo* rotacaoParaEsquerda(Nodo* nodo);
Nodo* balancearArvore(Nodo *nodo);
Nodo* percorrerArvoreBalanceando(Nodo* nodo);

//Hashing
Hashing* iniciarHash();
Hashing* iniciarVetorHash(Hashing* hash, int tamanho_hash);
int calcularHashPos(Hashing* raiz, int valor, int total);
Hashing* inserirHash(Hashing* hash, dadosBancarios* dados, int pos);
Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos);
Hashing* excluirHash(Hashing* hash, int pos);
Hashing* carregarArvoreInvertida(Hashing* arvore_invertida);
void listarHash(Hashing* hash);
int calcularAlturaHash(Hashing* nodo, int pos); 
Nodo* rotacaoParaDireitaHash(Hashing* nodo, int pos);
Nodo* rotacaoParaEsquerdaHash(Hashing* nodo, int pos);
Nodo* balancearHash(Hashing *nodo, int pos);
Hashing* percorrerHashBalanceando(Hashing* nodo, int pos);

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

int calcularHashPos(Hashing* raiz, int valor, int pos){

    if (raiz->vetor[pos] == NULL )
        return pos;
    else {
        if (raiz->vetor[pos]->cliente->id < valor )
            pos = calcularHashPos(raiz, valor, (2 + pos * 2));

        else if (raiz->vetor[pos]->cliente->id > valor )
            pos = calcularHashPos(raiz, valor, (1 + pos * 2));
    }
    return pos;
}

Hashing* inserirHash(Hashing* hash, dadosBancarios* dados, int pos){
    hash->vetor[pos] = inserirNodo(hash->vetor[pos], dados);
    return hash;
}

Hashing* carregarArvoreInvertida(Hashing* arvore_invertida){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");
    char conteudo[100];
    while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
        dadosBancarios* novo = iniciarlista();
        preencherDados(conteudo, novo);
        int pos = calcularHashPos(arvore_invertida, novo->id, 0);
        arvore_invertida = inserirHash(arvore_invertida, novo, pos);
        arvore_invertida = percorrerHashBalanceando(arvore_invertida, pos);
    }
    return arvore_invertida;
}

Hashing* excluirHash(Hashing* hash, int pos){
    free(hash->vetor[pos]);    
    hash->vetor[pos] = NULL;    
    return hash;
}

Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos){
    if (hash->vetor[pos] == NULL)
        return NULL;
    else{
        Nodo* aux = buscarValor(hash->vetor[pos], pesquisado);
        return aux;
    }
    return NULL;
}

void listarHash(Hashing* hash){
    int i;
    for ( i = 0; i < TAMVET; i++)
    {
        if(hash->vetor[i] != NULL)
        printf("ID: %d\n", hash->vetor[i]->cliente->id);
    }
    
}

int calcularAlturaHash(Hashing* nodo, int pos) {
	int esq, dir;
	if( nodo->vetor[pos] != NULL){
		esq = calcularAlturaHash(nodo, (2 + pos * 2));
		dir = calcularAlturaHash(nodo, (1 + pos * 2));
		if(esq > dir)
			return esq + 1;
		else
			return dir +1;
	}
	return 0;
}

Nodo* rotacaoParaDireitaHash(Hashing* nodo, int pos) {
    // Fazendo a movimentação necessária
    int pos_esquerda = (2 + pos * 2);
    nodo->vetor[pos_esquerda] = nodo->vetor[(1 + pos_esquerda * 2)];
    nodo->vetor[(1 + pos_esquerda * 2)] = nodo->vetor[pos];

    // Atualizando os fatores de balanceamento
    nodo->vetor[pos_esquerda]->fator_balanceamento = calcularAlturaHash(nodo, ( 1 + pos_esquerda * 2)) - calcularAlturaHash(nodo, ( 2 + pos_esquerda * 2));
    nodo->vetor[pos]->fator_balanceamento = calcularAlturaHash(nodo, ( 1 + pos * 2)) - calcularAlturaHash(nodo, ( 2 + pos * 2));

    return nodo->vetor[pos_esquerda];
}

Nodo* rotacaoParaEsquerdaHash(Hashing* nodo, int pos) {
    // Fazendo a movimentação necessária
    Nodo* nodo_direita = nodo->vetor[(1 + pos * 2)];
    int pos_direita = (1 + pos * 2);
    nodo->vetor[(1 + pos * 2)] = nodo->vetor[(2 + pos_direita * 2)];
    nodo->vetor[(2 + pos_direita * 2)] = nodo->vetor[pos];

       // Atualizando os fatores de balanceamento
    nodo->vetor[pos_direita]->fator_balanceamento = calcularAlturaHash(nodo, ( 1 + pos_direita * 2)) - calcularAlturaHash(nodo, ( 2 + pos_direita * 2));
    nodo->vetor[pos]->fator_balanceamento = calcularAlturaHash(nodo, ( 1 + pos * 2)) - calcularAlturaHash(nodo, ( 2 + pos * 2));

    return nodo->vetor[pos_direita];
} 

Nodo* balancearHash(Hashing *nodo, int pos) {
    // Desbalanceada para a esquerda
    if (nodo->vetor[pos]->fator_balanceamento < -1) {
        // Caso o nó à esquerda tenha somente filho à direita
        if(nodo->vetor[(2 + pos * 2)]->fator_balanceamento > 0)
            nodo->vetor[(2 + pos * 2)] = rotacaoParaEsquerdaHash(nodo, (2 + pos * 2));

        return rotacaoParaDireitaHash(nodo, pos);
    }
    // Desbalanceada para a direta
    else if (nodo->vetor[pos]->fator_balanceamento > 1) {
        // Caso o nó à direita tenha somente filho à esquerda
        if (nodo->vetor[(1 + pos * 2)]->fator_balanceamento < 0)
            nodo->vetor[(1 + pos * 2)] = rotacaoParaDireitaHash(nodo, (1 + pos * 2));

        return rotacaoParaEsquerdaHash(nodo, pos);
    }

    return nodo->vetor[pos];
}

Hashing* percorrerHashBalanceando(Hashing* nodo, int pos){
    if(nodo->vetor[pos] != NULL){
        percorrerHashBalanceando(nodo, (2 + pos * 2));
        percorrerHashBalanceando(nodo, (1 + pos * 2)); 
        nodo->vetor[pos]->fator_balanceamento = calcularAlturaHash(nodo, (1 + pos * 2)) - calcularAlturaHash(nodo, (2 + pos * 2));
        if (nodo->vetor[pos]->fator_balanceamento > 1 || nodo->vetor[pos]->fator_balanceamento < -1)
        nodo->vetor[pos] = balancearHash(nodo, pos);    
    }
    return nodo;
}

