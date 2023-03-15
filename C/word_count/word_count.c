/* this program reads a text from a file, puts all its words into a binary tree,
   keeps the frequency of how often each word appears on the text, and then organizes
   the words into an array of linked lists where the index is the frequency in which 
   that specif word appears in the text
   
   the program reads a file whose name must be given as a command line argument and the text
   must be ASCII compatible, so Enlish text is preferred. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*strcut da arvore de busca binaria que armazena a frequencia de cada palavra e a palavra em si. Temos
tambem os ponteiros para os nos da esquerda e direita da arvore asism como o ponteiro para o vetor
de listas ligadas*/
 typedef struct arvore {
    int freq;
    char palavra[30];
    struct arvore *esquerda;
    struct arvore *direita;
    struct arvore *proximo;
} arvore;

/*variavel que armazena a frequencia maxima que ocorre no texto, ela sera usada para callocar
apenas a quantidade necessaria de memoria no vetor de listas ligadas*/
int max = 1;

arvore *novo_node_arvore (char *palavra_atual);
arvore *insere (arvore *raiz, char *palavra_atual);
void organiza (arvore *raiz, arvore **cabeca);
void imprime (arvore **cabeca, int num);

int main(int argc, char **argv)
{
    char palavra_atual[30];
    arvore *raiz = NULL;
    arvore **cabeca;

    int num = -1, i = 0, j = 0 , k = 0, tamanho;

    FILE *texto = fopen(argv[1], "r");

    /*fscanf eh igual 1 enquanto houver palavras a serem lidas
    no arquivo de texto*/
    while (fscanf (texto, "%30s", palavra_atual) == 1)
    {

        /*verifica se o caractere nao eh uma letra*/
        if (isalpha(palavra_atual[0]) == 0 && palavra_atual[0] != '(' && palavra_atual[0] != 34)
            continue;
        
        tamanho = strlen(palavra_atual);

        
        for (i = 0; i < tamanho; i++)
        {
            /*caso especial de palavras que comecam com parenteses ou aspas*/
            if (palavra_atual[i] == '(' || palavra_atual[i] == 34)
            {
                /*percorre a palavra para saber se estamos lidando com um 
                parentese ou um parentese e aspas*/
                k = 0;
                while (isalpha(palavra_atual[k]) == 0 && k < tamanho)
                    k++;

                /*desloca as letras para a esquerda do vetor*/
                for (j = 0; j < tamanho - k; j++)
                    palavra_atual[j] = palavra_atual[j + k];

                /*percorre a palvra para adicionar o vetor nulo ao fim da mesma, necessario 
                ja que a palavra foi deslocada para a esquerda e podemos ter letras repetidas*/
                j = 0;
                while (palavra_atual[j] != ')' && palavra_atual[j] != 34 && j < strlen(palavra_atual) - k)
                    j++;

                palavra_atual[j] = '\0';
            }

            /*vai para a proxima letra se a palavra tiver tracos (-) ou aspas simples (')*/
            if (palavra_atual[i] == '-' || palavra_atual[i] == 39)
                continue;

            /*se a letra for maiuscula, converte para minuscula*/
            if (isupper(palavra_atual[i]) != 0)
                palavra_atual[i] = tolower(palavra_atual[i]);

            /*se o caractere nao for uma letra, adiciona o carcatere NULL
            e tambem verificamos para pontos e virgulas*/
            if (isalpha(palavra_atual[i]) == 0)
                palavra_atual[i] = '\0';
        }
        
        /*se a "palavra" tiver só uma letra, ela nao sera adicionada na arvore por
        nao ser uma palavra*/
        if (strlen(palavra_atual) == 1 || palavra_atual[0] == '\0')
            continue;

        /*insere a palavra na arvore*/
        raiz = insere(raiz, palavra_atual);
    }

    /*aloca memoria para o vetor duplo "cabeca" de tamanho igual a palavra com a maior
    frequencia no texto, denotada por "max"*/
    cabeca = calloc((max + 1), sizeof(arvore));

    /*organiza as palavras no vetor de listas ligadas*/
    organiza(raiz, cabeca);

    /*pede ao usuario para digitar frequencias, se for digitar 0, o programa termina*/
    while (num != 0)
    {
        printf("Type the frequency (0 to exit): ");
        scanf("%d", &num);

        /*para imprimir, "num" precisa ser igual ou menor do que a frequencia maxima que
        aparece no texto e o index tem que ser diferente de NULL, caso contrario, nao
        existe palavra no texto com a frequencia dada*/
        if (num <= max && cabeca[num] != NULL)
            imprime(cabeca, num);
        else if (num == 0)
            break;
        else
            printf("There are not words in the text with this frequency.\n");

        printf("\n");
    }

    /*libera memoria para o sistema e fecha o arquivo de texto aberto*/
    free(cabeca);
    fclose(texto);
    return 0;
}

/*funcao que cria um novo node para a arove, armazena a frequencia e copia a palavra
para a arvore*/
arvore *novo_node_arvore(char *palavra_atual)
{
    arvore *novo_node = calloc(1, sizeof(arvore));
    novo_node->freq++;
    strcpy(novo_node->palavra, palavra_atual);
    novo_node->esquerda = NULL;
    novo_node->direita = NULL;

    return novo_node;
}

/*funcao que insere o node na arvore na posicao certa, usando "strcmp" para verificar
se temos que adicionar a palavra no lado direito ou esquerdo do node*/
arvore *insere(arvore *raiz, char *palavra_atual)
{
    if (raiz == NULL)
        raiz = novo_node_arvore(palavra_atual);
    /*se "strcmp" for igual a 0, a palavra eh igual e apenas aumentamos sua frequencia no
    texto e verificamos sua frequencia com a frequencia "max" atual*/
    else if (strcmp(palavra_atual, raiz->palavra) == 0)
    {
        raiz->freq++;
        if (raiz->freq > max)
            max = raiz->freq;
    }
    /*se a palavra atual vier depois da palavra na raiz, colocamos ela na raiz 
    da esquerda*/
    else if (strcmp(palavra_atual, raiz->palavra) > 0)
        raiz->esquerda = insere(raiz->esquerda, palavra_atual);
    /*se a palavra atual vier antes da palavra na raiz, colocamos ela na raiz 
    da direita*/
    else if (strcmp(palavra_atual, raiz->palavra) < 0)
        raiz->direita = insere (raiz->direita, palavra_atual);

    return raiz;
}

/*funcao que percorre a arvore em modo "in order" do menor ao maior*/
void organiza (arvore *raiz, arvore **cabeca)
{
    arvore *temp = NULL;

    if (raiz != NULL)
    {
        organiza (raiz->esquerda, cabeca);

        /*insere o endereco da raiz no indice do vetor de listas ligadas*/
        temp = raiz;
        temp->proximo = cabeca[raiz->freq];
        cabeca[raiz->freq] = temp;

        organiza (raiz->direita, cabeca);
    }
}

/*imprime todas as palavras em ordem alfabetica com a frequencia dada pelo usuario*/
void imprime (arvore **cabeca, int num)
{
    int cont = 0;

    arvore *temp = cabeca[num];

    while (temp != NULL)
    {
        printf("%d- %s\n", cont + 1, temp->palavra);
        cont++;
        temp = temp->proximo;
    }

    printf("\nThere are %d words with frequency %d in the text. \n", cont, num);
}
