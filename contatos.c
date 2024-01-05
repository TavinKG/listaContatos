#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contatos.h"
//estrutura elemento que armazena os dados e o ponteiro para o proximo elemento
struct elemento{
    CONTATO dados;
    struct elemento *prox;
};
typedef struct elemento ELEM;

//funcao para criar a lista
Lista *criaLista(){
    Lista *li;
    //alocacao dinamica para o ponteiro de ponteiro
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}

//funcao para apagar a lista
void apagaLista(Lista *li){
    if(li != NULL){
        ELEM *no;
        while((*li) != NULL){
            //para apagar um elemento da lista, o ponteiro de ponteiro passa a apontar para o proximo ate que aponte para NULL
            no = *li;
            *li = (*li)->prox;
            //apos o ponteiro ser apontado para um proximo elemento, o elemento atual e liberado
            free(no);
        }
        //o ponteiro para ponteiro é liberado
        free(li);
    }
}

int tamLista(Lista *li){
    if(li == NULL){
        return 0;
    }
    int acum = 0;
    ELEM *no = *li;
    //enquanto o ponteiro nao apontar para NULL, ira incrementar o numero de contatos na lista
    while(no != NULL){
        acum++;
        no = no->prox;
    }
    return acum;
}

int listaVazia(Lista *li){
    if(li == NULL){
        return 1;
    }
    //quando o ponteiro inicial aponta para NULL indica que a lista esta vazia
    if(*li == NULL){
        return 1;
    }
    return 0;
}

//funcao para verificar se o codigo a ser inserido ja existe
int existe_codigo(Lista *li, int cod){
    ELEM *no = *li;
    //enquanto nao chegar ao final da lista, o algoritmo ira comparar o codigo a ser inserido com o atual codigo da lista
    while(no != NULL){
        //se encontrar, retorna 1 e sai da funcao
        if(no->dados.codigo == cod){
            return 1;
        }
        no = no->prox;
    }
    return 0;
}

