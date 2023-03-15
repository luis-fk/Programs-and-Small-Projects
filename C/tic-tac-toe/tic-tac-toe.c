/*A ideia basica desse programa eh que a maquina ira em todos os turnos verificar
cada bolinha colocada pelo oponente e verificar todos os eixos possiveis para cada
uma delas para analisar se existe possibilidade de vitoria do oponente no proximo turno.

Caso exista possibilidade de vitoria do oponente no proximo turno, este programa ira
colocar uma bolinha no local apropriado para evitar a vitoria.

Caso nao exista possibilidade de vitoria do oponente no proximo turno, este programa
ira fazer seu proprio jogo, que eh feito atraves da procura de um eixo onde nao ha
bolinhas do oponente. Caso o oponente obstrua um desses eixos, o programa ira procurar
outro eixo livre e continuar sua jogada.

De maneira resumida, esse programa ira fazer seu próprio jogo e ao mesmo tempo ira
impedir de que o jogador ganhe o jogo quando necessario.

O programa nao eh perfeito, mas ele oferece um nivel de desafio razoavel.*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int escolheJogada (int ***tab, int n, int cor, int *lin, int *col);
int jogada_dependente (int ***tab, int cor, int n, int *x, int *y, int z);
int jogada_independente (int ***tab, int cor, int n, int *lin, int *col, int z, int parametro);
int gravidade (int ***tab, int cor, int n, int *x, int *y, int z);
int jogadas (int ***tab, int n);
void print_tab (int ***tab, int n);
int vitoria (int ***tab, int cor, int n, int x, int y, int z, int parametro);
int colocar_bolinha (int ***tab, int cor, int n, int jogada, int *x, int *y, int z);

int main (){
    int ***tab, n, cor, cor_h, fim, x, y, z = 0;

    printf("Size of the board: ");
    scanf("%d", &n);

    /*usando calloc para iniciar todo o tabuleiro com 0*/
    tab = (int***)calloc(n, sizeof(int**));
    for (x = 0; x < n; x++){
        tab[x] = (int**)calloc(n, sizeof(int*));

        for (y = 0; y < n; y++)
            tab[x][y] = (int*)calloc(n, sizeof(int));
    }

    printf("Chose your color (blue: -1 or black: 1): ");
    scanf("%d", &cor_h);
    /*temos a cor escolhida pelo humano (cor_h) e a cor que a maquina
    ira usar (cor)*/
    if (cor_h == -1)
        cor = 1;
    else
        cor = -1;

    while (jogadas(tab, n) < n*n*n){
        /*caso o jogador tenha escolhido a bolinha preta, ele joga primeiro
        caso contrario, a maquina joga primeiro */
        if (jogadas(tab, n) > 0 || cor_h == 1){
            printf("Chose your play (x y): ");
            scanf("%d %d", &x, &y);

            /*as entradas do jogador tem que ser maiores que 0 e ate n-1*/
            if (x >= n || x < 0 || y >= n || y < 0){
                printf("Invalid input! Try again:\n");
                continue;
            }
            
            z = gravidade(tab, cor_h, n, &x, &y, z);
            if (z == -1)
                printf("Colum full, try another 'x' or 'y'\n");

            tab[x][y][z] = cor_h;

            /*verifica se a ultima jogada feita resulta no fim do jogo
            para o jogador*/
            fim = vitoria(tab, cor_h, n, x, y, z, 3);
            if (fim == 999){
                print_tab(tab, n);
                printf("Game over! You won!\n\n");
                return 0;
            }
        }
        /*jogada da maquina*/
        z = escolheJogada(tab, n, cor, &x, &y);
        tab[x][y][z] = cor;

        /*verifica se a ultima jogada feita resulta no fim do jogo
        para a maquina*/
        fim = vitoria(tab, cor, n, x, y, z, 3);
        if (fim == 999){
            print_tab(tab, n);
            printf("Game over! You lost!\n\n");
            return 0;
        }

        /*imprime a jogada da maquina e o tabuleiro*/
        print_tab(tab, n);
        printf("Machine's play: x: %d, y: %d, z: %d\n\n", x, y, z);
    }

    return 0;
}

