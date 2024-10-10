#include<stdio.h>
int main (){
    int n,sum=0;
    int m[n];
    scanf("%d",&n);
    if(n<=0)
    {
        printf("Error");
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        scanf("%d",&m[i]);
    }
    for(int i=n-1;i>=0;i--)
    {
        printf("%d",m[i]);
    }
    for(int i=0;i<n;i++)
    {
       sum=sum+m[i]; 
    }
    printf("\n%d",sum);
return 0;
}