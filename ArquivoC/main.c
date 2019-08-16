#include <stdio.h>
#include <string.h>

typedef struct dadosBancariosOriginal
{
    int id;
    char nome[50];
    float saldo;
    struct dadosBancariosOriginal *prox;

} dadosBancariosOriginal;

dadosBancariosOriginal *carregarArquivos( dadosBancariosOriginal *lista){
    FILE *ponteiro_arquivo;
    ponteiro_arquivo = fopen("DadosBancoPulini.txt", "r");

    if (ponteiro_arquivo == NULL)
        printf("ERRO! O arquivo não foi aberto!\n");
    else{
        printf("O arquivo foi aberto com sucesso!");
        while(!feof(ponteiro_arquivo)){
            char conteudo[100];
            fgets(conteudo, 100, ponteiro_arquivo);
            printf(" conteudo: %s", conteudo);
        }
}

int separastring(char *minhaString) {

    for (int i = 0; i < strlen(minhaString); i++)
    {
        if (minhaString[i] == '|')
        {
            return i;
        }
    }
}


int main(int argc, char const *argv[])
{
    printf("merda");
    return 0;
}
