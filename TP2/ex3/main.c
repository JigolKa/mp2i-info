#include<stdio.h>
#include<stdbool.h>
#include<assert.h>

// vérifie si a divise b 
bool divise(int a, int b)
{
		assert(a!=0);
		return b % a == 0;
}

// prend en argument un flottant et affiche son inverse
void inverse(float a)
{
		assert(a!=0);
		printf("a=%f, 1/f=%f\n", a,1./a);
}

// prend en argument 4 flottants
float carre(float x, float y, float z, float t)
{
		float val = 3.*x + 5.*y - 6.25*z+t; // calcule l'équation
		printf("val = %f\n", val);
		return val*val; // renvoie au carré
}

int main()
{
		printf("3 divise 15 = %d\n", divise(3, 15));
		inverse(0.5);
		printf("coordonnées au carré = %f\n", carre(0.5,0.2,3.4,8.2));
}
