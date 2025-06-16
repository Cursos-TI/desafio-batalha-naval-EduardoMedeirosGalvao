#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define NAVIO_TAM 3

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '.';
}

void imprimirTabuleiro(char tabuleiro[TAM][TAM], int ocultar) {
    printf("  ");
    for (int j = 0; j < TAM; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            if (ocultar && tabuleiro[i][j] == 'N')
                printf(". ");
            else
                printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarNavio(char tabuleiro[TAM][TAM]) {
    int linha, coluna, orientacao;
    int valido = 0;

    while (!valido) {
        linha = rand() % TAM;
        coluna = rand() % TAM;
        orientacao = rand() % 2; // 0 = horizontal, 1 = vertical

        valido = 1;

        if (orientacao == 0 && coluna + NAVIO_TAM <= TAM) {
            for (int j = 0; j < NAVIO_TAM; j++)
                if (tabuleiro[linha][coluna + j] != '.') valido = 0;

            if (valido)
                for (int j = 0; j < NAVIO_TAM; j++)
                    tabuleiro[linha][coluna + j] = 'N';
        } else if (orientacao == 1 && linha + NAVIO_TAM <= TAM) {
            for (int i = 0; i < NAVIO_TAM; i++)
                if (tabuleiro[linha + i][coluna] != '.') valido = 0;

            if (valido)
                for (int i = 0; i < NAVIO_TAM; i++)
                    tabuleiro[linha + i][coluna] = 'N';
        } else {
            valido = 0;
        }
    }
}

int atacar(char tabuleiro[TAM][TAM], int l, int c) {
    if (tabuleiro[l][c] == 'N') {
        tabuleiro[l][c] = 'X'; // acerto
        return 1;
    } else if (tabuleiro[l][c] == '.') {
        tabuleiro[l][c] = 'O'; // erro
    }
    return 0;
}

int navioAfundado(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == 'N') return 0;
    return 1;
}

int main() {
    char tabJogador[TAM][TAM], tabComputador[TAM][TAM];
    int linha, coluna;

    srand(time(NULL));

    inicializarTabuleiro(tabJogador);
    inicializarTabuleiro(tabComputador);

    posicionarNavio(tabJogador);
    posicionarNavio(tabComputador);

    printf("BATALHA NAVAL (5x5)\nVocê tem que afundar o navio inimigo!\n");

    while (1) {
        printf("\nSeu tabuleiro:\n");
        imprimirTabuleiro(tabJogador, 0);

        printf("\nTabuleiro do inimigo:\n");
        imprimirTabuleiro(tabComputador, 1);

        // Jogador ataca
        do {
            printf("\nDigite coordenadas para atacar (linha e coluna): ");
            scanf("%d %d", &linha, &coluna);
        } while (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM);

        if (atacar(tabComputador, linha, coluna))
            printf("-> ACERTOU!\n");
        else
            printf("-> Errou...\n");

        if (navioAfundado(tabComputador)) {
            printf("\nVocê venceu! Afundou o navio inimigo.\n");
            break;
        }

        // Computador ataca
        do {
            linha = rand() % TAM;
            coluna = rand() % TAM;
        } while (tabJogador[linha][coluna] == 'X' || tabJogador[linha][coluna] == 'O');

        printf("\nInimigo atacou em (%d, %d): ", linha, coluna);
        if (atacar(tabJogador, linha, coluna))
            printf("ACERTOU!\n");
        else
            printf("Errou...\n");

        if (navioAfundado(tabJogador)) {
            printf("\nVocê perdeu! Seu navio foi afundado.\n");
            break;
        }
    }

    return 0;
}