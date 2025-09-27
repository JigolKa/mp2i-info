#include<stdio.h>
#include<stdlib.h>
#define ll long int
#define max(a,b) a>b?a:b

ll suivant(ll x)
{
		return x%2==0? x/2 : 3*x+1;
}

ll syracuse(ll x, int n)
{
		if (n<0)
			return x;

		return syracuse(suivant(x), n-1);
}

ll temps_de_vol(ll x, ll* memo, ll N)
{
		if (x == 1)
				return 0;
	
		if (x>N)
			return temps_de_vol(suivant(x), memo, N) + 1;

		if (memo[x] != -1)
				return memo[x];

		return memo[x] = temps_de_vol(suivant(x),memo,N) + 1;
}

ll plus_long_temps_de_vol(ll N)
{
		ll *memo = (ll*)malloc(sizeof(ll)*(N+1));
		//fill(memo,-1, memo+N+1);
		for (int i = 1; i<=N;i++)
			memo[i]=-1; //printf("i=%d,memo[i]=%ld\n",i,memo[i]);
		memo[0]=0;

		ll maxi = -1;
		for (int i = 1; i<=N;i++)
				maxi = max(maxi, temps_de_vol(i, memo, N));
		return maxi;
}

int main()
{
		int n;
		ll x,N;
		/*printf("X N = "); 2e question
		scanf("%ld %d", &x, &n);
		printf("%d-ième terme de la suite = %ld\n", n, syracuse(x,n));*/

		/*printf("X = "); 3e question
		scanf("%ld", &x);
		printf("temps de vol de %ld = %ld\n", x, temps_de_vol(x));*/

		printf("N = ");
		scanf("%ld",&N);
		printf("max temps de vol = %ld\n", plus_long_temps_de_vol(N));
}
