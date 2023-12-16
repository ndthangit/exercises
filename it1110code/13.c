#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
int so_tu_nhien(char c){
	if(c>='0'&&c<='9')return 1;
	return 0;
}
int main(){
	char s[10000],p[10000];
	int a[2][10],b[2][10],C[21],c[20],cnt1=0,cnt2=0,i,j,k,tg1,tg2;
	for(j=0;j<2;j++){
		for(i=0;i<10;i++){
			a[j][i]=0;
			b[j][i]=0;
		}
	}
	printf("hay nhap vao hai da thuc de thuc hien tinh tong \n");
    gets(s);
    gets(p);
    for(i=0;i<strlen(s);i++){
    	if(s[i]=='x')cnt1++;
	}
	for(i=0;i<strlen(p);i++){
    	if(p[i]=='x')cnt2++;
	}
	i=0;
	for(k=0;k<cnt1;k++){
    	for(;i<strlen(s);i++){
    		if(so_tu_nhien(s[i])){
    			a[0][k]=a[0][k]*10+s[i]-48;
			}
    		else if(a[0][k]>0)break;
		}
		for(;i<strlen(s);i++){
			if(so_tu_nhien(s[i])){
				b[0][k]=b[0][k]*10+s[i]-48;
			}
			else if(b[0][k]>0)break;
		}
    }
    i=0;
    for(k=0;k<cnt2;k++){
    	for(;i<strlen(p);i++){
    		if(so_tu_nhien(p[i])){
    			a[1][k]=a[1][k]*10+p[i]-48;
			}
    		else if(a[1][k]>0)break;
		}
		for(;i<strlen(p);i++){
			if(so_tu_nhien(p[i])){
				b[1][k]=b[1][k]*10+p[i]-48;
			}
			else if(b[1][k]>0)break;
		}
    }
    i=0;
    for(;i<cnt1;i++){
    	C[i]=a[0][i];
    	c[i]=b[0][i];
	}
	for(;i<cnt1+cnt2;i++){
		C[i]=a[1][i-cnt1];
		c[i]=b[1][i-cnt1];
	}
	for(i=0;i<cnt1+cnt2-1;i++){
		for(j=i+1;j<cnt1+cnt2;j++){
			if(c[i]==c[j]){
				C[i]+=C[j];
				C[j]=0;
				c[j]=0;
			}
		}
	}
	for(i=0;i<cnt1+cnt2-1;i++){
		for(j=i+1;j<cnt1+cnt2;j++){
			if(c[i]<c[j]){
				tg1=c[i];
				tg2=C[i];
				c[i]=c[j];
				C[i]=C[j];
				c[j]=tg1;
				C[j]=tg2;
			}
		}
	}
	C[cnt1+cnt2]=0;
	for(i=0;i<cnt1+cnt2;i++){
		if(C[i]!=0){
			printf("%d*x^%d",C[i],c[i]);
			if(C[i+1])printf("+");
		}
	}
return 0;
}