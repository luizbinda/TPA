#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"

int main(){

    grafoBairros* grafo = lerArquivo("MatrizBairros.csv");
    grafo = lerArquivoDistancias( grafo, "MatrizBairros.csv");
    listarGrafo(grafo);
}
