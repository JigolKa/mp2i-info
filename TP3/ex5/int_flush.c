#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/* Lit un entier dans le terminal.
- Si la lecture réussit, alors la fonction renvoie true et stocke l'entier lu
  dans res.
- Si la lecture est infructueuse, alors la fonction renvoie false.
Dans les deux cas, l'entrée du terminal est ensuite vidée de tout caractère
additionnel */
bool read_int_and_flush(int *res)
{
	char c;
	int tmp = 0;
	while (scanf("%c", &c) && c != '\n')
	{
		if (0 <= c - '0' && c - '0' <= 9)
			tmp += c - '0', tmp *= 10;
	}

	*res = tmp / 10;
	return tmp != 0;
}

int main()
{
	// int *x;
	// read_int_and_flush(x);
	// printf("%d\n", *x);
	int x = 1;
	do
	{
		printf("Rentrez un entier (0 pour finir): ");
		bool b = read_int_and_flush(&x);
		if (b)
		{
			printf("Entier lu: %d\n", x);
		}
		else
		{
			printf("Erreur de lecture\n");
		}
	} while (x != 0);
}