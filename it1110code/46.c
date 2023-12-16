#include<stdio.h>
#include<math.h>
int main (){
    int i=1;
    double n,x,s,sh;
    s=sh=1;
    scanf("%lf%lf",&n,&x);
    if (n<=0 || ceil(n) != floor(n))
    {
        printf("ERROR");
        return 0;
    }
    for( i; i<=n;i++)
    {
        sh=sh*x;
        s= s+sh;
    }
    
    printf("%lf",s);
    return 0;
}