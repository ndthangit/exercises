// #include<stdio.h>
// int f(int a, int b) {
// return b+a;
//  }
//  int main() {
// int i = 10, *p;
//  p=&i;
// i= f(i--, (*p)--);
//  printf("%d\n", i);
//  return 0;
//  }
// // 19

// #include<stdio.h>
// 	int main() {
// 		int x=9;
// 		printf("%c",(x>=5)?(x>=7)?(x>=9)? 'A':'B':'C':'D');
// 		return 0;
// 	} 

// #include<stdio.h>
// 	int f(int a, int b) {
// 	  return b+a;
// 	}
// 	int main() {
// 	   int i = 10, *p;
// 	   p=&i;
// 	    i= f(i--, (*p)--);
// 	   printf("%d\n", i);
// 	   return 0;
// 	} 
// #include<stdio.h>
// 	int main() {
// 	   float x=2.5;
// 	   char *p=&x;
// 	   printf("%d\n",*p);
// 	   return 0;
// 	} 
#include<stdio.h>
	int f(int a, int b) {
	  return b+a;
	}
	int main() {
	   int i = 10, *p;
	   p=&i;
	    i= f(i--, (*p)--);
	   printf("%d\n", i);
	   return 0;
	} 

