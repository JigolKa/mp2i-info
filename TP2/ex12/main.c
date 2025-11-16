#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define ll long int

// affiche les nombres premiers <= N
int main()
{
		int N;
		printf("N = ");
		scanf("%d", &N);

		bool* is_prime = (bool*)malloc(sizeof(bool)*(N+1));
		for (int i = 2; i<= N; i++)
			is_prime[i]=true;
		is_prime[1]=false, is_prime[0]=false;
		for (int i = 2; i<=N;i++)
			if (is_prime[i])
				for (int j =2*i; j<=N;j+=i)
					is_prime[j]=false;
		for (int i = 2; i<=N;i++)
				if (is_prime[i])
					printf("%d ", i);
		printf("\n");
}
