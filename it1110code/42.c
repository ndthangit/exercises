#include<stdio.h>
#include<math.h>
int main(){
    int a;
    scanf("%d",&a);
if(a==2 || a== 3){ 
    printf(" la so nguyen to");
    return 0;
} else if (a<2)
{
    printf("khong la so nguye to");
    return 0;
} else if (a>3)
{
    for(int i=2;i<=sqrt(a);i++)
    {
        if(a%i ==0){
        printf("khong la so nguyen to");
        return 0;}
    }
}
printf("la so nguyen to");
    return 0;
}