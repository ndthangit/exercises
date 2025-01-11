#include <stdio.h>
void hoanvi(int *px, int *py)
{
    int z;
    z = *px;
    *px = *py;
    *py = z;
};
void main()
{
    int a = 35, b = 61;
    hoanvi(a, b);
    printf("%d%d", a, b);
};