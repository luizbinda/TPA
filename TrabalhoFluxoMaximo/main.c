
#include "structs.h"

int main(int argc, char const *argv[])
{
    char nome[30] = "ExemploArquivoFluxo.txt"; 
    Grafo *C = GrafobyArchive(nome); // Funcao para ler do arquivo 
    char nomeVeiculos[100] = "ExemploArquivoVeiculos.txt"; 
    int total = VeiculosbyArchive(nomeVeiculos); // Funcao para ler do arquivo
    Veiculos** veiculos = archiveVeiculos( nomeVeiculos, iniciarVeiculos(total));
    char nomeDistancia[30] = "ExemploArquivoDistancias.txt"; 
    Grafo *distancias = GrafobyArchive(nomeDistancia); // Funcao para ler do arquivo
    exibirGrafo(C); // listar grafo
    char o[30], d[30]; 
    printf("Digire a aresta de origem: ");
    scanf("%s", &o);
    printf("Digite a aresta de destino: ");
    scanf("%s", &d);
    int origem = buscarNome(C, o); // funcao converter string pra posicao na lista de nomes
    int destino = buscarNome(C, d); // funcao converter string pra posicao na lista de nomes

    if (origem != -1  && destino != -1) // se achar origem e destino chama funcao de fluxo
    {
        fluxo_maximo(C, origem, destino, veiculos, total, distancias);
        listarVeiculosNaoAlocados(veiculos, total);
    }
    
    else
        printf("Origem ou destino nao encontrados");
    
    return 0;
}
