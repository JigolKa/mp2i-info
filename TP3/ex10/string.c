#include <stdio.h>

int main(){
	char str[20];
	str[2] = 'U';
	str[3] = 'L';
	str[4] = 'T';
	str[8] = 'R'; 
	str[1] = 'A';
	str[0] = 'S';
	str[5] = '\0';
	str[6] = '!'; 
	str[7] = '!'; 

	printf("%s\n", str);
	return 0;
}