int insere_lista_ordenada(Lista *li, CONTATO c){
    if(li == NULL){
        return 0;
    }
    //se existir um codigo igual ao inserido, a funcao retorna 1 e entao ele entra nesse if e retorna 0
    if(existe_codigo(li, c.codigo)){
        return 0;
    }
    //elemento sendo alocado
    ELEM *no = (ELEM*) malloc(sizeof(ELEM));
    if(no == NULL){
        return 0;
    }
    //elemento recebendo os dados
    no->dados = c;
    //se a lista for vazia, ele ira apontar para NULL e o ponteiro inicial apontara para este elemento
    if(listaVazia(li)){
        no->prox = (*li);
        *li = no;
        return 1;
    }else{
        //caso contrario ele procurara a posicao correta a ser inserido e ira passar a apontar para o sucessor de seu antecessor
        //e seu antecessor ira apontar para o elemento recem inserido
        ELEM *ant, *atual = *li;
        while(atual != NULL && atual->dados.codigo < c.codigo){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = ant->prox;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista *li, int cod){
    if(li == NULL){
        return 0;
    }
    ELEM *ant, *no = *li;
    //o algoritmo procura o contato que corresponde ao codigo
    while(no != NULL && no->dados.codigo != cod){
        ant = no;
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }
    //ao encontrar, se estiver no inicio o ponteiro inicial apenas passa a apontar para o elemento sucessor ao removido
    if(no == *li){
        *li = no->prox;
    }else{
        //senao, o antecessor do elemento removido passa a apontar para o sucessor do elemento removido
        ant->prox = no->prox;
    }
    //aqui ele é liberado
    free(no);
    return 1;
}

int consulta_lista_total(Lista *li){
    if(li == NULL){
        return 0;
    }
    ELEM *no = *li;
    //enquanto a lista nao chegar ao final, o codigo e nome correspondente ao elemento atual sao exibidos
    while(no != NULL){
        printf("\nCodigo: %d", no->dados.codigo);
        printf("\nNome: %s\n", no->dados.nome);
        no = no->prox;
    }
    return 1;
}

int consulta_lista_cod(Lista *li, int cod, CONTATO *c){
    if(li == NULL){
        return 0;
    }
    ELEM *no = *li;
    //procura pelo contato correspondente ao codigo
    while(no != NULL && no->dados.codigo != cod){
        no = no->prox;
    }
    if(no == NULL){
        return 0;
    }else{
        //os dados sao passados para a variavel c que ira exibi-los
        *c = no->dados;
        return 1;
    }
}

void consulta_lista_nome(Lista *li, char nome[55]){
    //transformando o nome do parametro em minusculo
    strlwr(nome);
    ELEM *no = *li;
    char nomemin[55];
    while(no != NULL){
        //passando o nome do elemento para outra variavel e depois transforma para minusculo
        strcpy(nomemin, no->dados.nome);
        strlwr(nomemin);
        //se os nomes forem iguais, os dados sao retornados
        if(strcmp(nome, nomemin) == 0){
            printf("\n\nCodigo : %d", no->dados.codigo);
            printf("\n\nNome: %s", no->dados.nome);
            printf("\nEmpresa: %s", no->dados.empresa);
            printf("\nDepartamento: %s", no->dados.departamento);
            printf("\nTelefone: %s", no->dados.telefone);
            printf("\nCelular: %s", no->dados.celular);
            printf("\nEmail: %s\n", no->dados.email);
            no = no->prox;
        }else{
            //senao ele passa para o proximo elemento
            no = no->prox;
        }
    }
}

//funcao utilizando fgets para coletar os dados em strings
CONTATO coletarDados(){
    CONTATO c;
    printf("Digite o codigo: ");
    scanf("%d", &c.codigo);
    fflush(stdin);
    printf("Digite o nome: ");
    fgets(c.nome, 55, stdin);
    fflush(stdin);
    printf("Digite o nome da empresa: ");
    fgets(c.empresa, 55, stdin);
    fflush(stdin);
    printf("Digite o departamento: ");
    fgets(c.departamento, 55, stdin);
    fflush(stdin);
    printf("Digite o telefone: ");
    fgets(c.telefone, 15, stdin);
    fflush(stdin);
    printf("Digite o celular: ");
    fgets(c.celular, 15, stdin);
    fflush(stdin);
    printf("Digite o email: ");
    fgets(c.email, 55, stdin);
    return c;
}

void editarLista(Lista *li, int cod, CONTATO c){
    ELEM *no = *li;
    //buscando o contato correspondente ao codigo
    while(no != NULL && no->dados.codigo != cod){
        no = no->prox;
    }
    //atualizando os dados do respectivo contato
    no->dados = c;
    printf("\n\nLista editada com sucesso!\n");
}

void salvarLista(Lista *li, char arquivo[25]){
    //abrindo o arquivo no modo de escrita
    FILE* f = fopen(arquivo, "wb");

    if(f == NULL){
        printf("Nao foi possivel abrir o arquivo para escrita.\n");
        return;
    }
    ELEM *no = *li;

    //enquanto a lista nao chegar ao fim, os contatos serao inseridos com fwrite e passara para o proximo
    while(no != NULL){
        fwrite(&(no->dados), sizeof(CONTATO), 1, f);
        no = no->prox;
    }
    fclose(f);
}

void carregarLista(Lista *li, char arquivo[25]){
    //abertura do arquivo no modo de leitura
    FILE* f = fopen(arquivo, "rb");
    if(f == NULL){
        printf("Nao foi possivel abrir o arquivo para leitura.\n");
        return;
    }
    CONTATO c;
    int x;
    //enquanto a leitura do contato no arquivo retornar 1, ele ira ser inserido na lista
    while(fread(&c, sizeof(CONTATO), 1, f) == 1){
        x = insere_lista_ordenada(li, c);
    }
    fclose(f);
}