int escolheJogada (int ***tab, int n, int cor, int *lin, int *col){
    int z = -1;

    /*para a primeira jogada da maquina, ela colocara uma bolinha em uma posicao
    aleatoria do tabuleiro onde não tenha outra bolinha */
    if (jogadas(tab, n) < 2){
        do{
            srand(time(NULL));
            *lin = rand() % n;
            *col = rand() % n;
        } while (tab[*lin][*col][0] != 0);
        z = gravidade(tab, cor, n, lin, col, z);
        return z;
    }

    /*jogada = 999 somente se a proxima jogada resultar em uma vitoria da maquina.
    Esse caso foi implementado para os casos onde o jogador pode ganhar no proximo
    turno, mas ao mesmo tempo a maquina pode ganhar tambem se ela jogar primeiro,
    entao em vez de impedir a vitoria do jogador, a maquina ira fazer a jogada que
    resulta em sua vitoria*/
    z = jogada_independente(tab, cor, n, lin, col, z, 2);
    if (z != -1)
        return z;

    /*jogada dependente eh a jogada que depende se a proxima jogada do jogador vai
    resultar na sua vitoria ou nao*/
    z = jogada_dependente(tab, cor, n, lin, col, z);
    if(z != -1)
        return z;

    /*jogada independente eh a jogada quando a proxima jogada do jogador nao resultar
    em uma vitoria dele, entao a maquina faz seu proprio jogo */
    z = jogada_independente(tab, cor, n, lin, col, z, 1);
    return z;
}

/*essa funcao simplesmente percorre todo o tabuleiro verificando cada bolinha do jogador
para ver se ele pode ganhar no proximo turno. Caso o jogador possa ganhar, a maquina ira
impedir a vitoria fazendo sua jogada*/
int jogada_dependente (int ***tab, int cor, int n, int *lin, int *col, int z){
    int x, y, jogada = 0;

    for (z = 0; z < n; z++)
        for (x = 0; x < n; x++)
            for (y = 0; y < n; y++) {
                if (tab[x][y][z] != cor && tab[x][y][z] != 0){
                    jogada = vitoria (tab, cor, n, x, y, z, 0);

                    if (jogada > 0){
                        *lin = x;
                        *col = y;
                        z = colocar_bolinha (tab, cor, n, jogada, lin, col, z);
                        return z;
                    }
                    else
                        continue;
                }
            }
    return -1;
}

/*funcao da jogada que eh independente das jogadas do jogador. Essa funcao eh chamada duas vezes
com parametros diferentes que serao enviados para a funcao vitoria. Se "parametro == 2" entao 
apenas queremos verificar se a maquina pode vencer na sua proxima jogada. Se "parametro == 1" 
a maquina faz sua jogada normalmente*/
int jogada_independente (int ***tab, int cor, int n, int *lin, int *col, int z, int parametro){
    int x, y, jogada = 0;

    for (z = 0; z < n; z++)
        for (x = 0; x < n; x++)
            for (y = 0; y < n; y++){
                if (tab[x][y][z] == cor){
                    jogada = vitoria(tab, cor, n, x, y, z, parametro);

                    if (jogada > 0){
                        *lin = x;
                        *col = y;

                        z = colocar_bolinha(tab, cor, n, jogada, lin, col, z);
                    }
                    else
                        continue;

                    return z;
                }
            }
    return -1;
}

/*essa funcao pega a posicao "x" e "y" dadas pela maquina ou pelo jogador e coloca
ela no primeiro plano "z" disponivel, simulando o efeito da gravidade. Se a funcao
reotrnar "-1" significa que a coluna esta cheia*/
int gravidade (int ***tab, int cor, int n, int *x, int *y, int z){
    for (z = 0; z < n; z++){
         if (tab[*x][*y][z] != 0)
            continue;
         else
            return z;
    }
    return -1;
}

/*conta o numero de jogadas ate o momento*/
int jogadas (int ***tab, int n){
    int x, y, z, contador = 0;

    for(z = 0; z < n; z++)
        for(x = 0; x < n; x++)
            for(y = 0; y < n; y++)
                if(tab[x][y][z] == -1 || tab[x][y][z] == 1)
                    contador++;

    return contador;
}

/*imprime o tabuleiro com Slepp(2) para deixar um pouco mais "dinamico"*/
void print_tab (int ***tab, int n)
{
    int x, y, z;
    for (z = 0; z < n; z++){
            for (x = 0; x < n; x++){
                for (y = 0; y < n; y++){
                    printf("%d  ", tab[x][y][z]);
                }
                Sleep(2);
                printf("\n");
            }
            printf("\n");
        }
}

