#ifndef _EDITORMAPA_
#define _EDITORMAPA_

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <time.h>
//#include "gea.h"

#define LAR 62
#define ALT 18
#define CAMINHO 0
#define PAREDE 1
#define INICIO 2
#define ANIMAL 3

// Minha struct
typedef struct
{
	char nome[20];
	int fase[ALT][LAR];
} fase;

void editarmapa()
{

	int mapa[ALT][LAR];
	int lin, col, final, px, py;
	int pontos;
	// Minhas variaveis
	int g = 0, pos = 0, ini = 0, ani = 0;
	int cont_c = 0, verif = 0;
	int teste[ALT][LAR];
	char jogada;
	char escolha;
	fase f;
	FILE *arquivo_m;

	// INICIALIZA O MAPA COM PAREDES
	for (lin = 0; lin < ALT; lin++)
	{
		for (col = 0; col < LAR; col++)
		{
			mapa[lin][col] = PAREDE;
		}
	}

	// EDITOR DE MAPAS - USUARIO MONTA O MAPA A SER USADO NO JOGO
	while (cont_c == 0)
	{
		final = 0;
		px = py = 1;

		while (final == 0)
		{

			COR_BRANCO
			system("clear");
			printf("\t\t  EDITOR DE MAPAS - GAME RESGATE\n");
			for (lin = 0; lin < ALT; lin++)
			{
				// printf("");
				for (col = 0; col < LAR; col++)
				{

					if (lin == px && col == py)
					{
						COR_VERMELHO
						printf("_");
					}
					else if (mapa[lin][col] == CAMINHO)
					{
						COR_BRANCO
						printf(" ");
					}
					else if (mapa[lin][col] == PAREDE)
					{
						COR_BRANCO
						printf("#");
					}
					else if (mapa[lin][col] == INICIO)
					{
						COR_AZUL
						printf("☻");
					}
					else if (mapa[lin][col] == ANIMAL)
					{
						COR_LARANJA
						printf("♞");
					}
				}
				printf("\n");
			}
			COR_BRANCO
			printf("    (C: Caminho)(P: Parede)(I: Início)(A: Animal)(O: OK)");

			// CAPTURA TECLA
			jogada = getch();

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
							px--;
						}
					}
					// BAIXO
					else if (jogada == 66)
					{
						if (px < ALT - 2)
						{
							px++;
						}
					}
					// DIREITA
					else if (jogada == 67)
					{
						if (py < LAR - 2)
						{
							py++;
						}
					}
					// ESQUERDA
					else if (jogada == 68)
					{
						if (py > 1)
						{
							py--;
						}
					}
				}
			}

			// PAREDE
			else if (jogada == 'P' || jogada == 'p')
			{
				if (mapa[px][py] == ANIMAL)
				{
					ani = 0;
				}
				if (mapa[px][py] == INICIO)
				{
					ini = 0;
				}
				mapa[px][py] = PAREDE;
			}
			// CAMINHO
			else if (jogada == 'C' || jogada == 'c')
			{
				if (mapa[px][py] == ANIMAL)
				{
					ani = 0;
				}
				if (mapa[px][py] == INICIO)
				{
					ini = 0;
				}
				mapa[px][py] = CAMINHO;
			}
			// INICIO
			else if (jogada == 'I' || jogada == 'i')
			{
				if (ini == 0)
				{
					mapa[px][py] = INICIO;
					ini++;
				}
			}
			// ANIMAL
			else if (jogada == 'A' || jogada == 'a')
			{
				if (ani == 0)
				{
					mapa[px][py] = ANIMAL;
					ani++;
				}
			}
			// OK - SAIR

			else if (jogada == 'O' || jogada == 'o')
			{
				final = 1;
			}
			printf("\n");
		}
		// Testa se o mapa é valido
		cont_c = 1;

		for (lin = 0; lin < ALT; lin++)
		{
			for (col = 0; col < LAR; col++)
			{
				teste[lin][col] = mapa[lin][col];
			}
		}

		g = 1;
		cont_c = 0;
		for (verif = 0; verif < g; verif++)
		{
			for (lin = 0; lin < ALT; lin++)
			{
				for (col = 0; col < LAR; col++)
				{
					if (teste[lin][col] == INICIO)
					{
						// baixo
						if (teste[lin + 1][col] == ANIMAL)
						{
							lin = ALT;
							verif = g;
							cont_c = 1;
							break;
						}
						else if (teste[lin + 1][col] == CAMINHO)
						{
							teste[lin + 1][col] = INICIO;
							g++;
						}
						// cima
						if (teste[lin - 1][col] == ANIMAL)
						{
							lin = ALT;
							verif = g;
							cont_c = 1;
							break;
						}
						else if (teste[lin - 1][col] == CAMINHO)
						{
							teste[lin - 1][col] = INICIO;
							g++;
						}
						// direita
						if (teste[lin][col + 1] == ANIMAL)
						{
							lin = ALT;
							verif = g;
							cont_c = 1;
							break;
						}

						else if (teste[lin][col + 1] == CAMINHO)
						{
							teste[lin][col + 1] = INICIO;
							g++;
						}
						// esquerda
						if (teste[lin][col - 1] == ANIMAL)
						{
							lin = ALT;
							verif = g;
							cont_c = 1;
							break;
						}

						else if (teste[lin][col - 1] == CAMINHO)
						{
							teste[lin][col - 1] = INICIO;
							g++;
						}
					}
				}
			}
		}
	}
	// SALVAR MAPA NO .BIN
	// Joga o mapa dentro da struct

	printf("\nDigite o nome do mapa: ");
	__fpurge(stdin);
	gets(f.nome);

	for (lin = 0; lin < ALT; lin++)
	{
		for (col = 0; col < LAR; col++)
		{
			f.fase[lin][col] = mapa[lin][col];
		}
	}

	// abre o arquivo .bin e salva o mapa
	arquivo_m = fopen("Mapas.bin", "a+");
	if (arquivo_m == NULL)
	{
		printf("\nErro ao abrir o arquivo");
	}
	else
	{
		fwrite(&f, sizeof(fase), 1, arquivo_m);
		fclose(arquivo_m);
	}

	printf("\n\n");
}
#endif