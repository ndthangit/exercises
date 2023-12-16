#include<stdio.h>
#include<math.h>
int main(){
    int a, b, ucln,bcnn,tich;
    scanf("%d\n%d",&a ,&b);
    if(a<=0 ||b<=0)
    {
        printf("ERROR");
        return 0;
    }
    tich=a*b;
    while(a*b!=0)
    {
        if (a>b)
            a=a%b;
        else
            b=b%a;
    }
    ucln=a+b;
    bcnn=tich/ucln;
    printf("%d",ucln);
    printf("\n%d",bcnn);
    
    return 0;
}