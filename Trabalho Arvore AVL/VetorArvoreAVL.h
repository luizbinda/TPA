/*
#include "DadosBancoOriginal.h"
#include "ArvoreAVL.h"
*/

typedef struct Hashing {
    Nodo** vetor;
}Hashing;

Hashing* hash;

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
int getPosEsquerda(int pos);
int getPosDireita(int pos);
void descerPelaEsquerda(Hashing* nodo, int pos);
void subirPelaEsquerda(Hashing* nodo, int pos);
void descerPelaDireita(Hashing* nodo, int pos);
void subirPelaDireita(Hashing* nodo, int pos);


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
            pos = calcularHashPos(raiz, valor, getPosDireita(pos));

        else if (raiz->vetor[pos]->cliente->id > valor )
            pos = calcularHashPos(raiz, valor, getPosEsquerda(pos));
    }
    return pos;
}

Hashing* inserirHash(Hashing* hash, dadosBancarios* dados, int pos){
    hash->vetor[pos] = inserirNodo(hash->vetor[pos], dados);
    return hash;
}

Hashing* carregarArvoreInvertida(Hashing* hash){
    FILE* ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");
    char conteudo[100];
    while(fgets(conteudo, BUFSIZ, ponteiro_arquivo) != NULL){
        dadosBancarios* novo = iniciarlista();
        preencherDados(conteudo, novo);
        hash = inserirHash(hash, novo, calcularHashPos(hash, novo->id, 0));
        hash = percorrerHashBalanceando(hash, 0);
    }
    return hash;
}

Hashing* excluirHash(Hashing* hash, int pos){
    Nodo* excluido = hash->vetor[pos];
    if (hash->vetor[getPosDireita(pos)])
        descerPelaEsquerda(hash, getPosPai(pos));
    else if (hash->vetor[getPosEsquerda(pos)])
        descerPelaDireita(hash, getPosPai(pos));
    else
        hash->vetor[pos] = NULL;
    
    free(excluido);  
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
        printf("POS[%d] ID: %d\n", i, hash->vetor[i]->cliente->id);
    }
    
}

int calcularAlturaHash(Hashing* nodo, int pos) {

	if( nodo->vetor[pos] == NULL)
	    return 0;

    int esq = calcularAlturaHash(nodo, getPosEsquerda(pos));
	int dir = calcularAlturaHash(nodo, getPosDireita(pos));
    
    return (esq > dir) ? esq + 1 : dir +1;
}

Nodo* rotacaoParaDireitaHash(Hashing* nodo, int pos) {
    // Fazendo a movimentação necessária
    subirPelaDireita(nodo, pos);
    descerPelaDireita(nodo, pos);
    // Atualizando os fatores de balanceamento
    nodo->vetor[getPosEsquerda(pos)]->fator_balanceamento = calcularAlturaHash(nodo, getPosDireita(getPosEsquerda(pos))) - calcularAlturaHash(nodo, getPosEsquerda(getPosEsquerda(pos)));
    nodo->vetor[pos]->fator_balanceamento = calcularAlturaHash(nodo,getPosDireita(pos)) - calcularAlturaHash(nodo, getPosEsquerda(pos));

    return nodo->vetor[pos];
}

Nodo* rotacaoParaEsquerdaHash(Hashing* nodo, int pos) {
    
    subirPelaEsquerda(nodo, pos);
    descerPelaEsquerda(nodo, pos);
    // Atualizando os fatores de balanceamento
    nodo->vetor[getPosDireita(pos)]->fator_balanceamento = calcularAlturaHash(nodo, getPosDireita(getPosDireita(pos))) - calcularAlturaHash(nodo, getPosEsquerda(getPosDireita(pos)));
    nodo->vetor[pos]->fator_balanceamento = calcularAlturaHash(nodo, getPosDireita(pos)) - calcularAlturaHash(nodo, ( 1 + pos * 2));  

    return nodo->vetor[pos];
} 

Nodo* balancearHash(Hashing *nodo, int pos) {
    // Desbalanceada para a esquerda
    if (nodo->vetor[pos]->fator_balanceamento < -1) {
        // Caso o nó à esquerda tenha somente filho à direita
        if(nodo->vetor[getPosEsquerda(pos)]->fator_balanceamento > 0)
            nodo->vetor[getPosEsquerda(pos)] = rotacaoParaEsquerdaHash(nodo, getPosEsquerda(pos));

        return rotacaoParaDireitaHash(nodo, pos);
    }
    // Desbalanceada para a direta
    else if (nodo->vetor[pos]->fator_balanceamento > 1) {
        // Caso o nó à direita tenha somente filho à esquerda
        if (nodo->vetor[getPosDireita(pos)]->fator_balanceamento < 0)
            nodo->vetor[getPosDireita(pos)] = rotacaoParaDireitaHash(nodo, getPosDireita(pos));

        return rotacaoParaEsquerdaHash(nodo, pos);
    }

    return nodo->vetor[pos];
}

Hashing* percorrerHashBalanceando(Hashing* nodo, int pos){
    
    if(nodo->vetor[pos]){
        percorrerHashBalanceando(nodo, getPosEsquerda(pos));
        percorrerHashBalanceando(nodo, getPosDireita(pos));

        nodo->vetor[pos]->fator_balanceamento = calcularAlturaHash(nodo, getPosDireita(pos)) - calcularAlturaHash(nodo, getPosEsquerda(pos));
        if (nodo->vetor[pos]->fator_balanceamento > 1 || nodo->vetor[pos]->fator_balanceamento < -1)
            nodo->vetor[pos] = balancearHash(nodo, pos);    
    }
    return nodo;
}

int getPosEsquerda(int pos){
    return ( pos * 2) + 1;
}

int getPosDireita(int pos){
    return (pos * 2) + 2;
}

int getPosPai(int pos){
    return (pos - 1) / 2;
}

void descerPelaEsquerda(Hashing* nodo, int pos){
    if(nodo->vetor[pos]){              
        if(nodo->vetor[getPosEsquerda(pos)] && pos != 0){
            nodo->vetor[getPosDireita(getPosEsquerda(getPosPai(pos)))] = nodo->vetor[getPosEsquerda(pos)];
            nodo->vetor[getPosEsquerda(pos)] = NULL;
        }        
        nodo->vetor[pos] = nodo->vetor[getPosDireita(pos)];
        descerPelaEsquerda(nodo, getPosDireita(pos));
    }          
    else
        nodo->vetor[pos] = NULL;
}

void subirPelaEsquerda(Hashing* nodo, int pos){
    if(nodo->vetor[getPosEsquerda(pos)]){
        subirPelaEsquerda(nodo, getPosEsquerda(pos));
    }
    nodo->vetor[getPosEsquerda(pos)] = nodo->vetor[pos];
}

void descerPelaDireita(Hashing* nodo, int pos){
 
    if(nodo->vetor[pos]){
        if(nodo->vetor[getPosDireita(pos)] && pos != 0){
            nodo->vetor[getPosEsquerda(getPosDireita(getPosPai(pos)))] = nodo->vetor[getPosDireita(pos)];
            nodo->vetor[getPosDireita(pos)] = NULL;
        } 
        nodo->vetor[pos] = nodo->vetor[getPosEsquerda(pos)];
        descerPelaDireita(nodo, getPosEsquerda(pos));
    }
    else
        nodo->vetor[pos] = NULL;
}

void subirPelaDireita(Hashing* nodo, int pos){
    if(nodo->vetor[getPosDireita(pos)]){
            subirPelaDireita(nodo, getPosDireita(pos));
        }
    nodo->vetor[getPosDireita(pos)] = nodo->vetor[pos];
}

