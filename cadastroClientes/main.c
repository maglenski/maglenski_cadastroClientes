//Autor: Marcelo Glenski
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int num;
    //int num2;
    //float num3;
    //char letra[1];
    struct Node *prox;
};
typedef struct Node node;

void inicia(node *LISTA);
int menu(void);
void opcao(node *LISTA, int op);
node *criaNo();
void insereFim(node *LISTA);
void insereInicio(node *LISTA);
void exibe(node *LISTA);
void libera(node *LISTA);
void removeFim(node *LISTA);
void inserePosicao(node *LISTA);
void removePosicao(node *LISTA);
void limpaTela();
void verificaMemoria(node *LISTA);
int tamanhoLista(int imprime, node *LISTA);


int main(void)
{
    node *LISTA = (node *) malloc(sizeof(node));

    if(!LISTA)
    {
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    inicia(LISTA);
    int opt;

    do
    {
        opt=menu();
        limpaTela();
        opcao(LISTA,opt);
    }
    while(opt);

    free(LISTA);
    return 0;
}

void inicia(node *LISTA)
{
    LISTA->prox = NULL;
}

int menu(void)
{
    int opt;

    printf("Escolha a opcao\n");
    printf("0. Sair\n");
    printf("1. Exibir lista\n");
    printf("2. Adicionar inicio\n");
    printf("3. Adicionar final\n");
    printf("4. Remover final\n");
    printf("5. Adicionar na posicao\n");
    printf("6. Remover da posicao\n");
    printf("7. Zerar lista\n");
    printf("8. Tamanho da lista\n");
    printf("Opcao: ");
    scanf("%d", &opt);

    return opt;
}

void opcao(node *LISTA, int op)
{
    switch(op)
    {
    case 0:
        libera(LISTA);
        break;

    case 1:
        exibe(LISTA);
        break;

    case 2:
        insereInicio(LISTA);
        break;

    case 3:
        insereFim(LISTA);
        break;

    case 4:
        removeFim(LISTA);
        break;

    case 5:
        inserePosicao(LISTA);
        break;

    case 6:
        removePosicao(LISTA);
        break;

    case 7:
        inicia(LISTA);
        break;

    case 8:
        tamanhoLista(0, LISTA);
        break;

    default:
        printf("Comando invalido\n\n");
    }
}

int vazia(node *LISTA)
{
    if(LISTA->prox == NULL)
        return 1;
    else
        return 0;
}


void insereFim(node *LISTA)
{
    node *novo=(node *) malloc(sizeof(node));
    verificaMemoria(novo);

    printf("Primeiro numero no fim: ");
    scanf("%d", &novo->num);
    //printf("Segundo numero no fim: ");
    //scanf("%d", &novo->num2);
    //getc(stdin);
    //printf("Primeira letra no fim: ");
    //scanf("%c", &novo->letra);

    novo->prox = NULL;

    if(vazia(LISTA))
        LISTA->prox=novo;
    else
    {
        node *tmp = LISTA->prox;

        while(tmp->prox != NULL)
        {
            tmp = tmp->prox;
        }

        tmp->prox = novo;
    }
}

void insereInicio(node *LISTA)
{
    node *novo=(node *) malloc(sizeof(node)); //Cria o novo no
    verificaMemoria(novo);

    printf("Primeiro numero no inicio: ");
    scanf("%d", &novo->num);
    //printf("Segundo numero no inicio: ");
    //scanf("%d", &novo->num2);
    //getc(stdin);
    //printf("Primeira letra no inicio: ");
    //scanf("%c", &novo->letra);
    limpaTela();

    node *oldHead;          //Ponteiro para armazenar endereço da cabeca da lista.
    oldHead = LISTA->prox;  //Salva endereço apontado pela cabeca da lista para nao ser perdida.

    LISTA->prox = novo;     //Cabeca da lista aponta agora para novo elemento.
    novo->prox = oldHead;   //Novo elemento aponta para onda a cabeca da lista apontava.
}

void exibe(node *LISTA)
{
    if(vazia(LISTA))
    {
        printf("Lista vazia!\n");
        return;
    }

    node *tmp;
    tmp = LISTA->prox;

    printf("Lista contem: |");
    while(tmp != NULL)
    {
        //printf("%d-%d-%c|", tmp->num, tmp->num2, tmp->letra[0]);
        printf("%d|", tmp->num);
        tmp = tmp->prox;
    }
    printf("\n");
}

void libera(node *LISTA)
{
    if(!vazia(LISTA))
    {
        node *proxNode,
             *atual;

        atual = LISTA->prox;
        while(atual != NULL)
        {
            proxNode = atual->prox;
            free(atual);
            atual = proxNode;
        }
    }
}

void removeFim(node *LISTA)
{
    if(vazia(LISTA))
    {
        printf("Lista vazia!\n");
        return;
    }

    node *tmp = LISTA->prox;
    node *novoUltimo;

    while(tmp->prox != NULL)
    {
        novoUltimo = tmp;
        tmp = tmp->prox;
    }
    if(tmp == LISTA->prox)
    {
        free(tmp);
        inicia(LISTA);
    }
    else
    {
        novoUltimo->prox = NULL;
    }
}

void inserePosicao(node *LISTA)
{
    int contaPosicao = 0;
    int posicao;
    node *novo=(node *) malloc(sizeof(node)); //Cria o novo no
    verificaMemoria(novo);

    printf("Digite a pocicao a ser incluida: ");
    scanf("%d", &posicao);
    printf("Insira na posicao \"%d\" o numero a ser armazenado: ", posicao);
    scanf("%d", &novo->num);

    posicao = (posicao - 1);
    if((tamanhoLista(1, LISTA) <  posicao) || (posicao == -1) || ((vazia(LISTA)) && (posicao > 0)))
    {
        printf("Posicao invalida!\n");
        return;
    }

    node *posicaoAnterior;
    node *tmp = LISTA->prox;

    while(contaPosicao < posicao)
    {
        contaPosicao++;
        posicaoAnterior = tmp;
        tmp = tmp->prox;
    }
    if(posicao == 0)
    {
        LISTA->prox = novo;
        novo->prox = tmp;
    }
    else
    {
        posicaoAnterior->prox = novo;
        novo->prox = tmp;
    }
}

void removePosicao(node *LISTA)
{
    int contaPosicao = 0;
    int posicao;

    printf("Digite a pocicao a ser removida: ");
    scanf("%d", &posicao);
}

void limpaTela()
{
    system("cls");
}

void verificaMemoria(node *LISTA)
{
    if(!LISTA)
    {
        printf("Sem memoria disponivel!");
        exit(1);
    }
}

int tamanhoLista(int imprime, node *LISTA)
{
    int tamanhoLista = 0;
    node *novo=(node *) malloc(sizeof(node)); //Cria o novo no
    verificaMemoria(novo);

    if(vazia(LISTA))
    {
        //printf("Lista vazia!\n");
        return;
    }
    node *tamanho = LISTA->prox;

    while(tamanho->prox != NULL)
    {
        tamanhoLista++;
        tamanho = tamanho->prox;
    }
    if(imprime == 0)
    {
        printf("Tamanho da lista: %d\n", (tamanhoLista + 1));
    }
    return (tamanhoLista + 1);
}
