#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>

bool verifier(int target, int guess)
{
		if (guess < target)
			printf("Plus haut\n");
		else if (guess > target)
			printf("Plus bas\n");
		else printf("Gagné\n");
		return guess == target;
}

int main()
{
		srand(time(NULL));
		int target = 1 + rand() % 100;
		bool over = false;
		while (!over)
		{
				printf("Entrez un nombre = ");
				int cur;
				scanf("%d",&cur);
				over = verifier(target,cur);
		}
		return 0;
}
