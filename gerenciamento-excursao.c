#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct turista {
    char nome[100];
    char cpf[15];
    struct turista *proximo;
} Turista;

typedef struct excursao {
    char nomeDoGrupo[100];
    char data[11];
    int numeroDeDias;
    char destino[100];
    int quantDeTuristas;
    Turista *turistas;
    struct excursao *proximo;
} Excursao;

int criarExcursao(Excursao **lista, char nome[], char data[], int dias, char destino[], int quant){
    Excursao *novaExcursao = (Excursao *) malloc(sizeof(Excursao));
    if(!novaExcursao){
        printf("Nao foi possivel alocar memoria para a excursao\n\n");
        return 0;
    }
    strcpy(novaExcursao->nomeDoGrupo, nome);
    strcpy(novaExcursao->data, data);
    novaExcursao->numeroDeDias = dias;
    strcpy(novaExcursao->destino, destino);
    novaExcursao->quantDeTuristas = quant;
    novaExcursao->turistas = NULL;
    novaExcursao->proximo = *lista;
    *lista = novaExcursao;
    return 1;
}

int removerExcursao(Excursao **lista, char nome[]){
    Excursao *anterior = NULL;
    Excursao *aux = *lista;

    while(aux != NULL && strcmp(aux->nomeDoGrupo, nome) != 0){
        anterior = aux;
        aux = aux->proximo;
    }

    if(aux == NULL){
        printf("A excursao nao foi encontrada.\n\n");
        return 0;
    }

    if(anterior == NULL){
        *lista = aux->proximo;
    } else {
        anterior->proximo = aux->proximo;
    }

    free(aux);
    return 1;
}


int main(){
    Excursao *lista = NULL;
    int escolha;

    do{
        system("cls");
        printf(">> MENU <<\n\n");
        printf("1 - Criar Excursao\n");
        printf("2 - Remover Excursao\n");
        printf("3 - Inserir Turista em Excursao\n");
        printf("4 - Remover Turista de Excursao\n");
        printf("5 - Listar Todas as Excursoes\n");
        printf("6 - Listar Informacoes de Excursao Especifica\n");
        printf("7 - Encerrar Programa\n\n");

        printf("input: ");
        scanf("%d", &escolha);

        switch (escolha){
            case 1:
                
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                break;
            default:
                system("cls");
                printf("Opcao invalida.\n\n");
                system("pause");
        }
        
    }while(escolha != 7);
}