#include<stdio.h>
#include<string.h>
#include <stdlib.h>
void hoan_vi(float *x, float *y){
     float z;
     z=*x; 
     *x=*y;
     *y=z;
}
int main(){
     float x,y; x=4.1; y=5.2;
     hoan_vi(&x,&y);
     printf("%0.2f %0.2f",x,y);
}
