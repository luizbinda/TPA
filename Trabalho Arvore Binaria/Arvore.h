#define TAMVET 500

typedef struct Nodo {
    dadosBancarios* cliente;
    struct Nodo* esquerda;
    struct Nodo* direita;
    int nivel, altura;
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
int calcularTotalNodos(Nodo* nodo);
int estritamenteBinaria(Nodo* nodo);
/////////////////////// Hash
Hashing* iniciarHash();
Hashing* iniciarVetorHash(Hashing* hash, int tamanho_hash);
int calcularHashPos(Hashing* raiz, int valor, int total);
int calcularHashPosDivisao(int valor, int total);
Hashing* inserirHash(Hashing* hash, Nodo* dados, int pos);
Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos);
Hashing* excluirHash(Hashing* hash, int id_exluido);
void listarHashFechada(Hashing* hash, int tamanho_hash);
Hashing* carregarArvoreInvertida(Nodo* raiz, Hashing* arvore_invertida);
int verificarEspelhamento(Nodo* nodo, Hashing* arvore_invertida, int pos);

Nodo* criarNodo(dadosBancarios* cliente){
    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->cliente = cliente;
	novo->direita = NULL;
	novo->esquerda = NULL;
    novo->nivel = 0;
    novo->altura = 0;
	return novo;
}

Nodo* inserirNodo(Nodo* nodo, dadosBancarios* cliente){
    if(nodo == NULL)
        nodo = criarNodo(cliente);
    else if ( cliente->id < nodo->cliente->id)
        nodo->esquerda = inserirNodo(nodo->esquerda, cliente);
    else 
        nodo->direita = inserirNodo(nodo->direita, cliente);

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
            (*nodo) = (*nodo)->direita;
            free(temporario);
        }
        else if((*nodo)->direita == NULL){
            Nodo* temporario = (*nodo);
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

Hashing* inserirHash(Hashing* hash, Nodo* dados, int pos){

    if (hash->vetor[pos] == NULL)
        hash->vetor[pos] = dados;

    else{
        Nodo* aux = hash->vetor[pos];
        aux = inserirNodo( aux, aux->cliente);
    }
    return hash;
}

Nodo* pesquisarHash(Hashing* hash, int pesquisado, int pos){
    if (hash->vetor[pos] == NULL)
        return NULL;
    else if (hash->vetor[pos]->exluido_hash == 1)
        return hash->vetor[pos];
    else{
        Nodo* aux = buscarValor(raiz, valor);
        return aux;
        }
    }
    return NULL;
}

Hashing* excluirHash(Hashing* hash, int id_exluido){
    Nodo* aux = pesquisarHash(hash, id_exluido, calcularHashPosDivisao(id_exluido, TAMVET));
    
    if (aux == NULL)
        printf("O id que deseja excluir nao existe...\n");	
                    
    else if ( aux->exluido_hash == 1)
        printf("O id pesquisado ja foi excluido!\n");

    else{
        aux->exluido_hash = 1;
    }

    return hash;
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
        arvore_invertida = inserirHash(arvore_invertida, novo_nodo, calcularHashPos(arvore_invertida, novo->id, 0));
    }
    return arvore_invertida;
}

int verificarEspelhamento(Nodo* nodo, Hashing* arvore_invertida, int pos) {
    int espelho;
    if(nodo != NULL && arvore_invertida->vetor[pos] != NULL && nodo->cliente->id == arvore_invertida->vetor[pos]->cliente->id)
        espelho = 1;
    if(nodo == NULL && arvore_invertida->vetor[pos] == NULL)
        espelho = 1;
    if(nodo != NULL && arvore_invertida->vetor[pos] != NULL && nodo->cliente->id != arvore_invertida->vetor[pos]->cliente->id)
        espelho = 0;
    if((nodo == NULL && arvore_invertida->vetor[pos] != NULL) || (nodo != NULL && arvore_invertida->vetor[pos] == NULL))
        espelho = 0;
    if(nodo != NULL && arvore_invertida->vetor[pos] != NULL)
        espelho = verificarEspelhamento(nodo->esquerda, arvore_invertida, (2 + pos * 2)) && verificarEspelhamento(nodo->direita, arvore_invertida, (1 + pos * 2));
        
    return espelho;
}

