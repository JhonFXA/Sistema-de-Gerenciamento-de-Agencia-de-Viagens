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
        printf("Esta excursao nao foi encontrada.\n");
        return 0;
    }
    Turista *novoTurista = (Turista*)malloc(sizeof(Turista));

    if (novoTurista == NULL){
        printf("Memoria nao alocada.\n");
        return 0;
    }
    strcpy(novoTurista -> nome,nomeTurista);
    strcpy(novoTurista -> cpf,cpf);
    novoTurista -> proximo = aux -> turistas;
    aux -> turistas = novoTurista;
    return 1;
}

int removerTurista(Excursao **lista, char cpf[]){
    Excursao *aux = *lista;
    while(aux != NULL){
        Turista *anterior = NULL;
        while(aux->turistas != NULL){
            if(strcmp(aux->turistas->cpf, cpf) == 0){
                if(anterior == NULL){
                    aux->turistas = aux->turistas->proximo;
                } else {
                    anterior->proximo = aux->turistas->proximo;
                }
                free(aux->turistas);
                return 1;
            }
            anterior = aux->turistas;
            aux->turistas = aux->turistas->proximo;
        }
        aux = aux->proximo;
    }
    printf("Nao existe turista com este CPF.\n");
    return 0;
}

int listarExcursoes(Excursao **lista){
    Excursao *aux = *lista;
    int i=1;
    
    if(aux==NULL){
        printf("\nAinda nao ha excursoes cadastradas!\n\n");
        return 0;
    }else{
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
    }
    return 1;
}

int listarQtdTurista(Excursao **lista,char nomeExcursao[]){
    Excursao *aux = *lista;
    int contador = 0;
    int i=1;
    
    if(aux==NULL){
        printf("\nAinda nao ha excursoes cadastradas!\n\n");
        return 0;
    }else{
        while(aux != NULL && strcmp(aux->nomeDoGrupo,nomeExcursao) != 0){
            i++;
            aux = aux->proximo;
        }
        if (aux == NULL){
            printf("\n Excursao nao encontrada \n");
            return 0;
        }else{
            printf("\n >> Excursao %d << \n", i);
            printf("Grupo: %s\n", aux->nomeDoGrupo);
            printf("Data: %s\n", aux->data);
            printf("Numero de dias: %d\n",aux->numeroDeDias);
            printf("Destino: %s\n", aux->destino);
            printf("Numero de turistas: %d\n", aux->quantDeTuristas);
            printf("\n==============================\n");
            printf("\nLISTA DE TURISTAS:\n");
            while (aux -> turistas != NULL){
                contador++;
                printf("Nome: %s\nCPF: %s\n\n",aux->turistas->nome, aux->turistas->cpf);
                aux -> turistas = aux -> turistas -> proximo;
            }
            printf("Numero de turistas inscritos nesta excursao: %d\n", contador);
        }
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
                
                printf("Insira o nome do grupo: ");
                getchar();
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                
                printf("\nInsira a data da excursao (formato DD/MM/AAAA): ");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0';
                
                printf("\nInsira o destino da excursao: ");
                getchar();
                fgets(destino, sizeof(destino), stdin);
                destino[strcspn(destino, "\n")] = '\0';
                
                printf("\nInsira a quantidade de dias da excursao: ");
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
                    printf("Nao ha excursoes para remover.\n\n");
                } else {
                    char nome[100];

                    printf("Insira o nome do grupo: ");
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
            case 3:

                break;
            case 4: {
                if (lista == NULL){
                    printf("Não ha excursoes para remover turistas");    
                
                } else {
                    char nomeExcursao[100], cpf[15];

                    printf("Insira o nome da excursao: ");
                    getchar();
                    fgets(nomeExcursao, sizeof(nomeExcursao), stdin);
                    nomeExcursao[strcspn(nomeExcursao, "\n")] = '\0';

                    printf("Insirao CPF do turista: ");
                    fgets(cpf, sizeof(cpf),stdin);
                    cpf[strcspn(cpf), "\n"] = '0';

                    int result = removerTurista(&lista, nomeExcursao, cpf);

                    if (result == 0)
                        printf("Nao foi possivel remover o turista \n\n");
                }
                break;
            }

                
            case 5:
                break;
            case 6:
                break;
            default:
                printf("Opcao invalida.\n\n");
        }
        
    }while(escolha != 7);
}