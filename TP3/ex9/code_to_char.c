#include <stdio.h>
/* Affiche le caractère correspondant à un code entier dans [0, 127] */

int main()
{
	char c;
	printf("Veuillez rentrer un entier entre 0 et 127: ");
	int code;
	scanf("%d", &code); // scanne un entier et le stocke dans code
	c = code; // permet de convertir la valeur de int (32 bits) vers char (8 bits)
	          // si on rentre un code plus grand que 255, alors c contient code modulo 256

	printf("Le code %d correspond au caractère '%c'\n", c, c); // affiche le caractère correspondant à l'entier c
	return 0;
}