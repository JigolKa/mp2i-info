#include <stdio.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	char str1[8] = "BONJOUR"; // 7 lettres + 1 caractère nul = 8
	char str2[9] = "COUCOURR";

	str1[7] = ' ';
	str2[6] = ' ';

	printf("%s\n", str1);
	printf("%s\n", str2);

	return 0;
}