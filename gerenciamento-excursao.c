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

int criarExcursao(Excursao **lista, char nome[], char data[], int dias, char destino[]){
    Excursao *novaExcursao = (Excursao *) malloc(sizeof(Excursao));
    if(!novaExcursao)
        return 0;
    strcpy(novaExcursao->nomeDoGrupo, nome);
    strcpy(novaExcursao->data, data);
    novaExcursao->numeroDeDias = dias;
    strcpy(novaExcursao->destino, destino);
    novaExcursao->quantDeTuristas = 0;
    novaExcursao->turistas = NULL;
    novaExcursao->proximo = NULL;

    Excursao *ultimo = *lista;
    if (*lista == NULL) {
        *lista = novaExcursao;
    } else {
        while(ultimo->proximo != NULL){
            ultimo = ultimo->proximo;
        }

        ultimo->proximo = novaExcursao;
    }
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

int inserirTurista(Excursao **listaExcursao, char nomeExcursao[], char nomeTurista[], char cpf[]){
    Excursao *aux = *listaExcursao;

    while (aux != NULL && strcmp(aux->nomeDoGrupo,nomeExcursao) != 0){
        aux = aux -> proximo;
    }
    if (aux == NULL){
        return 0;
    }
    Turista *novoTurista = (Turista*)malloc(sizeof(Turista));

    if (novoTurista == NULL){
        printf("Memoria nao alocada.\n");
        return 0;
    }
    strcpy(novoTurista -> nome,nomeTurista);
    strcpy(novoTurista -> cpf,cpf);
    novoTurista -> proximo = NULL;

    Turista *ultimo = aux->turistas;
    if(aux->turistas == NULL){
        aux->turistas = novoTurista;
    } else {
        while(ultimo->proximo != NULL)
            ultimo = ultimo->proximo;
        ultimo->proximo = novoTurista;
    }
    aux -> quantDeTuristas++;
    return 1;
}

int removerTurista(Excursao **lista, char cpf[]) {
    Excursao *aux = *lista;

    while (aux != NULL) {
        Turista *anterior = NULL;
        Turista *atual = aux->turistas;

        while (atual != NULL) {
            if (strcmp(atual->cpf, cpf) == 0) {
                if (anterior == NULL) {
                    aux->turistas = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }

                free(atual);
                aux->quantDeTuristas--;

                return 1;
            }
            anterior = atual;
            atual = atual->proximo;
        }

        aux = aux->proximo;
    }

    return 0;
}


int listarExcursoes(Excursao *lista){
    Excursao *aux = lista;
    int i=1;
    
    printf("\n  LISTA DE TODAS AS EXCURSOES\n");
    while(aux!=NULL){
        printf("\n >> Excursao %d << \n", i);
        printf("Grupo: %s\n", aux->nomeDoGrupo);
        printf("Data: %s\n", aux->data);
        printf("Numero de dias: %d\n",aux->numeroDeDias);
        printf("Destino: %s\n", aux->destino);
        printf("Numero de turistas: %d\n", aux->quantDeTuristas);
        printf("\n==============================\n");
        i++;
        aux = aux->proximo;
    }
    return 1;
}

int listarQtdTurista(Excursao *lista, char nomeExcursao[]) {
    Excursao *aux = lista;
    int contador = 0;
    int i = 1;

    while (aux != NULL && strcmp(aux->nomeDoGrupo, nomeExcursao) != 0) {
        i++;
        aux = aux->proximo;
    }

    if (aux == NULL) {
        return 0;
    } else {
        printf("\n >> Excursao %d << \n", i);
        printf("Grupo: %s\n", aux->nomeDoGrupo);
        printf("Data: %s\n", aux->data);
        printf("Numero de dias: %d\n", aux->numeroDeDias);
        printf("Destino: %s\n", aux->destino);
        printf("Numero de turistas: %d\n", aux->quantDeTuristas);
        printf("\n==============================\n");
        printf("\nLISTA DE TURISTAS:\n");

        Turista *turistaAtual = aux->turistas;

        while (turistaAtual != NULL) {
            contador++;
            printf("Nome: %s\nCPF: %s\n\n", turistaAtual->nome, turistaAtual->cpf);
            turistaAtual = turistaAtual->proximo;
        }

        printf("Numero de turistas inscritos nesta excursao: %d\n", contador);
    }

    return 1;
}


int main(){
    Excursao *lista = NULL;
    int escolha;

    do{
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

        printf("\n\n");

        switch (escolha){
            case 1: {
                char nome[100], data[11], destino[100];
                int dias;
                
                printf("\nInsira o nome do grupo: ");
                getchar();
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("\n\n");
                printf("Insira a data da excursao (formato DD/MM/AAAA): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                
                getchar();
                printf("\n\n");
                printf("Insira o destino da excursao: ");
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';
                
                printf("\n\n");
                printf("Insira a quantidade de dias da excursao: ");
                scanf("%d", &dias);
                getchar();
                
                int result = criarExcursao(&lista, nome, data, dias, destino);
                
                if (result == 0) {
                    printf("\n\nNao foi possivel alocar memoria para a excursao\n\n");
                } else {
                    printf("\n\nA excursao foi criada com sucesso!\n\n");
                }
                break;
            }
            case 2: {
                if(lista == NULL){
                    printf("\nNao ha excursoes para remover.\n\n");
                } else {
                    char nome[100];

                    printf("\nInsira o nome do grupo: ");
                    getchar();
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    int result = removerExcursao(&lista, nome);
                    if(result == 0)
                        printf("\nA excursao nao foi encontrada.\n\n");
                    else
                        printf("\nA excursao foi removida com sucesso!\n\n");
                }
                break;
            }
            case 3:{
                if(lista == NULL){
                    printf("\nNao ha excursoes para adicionar turistas\n\n"); 
                } else {
                    char cpf[15], nomeExcursao[100], nomeTurista[100];

                    getchar();
                    printf("\nInsira o nome da excursao: ");
                    fgets(nomeExcursao, sizeof(nomeExcursao), stdin);
                    nomeExcursao[strcspn(nomeExcursao, "\n")] = '\0';

                    printf("\n\n");
                    printf("Insira o nome do turista: ");
                    fgets(nomeTurista, sizeof(nomeTurista), stdin);
                    nomeTurista[strcspn(nomeTurista, "\n")] = '\0';

                    printf("\n\n");
                    printf("Insira o CPF do turista: ");
                    scanf("%s", cpf);
                    
                    int result = inserirTurista(&lista, nomeExcursao, nomeTurista, cpf);
                    if(result == 0)
                        printf("\nEsta excursao nao foi encontrada.\n\n");
                    else
                        printf("\nTurista adicionado com sucesso!\n\n");
                }
                break;
            }
            case 4: {
                if (lista == NULL){
                    printf("\nNao ha excursoes para remover turistas\n\n");    
                } else {
                    char cpf[15];

                    printf("\n\n");
                    printf("Insira o CPF do turista: ");
                    scanf("%s", cpf);

                    int result = removerTurista(&lista, cpf);

                    if (result == 0)
                        printf("\nNao foi possivel remover o turista \n\n");
                    else
                        printf("\nTurista removido com sucesso!\n\n");
                }
                break;
            }   
            case 5:{
                if (lista == NULL)
                    printf("\nAinda nao ha excursoes cadastradas!\n\n");
                else 
                    listarExcursoes(lista);
                    
                break;
            }
            case 6:{
                if(lista == NULL){
                    printf("\nAinda nao ha excursoes cadastradas!\n\n");
                } else {
                    char nomeExcursao[100];

                    printf("\nInsira o nome da excursao: ");
                    getchar();
                    fgets(nomeExcursao, sizeof(nomeExcursao), stdin);
                    nomeExcursao[strcspn(nomeExcursao, "\n")] = '\0';

                    int result = listarQtdTurista(lista, nomeExcursao);
                    if(result == 0)
                        printf("\nExcursao nao encontrada\n\n");
                }
                break;
            }
            case 7:
                printf("\nEncerrando o programa...\n\n");
                break;
            default:
                printf("\n\nOpcao invalida.\n\n");
        }
        
    }while(escolha != 7);
}