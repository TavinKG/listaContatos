#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contatos.h"

int main()
{
    //variaveis utilizadas para as chamadas da funcoes e manipulacao do menu
    int x = 0, m = 1;
    int codigo;
    char nome[55];
    CONTATO c;


    Lista *li;
    li = criaLista();
    //lista no arquivo sendo carregada
    carregarLista(li, "lista_contatos.bin");


    //do while para exibir o menu
    do{
        system("cls");
        printf("\t\tMENU");
        printf("\n\n[1] Inserir novo contato");
        printf("\n[2] Exibir todos os contatos");
        printf("\n[3] Buscar contato pelo codigo");
        printf("\n[4] Buscar contato pelo nome");
        printf("\n[5] Editar um contato");
        printf("\n[6] Remover contato");
        printf("\n[7] Verificar tamanho da lista");
        printf("\n[8] Encerrar programa");
        printf("\n\nEscolha uma das opcoes acima: ");
        scanf("%d", &x);
        system("cls");
        //switch case para alternar entre as diversas opcoes
        switch(x){
            case 1:
                //para inserir um contato, sao coletados seus dados e depois щ realizada a inserчуo
                c = coletarDados();
                x = insere_lista_ordenada(li, c);
                if(x){
                    printf("\nInserido ordenadamente com sucesso!");
                }else{
                    printf("\nNao foi possivel inserir ordenadamente.");
                }
                break;
            case 2:
                //aqui щ realizada a consulta total
                x = consulta_lista_total(li);
                if(!x){
                    printf("Nao foi possivel consultar a lista!");
                }
                system("pause");
                break;
            case 3:
                //aqui щ realizada a consulta pelo codigo
                printf("Digite o codigo do contato para busca: ");
                scanf("%d", &codigo);
                x = consulta_lista_cod(li, codigo, &c);
                if(x){
                    printf("\n\nCodigo: %d:", c.codigo);
                    printf("\n\nNome: %s", c.nome);
                    printf("\nEmpresa: %s", c.empresa);
                    printf("\nDepartamento: %s", c.departamento);
                    printf("\nTelefone: %s", c.telefone);
                    printf("\nCelular: %s", c.celular);
                    printf("\nEmail: %s\n", c.email);
                }else{
                    printf("\nCodigo %d nao encontrado.\n", codigo);
                }
                system("pause");
                break;
            case 4:
                //aqui щ utilizado fgets para armanezar o nome a ser consultado
                fflush(stdin);
                printf("Digite o nome que deseja buscar: ");
                fgets(nome, 55, stdin);
                consulta_lista_nome(li, nome);
                system("pause");
                break;
            case 5:
                //para editar primeiro щ armazenado o codigo a ser editado
                printf("Digite o codigo do contato que deseja editar: ");
                scanf("%d", &codigo);
                //apos, a funcao de consulta de dados exibe os dados do contato
                x = consulta_lista_cod(li, codigo, &c);
                if(x){
                    printf("\n\nCodigo: %d:", c.codigo);
                    printf("\n\nNome: %s", c.nome);
                    printf("\nEmpresa: %s", c.empresa);
                    printf("\nDepartamento: %s", c.departamento);
                    printf("\nTelefone: %s", c.telefone);
                    printf("\nCelular: %s", c.celular);
                    printf("\nEmail: %s\n", c.email);
                }else{
                    printf("\nCodigo %d nao encontrado.\n", codigo);
                }
                printf("\n\nDeseja realmente editar este contato?");
                printf("\n[1] Sim\n[0] Nao: ");
                scanf("%d", &x);
                if(x){
                    printf("\n\n\n");
                    //por ultimo, os novos dados sao coletados e o contato щ editado
                    c = coletarDados();
                    editarLista(li, codigo, c);
                }
                system("pause");
                break;
            case 6:
                //para remover primeiro щ armazenado o codigo correspondente
                printf("Digite o codigo do contato que deseja remover: ");
                scanf("%d", &codigo);
                //apos щ realizada a consulta pelo codigo e exibidos os dados do contato
                x = consulta_lista_cod(li, codigo, &c);
                if(x){
                    printf("\n\nCodigo: %d", c.codigo);
                    printf("\n\nNome: %s", c.nome);
                    printf("\nEmpresa: %s", c.empresa);
                    printf("\nDepartamento: %s", c.departamento);
                    printf("\nTelefone: %s", c.telefone);
                    printf("\nCelular: %s", c.celular);
                    printf("\nEmail: %s\n", c.email);
                }else{
                    printf("\nCodigo %d nao encontrado.\n", codigo);
                }
                printf("\n\nDeseja realmente excluir este contato?");
                printf("\n[1] Sim\n[0] Nao: ");
                scanf("%d", &x);
                //se optar por sim, o contato sera removido
                if(x){
                    x = remove_lista(li, codigo);
                    if(x){
                        printf("\nRemovido elemento com sucesso!\n");
                    }else{
                        printf("\nNao foi possivel remover o elemento.\n");
                    }
                }
                system("pause");
                break;
            case 7:
                //o algoritmo retorna o tamanho da lista
                x = tamLista(li);
                printf("O tamanho da lista e: %d\n", x);
                system("pause");
                break;
            case 8:
                //aqui a lista щ salva em um arquivo binario e apos isso щ apagada
                salvarLista(li, "lista_contatos.bin");
                apagaLista(li);
                m = 0;
                break;
            default:
                //caso outro numero seja digitado essa mensagem щ exibida
                printf("ERRO: Opcao incorreta!");
                system("pause");
        }
    }while(m);

}
