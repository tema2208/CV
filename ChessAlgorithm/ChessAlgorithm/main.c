#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>


int check_vert_horizont(int desk[8][8], int king1, int king2)
{
	if ((desk[king1 - 1][king2 - 1] > 0) || (desk[king1 - 1][king2 - 1] == -1) || (desk[king1 - 1][king2 - 1] == -3) || (desk[king1 - 1][king2 - 1] == -4) || (desk[king1 - 1][king2 - 1] == -6)) { return 1; } // не надо ли тут убрать пешку?
	if ((desk[king1 - 1][king2 - 1] == -2) || (desk[king1 - 1][king2 - 1] == -5)) {

		printf("cannot move vertical or horizontal because %d", desk[king1 - 1][king2 - 1]);
		return 0;
	}
	return 1;
}

int check_diagonal(int desk[8][8], int king1, int king2)
{
	if ((desk[king1 - 1][king2 - 1] > 0) || (desk[king1 - 1][king2 - 1] == -1) || (desk[king1 - 1][king2 - 1] == -3) || (desk[king1 - 1][king2 - 1] == -2) || (desk[king1 - 1][king2 - 1] == -6)) { return 1; }
	if ((desk[king1 - 1][king2 - 1] == -4) || (desk[king1 - 1][king2 - 1] == -5)) {
		printf("cannot move diagonal");
		return 0;
	}
	return 1;
}

void print_desk(int arr[8][8])
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void input_from_file(FILE* file, int arr[8][8])
{
	printf("1(-1) - white (black) pawn\n");
	printf("2(-2) - white (black) rook\n");
	printf("3(-3) - white (black) knight\n");
	printf("4(-4) - white (black) bishop\n");
	printf("5(-5) - white (black) queen\n");
	printf("6(-6) - white (black) king\n");


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fscanf(file, "%d", &arr[i][j]);
		}
	}
}
void kings_coordinates(int desk[8][8], int* king1, int* king2)
{
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; i < 8; ++j)
		{
			if (desk[i][j] == 6)
			{
				*king1 = i + 1;
				*king2 = j + 1;
				return;
			}
		}
	}
}
void basic_input(int desk[8][8], int start_rook1, int start_rook2, int king1, int king2)
{
	int  k, i, j, tmp1, tmp2;
	printf("1(-1) - white (black) pawn\n");
	printf("2(-2) - white (black) rook\n");
	printf("3(-3) - white (black) knight\n");
	printf("4(-4) - white (black) bishop\n");
	printf("5(-5) - white (black) queen\n");
	printf("6(-6) - white (black) king\n");

	for (i = 0; i <= 7; i++)
	{
		for (j = 0; j <= 7; j++)
		{
			desk[i][j] = 0;
		}
	}
	do
	{
		scanf("%d %d %d", &i, &j, &k);
		desk[i - 1][j - 1] = k;
	} while ((i != 0) && (j != 0) && (k != 0));

	printf("Indicate the position of the white rook:\n");
	scanf("%d%d", &tmp1, &tmp2);
	start_rook1 = tmp1;
	start_rook2 = tmp2;
	desk[start_rook1 - 1][start_rook2 - 1] = 2;

	printf("Indicate the position of the white king:\n");
	scanf("%d%d", &tmp1, &tmp2);
	king1 = tmp1;
	king2 = tmp2;
	desk[king1 - 1][king2 - 1] = 6;


}

