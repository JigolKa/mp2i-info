#include<stdio.h>

int main()
{
		int acc = 0, cur = 0;

		while (cur>=0)
		{
			acc+=cur;
			scanf("%d",&cur);
		}
		printf("somme = %d\n", acc);

}
