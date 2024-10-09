#include<stdio.h>
int main(){
    // int i=4;
    // int a,b;
    // a=4;
    // b= a;
    // a++;
    int a= 4;
    int *b;
    b=&a;
    (*b)++;
    printf("%d\n",*b);

    printf("%d",a);
}