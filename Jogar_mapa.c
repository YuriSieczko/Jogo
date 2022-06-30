#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
#include "gea.h"
#include "editor_mapa.h"

#define LAR 62
#define ALT 18
#define CAMINHO 0
#define PAREDE 1
#define INICIO 2
#define ANIMAL 3
#define OBSTACULO 4
#define FUTURO 5

int main()
{
    int mapa[ALT][LAR];
    int lin, col, final, px, py;
    int pontos;
    char jogada;
    // Minhas variaveis
    int op, rodar = 1;
    int cont = 0, ret = 0;
    int e = 0;
    int j = 0, rel = 0;
    //int g = 0;
    //int cont_c = 0, verif = 0;
    int jogada_aut = 2;

    // clock
    time_t t_ini, t_fin, t_tot;

    FILE *arquivo_m;
    fase f;

    void tchau();

    while (rodar == 1)
    {
        system("clear");
        printf("Selecione a opção:");
        printf("\n(1) Jogar mapas");
        printf("\n(2) Criar mapas");
        printf("\n(3) Sair");
        printf("\n> ");
        scanf("%i", &j);
        t_tot = 0;
        if (j == 1)
        {
            // jogar
            rel = 0; // Controle pra mostrar relogio no lugar certo.
            // Busca os mapas salvos no .bin.
            arquivo_m = fopen("Mapas.bin", "a+");
            system("clear");
            rewind(arquivo_m);
            printf("Selecione o mapa: \n");
            cont = 0;
            do
            {
                ret = fread(&f, sizeof(fase), 1, arquivo_m);

                if (ret == 1)
                {
                    printf("\n%s [%i]", f.nome, cont);
                    cont++;
                }
            } while (ret == 1);

            printf("\n");

            scanf("%i", &e);

            rewind(arquivo_m);
            // Menu de opçoes do jogo.
            cont = 0;
            do
            {
                ret = fread(&f, sizeof(fase), 1, arquivo_m);

                if (cont == e)
                {
                    system("clear");
                    printf("Escolha um modo de jogo\n");
                    printf("(1) Manual\n(2)Automático\n(3)Sair\n> ");
                    scanf("%i", &op);
                    // Jogo opção manual.
                    if (op == 1)
                    {
                        for (lin = 0; lin < ALT; lin++)
                        {
                            // printf("");
                            for (col = 0; col < LAR; col++)
                            {
                                if (f.fase[lin][col] == INICIO)
                                {
                                    px = lin;
                                    py = col;
                                }
                            }
                        }

                        t_ini = time(NULL);
                        while (jogada != ANIMAL)
                        {
                            COR_BRANCO
                            system("clear");
                            printf("\t\t  GAME RESGATE - %s \n", f.nome);

                            for (lin = 0; lin < ALT; lin++)
                            {
                                // printf("");
                                for (col = 0; col < LAR; col++)
                                {

                                    if (lin == px && col == py)
                                    {
                                        COR_AZUL
                                        printf("☻");
                                    }
                                    else if (f.fase[lin][col] == CAMINHO)
                                    {
                                        COR_BRANCO
                                        printf(" ");
                                    }
                                    else if (f.fase[lin][col] == PAREDE)
                                    {
                                        COR_BRANCO
                                        printf("#");
                                    }
                                    else if (f.fase[lin][col] == INICIO)
                                    {
                                        COR_AZUL
                                        printf(" ");
                                    }
                                    else if (f.fase[lin][col] == ANIMAL)
                                    {
                                        COR_LARANJA
                                        printf("♞");
                                    }
                                }
                                printf("\n");
                            }

                            if (rel > 0)
                            {
                                if (t_tot / 60 < 10)
                                {
                                    printf("Tempo: [0%li:", t_tot / 60);
                                }
                                else
                                {
                                    printf("Tempo: [%li:", t_tot / 60);
                                }
                                if (t_tot % 60 < 10)
                                {
                                    printf("0%li]", t_tot % 60);
                                }
                                else
                                {
                                    printf("%li]", t_tot % 60);
                                }
                            }

                            if (f.fase[px][py] == ANIMAL)
                            {
                                break;
                            }

                            // CAPTURA TECLA
                            jogada = getch();
                            rel = 1; // controle do reglogio;
                            // TECLA ESPECIAL
                            if (jogada == 27)
                            {
                                jogada = getch();

                                if (jogada == 91)
                                {
                                    jogada = getch();

                                    // CIMA
                                    if (jogada == 65)
                                    {
                                        if (px > 1)
                                        {
                                            if (f.fase[px - 1][py] != PAREDE)
                                            {
                                                px--;
                                            }
                                        }
                                    }
                                    // BAIXO
                                    else if (jogada == 66)
                                    {
                                        if (px < ALT - 2)
                                        {
                                            if (f.fase[px + 1][py] != PAREDE)
                                            {
                                                px++;
                                            }
                                        }
                                    }
                                    // DIREITA
                                    else if (jogada == 67)
                                    {
                                        if (py < LAR - 2)
                                        {
                                            if (f.fase[px][py + 1] != PAREDE)
                                            {
                                                py++;
                                            }
                                        }
                                    }
                                    // ESQUERDA
                                    else if (jogada == 68)
                                    {
                                        if (py > 1)
                                        {
                                            if (f.fase[px][py - 1] != PAREDE)
                                            {
                                                py--;
                                            }
                                        }
                                    }
                                }

                                t_tot = time(NULL) - t_ini;
                            }
                        }
                        tchau();
                    }

                    if (op == 2)
                    {
                        rel = 0;
                        // Timer inicio
                        t_ini = time(NULL);
                        while (jogada_aut > 1)
                        {
                            COR_BRANCO
                            system("clear");
                            printf("\t\t  GAME RESGATE - %s \n", f.nome);

                            for (lin = 0; lin < ALT; lin++)
                            {
                                // printf("");
                                for (col = 0; col < LAR; col++)
                                {
                                    if (f.fase[lin][col] == CAMINHO)
                                    {
                                        COR_BRANCO
                                        printf(" ");
                                    }
                                    else if (f.fase[lin][col] == PAREDE)
                                    {
                                        COR_BRANCO
                                        printf("#");
                                    }
                                    else if (f.fase[lin][col] == INICIO)
                                    {
                                        COR_AZUL
                                        printf("☻");
                                    }
                                    else if (f.fase[lin][col] == ANIMAL)
                                    {
                                        COR_LARANJA
                                        printf("♞");
                                    }
                                    else if (f.fase[lin][col] == OBSTACULO)
                                    {
                                        COR_BRANCO
                                        printf(" ");
                                    }
                                }
                                printf("\n");
                            }
                            // Mostra o timer.

                            if (rel > 0)
                            {
                                if (t_tot / 60 < 10)
                                {
                                    printf("Tempo: [0%li:", t_tot / 60);
                                }
                                else
                                {
                                    printf("Tempo: [%li:", t_tot / 60);
                                }
                                if (t_tot % 60 < 10)
                                {
                                    printf("0%li]", t_tot % 60);
                                }
                                else
                                {
                                    printf("%li]", t_tot % 60);
                                }
                            }
                            if (jogada_aut == 3)
                            {
                                jogada_aut = 0;
                                tchau();
                            }
                            // Jogo automatico
                            rel = 1;
                            for (lin = 0; lin < ALT; lin++)
                            {
                                // printf("");
                                for (col = 0; col < LAR; col++)
                                {
                                    if (f.fase[lin][col] == INICIO || f.fase[lin][col] == OBSTACULO)
                                    {
                                        if (f.fase[lin + 1][col] == ANIMAL)
                                        {
                                            f.fase[lin + 1][col] = FUTURO;
                                            f.fase[lin][col] = OBSTACULO;
                                            lin = ALT;
                                            jogada_aut = 3;
                                            break;
                                        }
                                        else if (f.fase[lin - 1][col] == ANIMAL)
                                        {
                                            f.fase[lin - 1][col] = FUTURO;
                                            f.fase[lin][col] = OBSTACULO;
                                            lin = ALT;
                                            jogada_aut = 3;
                                            break;
                                        }
                                        else if (f.fase[lin][col + 1] == ANIMAL)
                                        {
                                            f.fase[lin][col + 1] = FUTURO;
                                            f.fase[lin][col] = OBSTACULO;
                                            lin = ALT;
                                            jogada_aut = 3;
                                            break;
                                        }
                                        else if (f.fase[lin][col - 1] == ANIMAL)
                                        {
                                            f.fase[lin][col - 1] = FUTURO;
                                            f.fase[lin][col] = OBSTACULO;
                                            lin = ALT;
                                            jogada_aut = 3;
                                            break;
                                        }
                                        else
                                        {
                                            // baixo
                                            if (f.fase[lin + 1][col] == CAMINHO)
                                            {
                                                f.fase[lin][col] = OBSTACULO;
                                                f.fase[lin + 1][col] = FUTURO;
                                            }
                                            // cima
                                            if (f.fase[lin - 1][col] == CAMINHO)
                                            {
                                                f.fase[lin][col] = OBSTACULO;
                                                f.fase[lin - 1][col] = FUTURO;
                                            }
                                            // direita
                                            if (f.fase[lin][col + 1] == CAMINHO)
                                            {
                                                f.fase[lin][col] = OBSTACULO;
                                                f.fase[lin][col + 1] = FUTURO;
                                            }
                                            // esquerda
                                            if (f.fase[lin][col - 1] == CAMINHO)
                                            {
                                                f.fase[lin][col] = OBSTACULO;
                                                f.fase[lin][col - 1] = FUTURO;
                                            }
                                        }
                                    }
                                }
                                t_tot = time(NULL) - t_ini;
                            }

                            for (lin = 0; lin < ALT; lin++)
                            {
                                // printf("");
                                for (col = 0; col < LAR; col++)
                                {
                                    if (f.fase[lin][col] == FUTURO)
                                    {
                                        f.fase[lin][col] = INICIO;
                                    }
                                }
                            }
                            sleep(1);
                        }
                        break;
                    }
                }
                cont++;
            } while (ret == 1);
        }
        // Editor de mapa,, switch (j).
        if (j == 2)
        {
            editarmapa();
        }
        // Sair switch (j).
        if (j == 3)
        {
            rodar = 0;
        }
    }

    printf("\n\n");

    return 0;
}

void tchau()
{
    printf("\n!!RESGATE COMPLETO!!");
    __fpurge(stdin);
    getchar();
}
