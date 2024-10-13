#include<stdio.h>
int reallocCub(float ***Mc, int mo, int ro, int co, int mn,int rn,int cn) {
  float ***M = new float **[mn];
  if (M) {
    for(int k=0;k < mo;k++) { 
       M[k] = new float *[rn];
       if (!M[k]) return 0;
       for(i=0;i < rn;i++) {
          M[k][i] = new float [cn];
          if (!M[k][i]) return 0;
          M[k][i][j]= k < mo && i < ro && j < co ? Mc[k][i][j]:0;
       }
     }
     for(int k=0;k < mo;k++)  
       for(i=0;i < rn;i++) 
          delete [] Mc[k][i];
       delete [] Mc[k];
     delete [] Mc
     *Mc=M;
   }
   else return 0;
      }  
int main() {
   int i = 10, *p;
   p = &i;        // p points to the address of i
   i = f(--i, *p--); // --i decrements i to 9, *p returns 10 before p is decremented
   printf("%d\n", i); // i becomes 9 + 10 = 19
   return 0;
}