/*essa funcao, apesar de longa, recebe um total de 4 parametros "0", "1", "2" e "3".
Para os parametros "0", "1" e "2", o programa retorna os valores de 1 a 13, respectivos a
todos os eixos possiveis do cubo. Esse valor sera enviado para a funcao "colocar_bolinha"
que entao ira colocar a bolinha no respectivo eixo.

- parametro 0: eh o caso onde verificamos se existe possibilidade de vitoria do jogador
na sua proxima jogada, por isso invertemos a cor da maquina e fazemos as verificacoes das
bolinhas baseada na cor do jogador.

- parametro 1: parametro da jogada independente, basicamente verifica se o eixo esta livre
de bolinhas do oponente para que a maquina possa comecar a colocar bolinhas naquele eixo.

- parametro 2: parametro para verificar se existe possibilidade de vitoria da maquina.

- parametro 3: parametro que verifica se a ultima jogada resultou na vitoria tanto do
jogador ou da maquina e encerra o programa.*/
int vitoria (int ***tab, int cor, int n, int x, int y, int z, int parametro){
    int i, j, k, vitoria;

    if (parametro == 0){
        if (cor == -1)
            cor = 1;
        else
            cor = -1;
    }

    for (vitoria = 0, i = 0; i < n; i++){
        if (tab[i][y][z] == cor)
            vitoria++;
        else if (tab[i][y][z] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 1;
    else if (vitoria != -999 && parametro == 1)
        return 1;
    else if (vitoria == n - 2 && parametro == 2)
        return 1;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, j = 0; j < n; j++){
        if (tab[x][j][z] == cor)
            vitoria++;
        else if (tab[x][j][z] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 2;
    else if (vitoria != -999 && parametro == 1)
        return 2;
    else if (vitoria == n - 2 && parametro == 2)
        return 2;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, k = 0; k < n; k++){
        if (tab[x][y][k] == cor)
            vitoria++;
        else if (tab[x][y][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 3;
    else if (vitoria != -999 && parametro == 1)
        return 3;
    else if (vitoria == n - 2 && parametro == 2)
        return 3;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = 0, j = 0; i < n || j < n; i++, j++){
        if (tab[i][j][z] == cor)
            vitoria++;
        else if (tab[i][j][z] == 0)
           vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 4;
    else if (vitoria != -999 && parametro == 1)
        return 4;
    else if (vitoria == n - 2 && parametro == 2)
        return 4;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = 0, j = n - 1; i < n || j >= 0; i++, j--){
        if (tab[i][j][z] == cor)
            vitoria++;
        else if (tab[i][j][z] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 5;
    else if (vitoria != -999 && parametro == 1)
        return 5;
    else if (vitoria == n - 2 && parametro == 2)
        return 5;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = 0, k = 0; i < n || k < n; i++, k++){
        if (tab[i][y][k] == cor)
            vitoria++;
        else if (tab[i][y][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 6;
    else if (vitoria != -999 && parametro == 1)
        return 6;
    else if (vitoria == n - 2 && parametro == 2)
        return 6;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = n - 1, k = 0; i >= 0 || k < n; i--, k++){
        if (tab[i][y][k] == cor)
            vitoria++;
        else if (tab[i][y][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 7;
    else if (vitoria != -999 && parametro == 1)
        return 7;
    else if (vitoria == n - 2 && parametro == 2)
        return 7;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, j = 0, k = 0; j < n || k < n; j++, k++){
        if (tab[x][j][k] == cor)
            vitoria++;
        else if (tab[x][j][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 8;
    else if (vitoria != -999 && parametro == 1)
        return 8;
    else if (vitoria == n - 2 && parametro == 2)
        return 8;
    else if (vitoria == n && parametro == 3)
        return 999;


     for (vitoria = 0, j = n - 1, k = 0; j >= 0 || k < n; j--, k++){
        if (tab[x][j][k] == cor)
            vitoria++;
        else if (tab[x][j][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 9;
    else if (vitoria != -999 && parametro == 1)
        return 9;
    else if (vitoria == n - 2 && parametro == 2)
        return 9;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = 0, j = 0, k = 0; i < n || j < n || k < n; i++, j++, k++){
        if (tab[i][j][k] == cor)
            vitoria++;
        else if (tab[i][j][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 10;
    else if (vitoria != -999 && parametro == 1)
        return 10;
    else if (vitoria == n - 2 && parametro == 2)
        return 10;
    else if (vitoria == n && parametro == 3)
        return 999;


    for (vitoria = 0, i = n - 1, j = 0, k = 0; i >= 0 || j < n || k < n; i--, j++, k++){
        if (tab[i][j][k] == cor)
            vitoria++;
        else if (tab[i][j][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 11;
    else if (vitoria != -999 && parametro == 1)
        return 11;
    else if (vitoria == n - 2 && parametro == 2)
        return 11;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = 0, j = n - 1, k = 0; i < n || j >= 0 || k < n; i++, j--, k++){
        if (tab[i][j][k] == cor)
            vitoria++;
        else if (tab[i][j][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 12;
    else if (vitoria != -999 && parametro == 1)
        return 12;
    else if (vitoria == n - 2 && parametro == 2)
        return 12;
    else if (vitoria == n && parametro == 3)
        return 999;

    for (vitoria = 0, i = n - 1, j = n - 1, k = 0; i >= 0 || j >= 0 || k < n; i--, j--, k++){
        if (tab[i][j][k] == cor)
            vitoria++;
        else if (tab[i][j][k] == 0)
            vitoria--;
        else{
            vitoria = -999;
            break;
        }
    }
    if (vitoria == n - 2 && parametro == 0)
        return 13;
    else if (vitoria != -999 && parametro == 1)
        return 13;
    else if (vitoria == n - 2 && parametro == 2)
        return 13;
    else if (vitoria == n && parametro == 3)
        return 999;

    return 0;
}

/*essa funcao recebe o valor da jogada escolhido pela funcao "vitoria" e encontra a
primeira posicao livre para colocar a bolinha*/
int colocar_bolinha (int ***tab, int cor, int n, int jogada, int *x, int *y, int z){
    int i, j, k;

    if (jogada == 1){
        for (i = 0; i < n; i++)
            if (tab[i][*y][z] == 0){
                *x = i; 
                z = gravidade(tab, cor, n, x, y, z);
                return z;
            }
    }
    else if (jogada == 2){
        for (j = 0; j < n; j++)
            if (tab[*x][j][z] == 0){
                *y = j;
                z = gravidade(tab, cor, n, x, y, z);
                return z;
            }
    }
    else if (jogada == 3){
        for (k = 0; k < n; k++)
            if (tab[*x][*y][k] == 0){
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 4){
        for (i = 0, j = 0; i < n || j < n; i++, j++)
            if (tab[i][j][z] == 0){
                *x = i;
                *y = j;
                z = gravidade(tab, cor, n, x, y, z);
                return z;
            }
    }
    else if (jogada == 5){
        for (i = 0, j = n - 1; i < n || j >= 0; i++, j--)
            if (tab[i][j][z] == 0){
                *x = i;
                *y = j;
                z = gravidade(tab, cor, n, x, y, z);
                return z;
            }
    }
    else if (jogada == 6){
        for (i = 0, k = 0; i < n || k < n; i++, k++)
            if (tab[i][*y][k] == 0){
                *x = i;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 7){
        for (i = n - 1, k = 0; i >= 0 || k < n; i--, k++)
            if (tab[i][*y][k] == 0){
                *x = i;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 8){
        for (j = 0, k = 0; j < n || k < n; j++, k++)
            if (tab[*x][j][k] == 0){
                *y = j;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 9){
        for (j = n - 1, k = 0; j >= 0 || k < n; j--, k++)
            if (tab[*x][j][k] == 0){
                *y = j;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 10){
        for (i = 0, j = 0, k = 0; i < n || j < n || k < n; i++, j++, k++)
            if (tab[i][j][k] == 0){
                *x = i;
                *y = j;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 11){
        for (i = n - 1, j = 0, k = 0; i >= 0 || j < n || k < n; i--, j++, k++)
            if (tab[i][j][k] == 0){
                *x = i;
                *y = j;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else if (jogada == 12){
        for (i = 0, j = n - 1, k = 0; i < n || j >= 0|| k < n; i++, j--, k++)
            if (tab[i][j][k] == 0){
                *x = i;
                *y = j;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }
    else{
        for (i = n - 1, j = n - 1, k = 0; i >= 0 || j >= 0|| k < n; i--, j--, k++)
            if (tab[i][j][k] == 0){
                *x = i;
                *y = j;
                z = gravidade(tab, cor, n, x, y, k);
                return z;
            }
    }

    return z;
}



