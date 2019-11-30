
#include "structs.h"

int main(int argc, char const *argv[])
{
    char nome[30] = "grafo1.txt";
    Grafo *C = GrafobyArchive(nome);
    //exibirGrafo(C);
    int o, d;
    printf("Digire a aresta de origem: ");
    scanf("%d", &o);
    printf("Digite a aresta de destino: ");
    scanf("%d", &d);
    fluxo_maximo(C, o, d);
    return 0;
}
