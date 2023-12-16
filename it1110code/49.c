//giải thích ác bước tình toán của đoạn code sau với x=3 n=4:
#include <stdio.h>
#include <math.h>

int main(){
    double x,can;
    int n, i=1;
    scanf("%lf%d",&x,&n);
    if(n<1||x<0)
    {
        printf("Error");
        return 0;
    }   
    can=sqrt(x);
    for(i=1; i<n;i++)
    {
       
        can=sqrt(x+can);
            
    }
    printf("%.4lf",can);
    return 0;
}