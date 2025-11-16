#include <stdio.h>

void echange(float *pa, float *pb)
{
    int tmp = *pa;
    *pa = *pb, *pb = tmp;
}

signed main()
{
    float a = 10, b = 20;
    printf("a=%f,b=%f\n", a, b);
    echange(&a, &b);
    printf("a=%f,b=%f\n", a, b);
}