#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

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
int main()
{

    int x = 2, y = 3, z = 4;
    vidu(y, z, x);
    cout << x <<" "<< y<<" " << z;
    return 0;
}