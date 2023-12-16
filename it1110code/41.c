#include<stdio.h>
#include<string.h>
int main(){
    char a[1000];
    fgets(a,1000,stdin);
    int i,j;
    for(i=0;a[i]==' ';i++);
    for(j=strlen(a)-2;a[j]==' ';j--);
    for(;i<=j;i++)
    {
        if(a[i]==' '&&a[i+1]==' ') 
            continue;
        printf("%c",a[i]);
    }
    return 0;
}