//estrutura para armazenar os dados do contato
typedef struct contato{
    int codigo;
    char nome[55];
    char empresa[55];
    char departamento[55];
    char telefone[15];
    char celular[15];
    char email[55];
}CONTATO;

typedef struct elemento* Lista;

//funcao para criar a lista
Lista *criaLista();

//funcao para apagar a lista
void apagaLista(Lista *li);

//funcao para verificar o tamanho da lista
int tamLista(Lista *li);

//funcao para verificar se a lista esta vazia
int listaVazia(Lista *li);

//funcao para verificar se ja existe um contato na lista com o mesmo codigo do contato a ser inserido
int existe_codigo(Lista *li, int cod);

//funcao que insere o contato
int insere_lista_ordenada(Lista *li, CONTATO c);

//funcao que remove o contato da lista
int remove_lista(Lista *li, int cod);

//funcao para consultar todos os contatos da lista
int consulta_lista_total(Lista *li);

//funcao para consultar o contato pelo codigo
int consulta_lista_cod(Lista *li, int cod, CONTATO *c);

//funcao para consultar contatos pelo nome
void consulta_lista_nome(Lista *li, char nome[55]);

//funcao para coletar dados do teclado
CONTATO coletarDados();

//funcao para editar um contato da lista
void editarLista(Lista *li, int cod, CONTATO c);

//funcao para salvar a lista em um arquivo binario
void salvarLista(Lista *li, char arquivo[25]);

//funcao para ler a lista de um arquivo binario
void carregarLista(Lista *li, char arquivo[25]);
