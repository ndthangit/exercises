#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

int main() {
   char a[100],result[100];
   printf("nhap chuoi: ");
   fgets(a,100,stdin);
   char *p=a,*q;
   while (q= strtok(p,"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"))
   {
         p=NULL;
         printf("%s\n",q);
   }
   printf("check");

   return 0;
}