#include<stdio.h>
#include<math.h>
int main (){
    double a,b,c, denta, t,nl,nn;
    if (a==0||b==0||c==0) 
    {
        printf("phuong trinh vo so nghiem");
        return 0;
    }
    else if(a==0||b==0||c!=0) 
    {
        printf("phuong trinh vo nghiem");
        return 0;
    }
    else if (a==0|| b!=0) printf("%lf",b/c);
    else if (a!=0)
    {
        denta=b*b-4*a*c;
        if(denta<0) 
        {
            denta=-denta;
            t=sqrt(denta);
            printf("%.6lf+%.6lfi",-b/(2*a),t/(2*a));
            printf("%.6lf-%.6lfi",-b/(2*a),t/(2*a));
        }
        else if (denta == 0) printf("%lf", -b/(2*a));
        else 
        {
            t=sqrt(denta);
            nl=(-b+t)/(2*a);
            nn=(-b-t)/(2*a);
            printf("%.6lf",nl);
            printf("\n%.6lf",nn);
        }
        
    }
    
    
    return 0;
    
}