#include<stdio.h>

void ligne(int k)
{
		for (int i = 0; i<2*k+1;i++)
				printf("-");
		printf("|\n");
}

void escalier(int n)
{
		for (int i = 0;i<n;i++)
				ligne(i);
}

int main()
{
		int n;
		printf("Entrez un entier = ");
		scanf("%d", &n);
		escalier(n);
}
