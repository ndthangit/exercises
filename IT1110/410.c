#include<stdio.h>
#include<math.h>
double gt(double x, int n)
    {
        double lt=1;
        for(int i=1; i<=n;i++)
            {
                lt=lt*(x/i);
            }
        return lt;
    }
int main(){
    double x,s=1;
    int n,dau=1;
    scanf("%d %lf",&n,&x);
    if(n<1||x<0)
    {
        printf("Error");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        dau=-dau;
        s+=dau*gt(x,i);
    }
    printf("%.4lf",s);
    return 0;
}