//is the king under attack
void check(int st_rook1, int st_rook2, int to_rook1, int to_rook2, int desk[8][8])
{
	int king1, king2;
	kings_coordinates(desk, &king1, &king2);
	desk[to_rook1 - 1][to_rook2 - 1] = 2;
	desk[st_rook1 - 1][st_rook2 - 1] = 0;
	int h = king1;
	int x = king2;

	if ((desk[king1][king2] == -1) || (desk[king1 - 2][king2] == -1) || (desk[king1][king2] == -6) || (desk[king1 - 2][king2] == -6) || (desk[king1 - 1][king2] == -6) || (desk[king1 - 2][king2 - 1] == -6) || (desk[king1 - 2][king2 - 2] == -6) || (desk[king1 - 1][king2 - 2] == -6) || (desk[king1][king2 - 2] == -6) || (desk[king1][king2 - 1] == -6)) { // проверка для пешки и короля
		printf("this move is not allowed");
		return;
	}
	if ((desk[king1][king2 + 1] == -3) || (desk[king1 + 1][king2] == -3) || (desk[king1 + 1][king2 - 2] == -3) || (desk[king1][king2 - 3] == -3) || (desk[king1 - 2][king2 - 3] == -3) || (desk[king1 - 3][king2 - 2] == -3) || (desk[king1 - 3][king2] == -3) || (desk[king1 - 2][king2 + 1] == -3)) { // проверка для коня
		printf("this move is not allowed");
		return;
	}

	// horizontal right
	for (int d = 1; d <= (8 - king1); d++)
	{
		king1++;
		if (!check_vert_horizont(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}
	king1 = h;
	// horizontal left
	for (int d = 1; d <= (king1 - 1); d++) {
		king1--;
		if (!check_vert_horizont(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}
	king1 = h;

	//vertical right 
	for (int d = 1; d <= (8 - king2); d++) {
		king2++;
		if (!check_vert_horizont(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}
	king2 = x;
	//vertical left
	for (int d = 1; d <= (king2 - 1); d++) {
		king2--;
		if (!check_vert_horizont(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}

	king1 = h;
	king2 = x;

	// for diagonal

	for (int d = 1; d <= 8; d++) {
		king1++;
		king2++;
		if (!check_diagonal(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}

	king1 = h;
	king2 = x;

	for (int d = 1; d <= 8; d++) {
		king1++;
		king2--;
		if (!check_diagonal(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}

	king1 = h;
	king2 = x;

	for (int d = 1; d <= 8; d++) {
		king1--;
		king2++;
		if (!check_diagonal(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}

	king1 = h;
	king2 = x;

	for (int d = 1; d <= 8; d++) {
		king1--;
		king2--;
		if (!check_diagonal(desk, king1, king2))
		{
			printf("this move is not allowed");
			return;
		}
	}

	printf("this move is allowed!");
}

void main()
{
	system("chcp 1251");
	int desk[8][8], to_rook1, to_rook2, k, start_rook1 = 0, start_rook2 = 0, l, king1 = 0, king2 = 0, i, j;

	//basic_input(desk[8][8], start_rook1, start_rook2, king1, king2);

	FILE* myfile = fopen("input2.txt", "r");
	input_from_file(myfile, desk);

	printf("Indicate the position of the white rook:\n");
	scanf("%d%d", &start_rook1, &start_rook2);
	desk[start_rook1 - 1][start_rook2 - 1] = 2;


	kings_coordinates(desk, &king1, &king2);

	print_desk(desk);

	printf("\n");
	printf("indicate the position to which the rook will go:\n");
	scanf("%d%d", &to_rook1, &to_rook2);
	desk[start_rook1 - 1][start_rook2 - 1] = 0;
	printf("\n");

	printf("st_r1: %d st_r2: %d to_r1: %d to_r2: %d king: %d   ", start_rook1, start_rook2, to_rook1, to_rook2, desk[king1 - 1][king2 - 1]);

	if (((to_rook1 != start_rook1) && (to_rook2 != start_rook2)) || ((to_rook1 == start_rook1) && (to_rook2 == start_rook2)))
	{
		printf("this move is not allowed");
		return;
	}
	if (to_rook1 == start_rook1)
	{
		if (to_rook2 > start_rook2)
		{
			for (int l = 1; l <= 7; l++)
			{
				start_rook2++;
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook2 != to_rook2))
				{
					printf("this move is not allowed");
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] == 0) && (start_rook2 == to_rook2))
				{
					check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook2 == to_rook2))
				{
					if (desk[start_rook1 - 1][start_rook2 - 1] > 0)
					{
						printf("this move is not allowed");
						return;
					}
					if (desk[start_rook1 - 1][start_rook2 - 1] < 0) {
						check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
						return;
					}
				}
			}
		}
		if (to_rook2 < start_rook2) {
			for (int l = 1; l <= 7; l++) {
				start_rook2--;
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook2 != to_rook2)) {
					printf("this move is not allowed");
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] == 0) && (start_rook2 == to_rook2)) {
					check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook2 == to_rook2))
				{
					if (desk[start_rook1 - 1][start_rook2 - 1] > 0) {
						printf("this move is not allowed");
						return;
					}
					if (desk[start_rook1 - 1][start_rook2 - 1] < 0) {
						check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
						return;
					}
				}
			}

		}

	}
	if (to_rook2 == start_rook2) {
		if (to_rook1 > start_rook1) {
			for (int l = 1; l <= 7; l++) {
				start_rook1++;
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook1 != to_rook1)) {
					printf("this move is not allowed");
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] == 0) && (start_rook1 == to_rook1)) {
					check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook1 == to_rook1))
				{
					if (desk[start_rook1 - 1][start_rook2 - 1] > 0) {
						printf("this move is not allowed");
						return;
					}
					if (desk[start_rook1 - 1][start_rook2 - 1] < 0) {
						check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
						return;
					}
				}
			}
		}
		if (to_rook1 < start_rook1) {
			for (int l = 1; l <= 7; l++) {
				start_rook1--;
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook1 != to_rook1))
				{
					printf("this move is not allowed");
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] == 0) && (start_rook1 == to_rook1)) {
					check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
					return;
				}
				if ((desk[start_rook1 - 1][start_rook2 - 1] != 0) && (start_rook1 == to_rook1)) {
					if (desk[start_rook1 - 1][start_rook2 - 1] > 0) {
						printf("this move is not allowed");
						return;
					}
					if (desk[start_rook1 - 1][start_rook2 - 1] < 0) {
						check(start_rook1, start_rook2, to_rook1, to_rook2, desk);
						return;
					}
				}
			}

		}
	}

}