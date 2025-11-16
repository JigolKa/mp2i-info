#include <stdio.h>
/* Affiche le code du caractère entré par l'utilisateur
*/

int main()
{
	char c;
	printf("Veuillez rentrer un caractère: ");
	scanf("%c", &c); // scanne un caractère unique
	printf("Le caractère '%c' a pour code %d\n", c, c);
	return 0;
}