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
// #include <stdio.h>
// int main()
// {
// 	// khai bao mang 2 chieu a gom 3 x 3 phan tu
// 	int a[3][3] = {
// 		{1, 2, 3},
// 		{4, 5, 6},
// 		{7, 8, 9},
// 	};
// 	// khoi tao con tro p cho mang a[3][3]
// 	int(*p)[3];

// 	p = a;

// 	printf("Cac phan tu trong mang la so chan \n");
// 	// duyet cac hang trong mang
// 	for (int i = 0; i < 3; i++)
// 	{
// 		// duyet cac cot trong mang
// 		for (int j = 0; j < 3; j++)
// 		{
// 			if (*(*(p + i) + j) % 2 == 0)
// 			{
// 				// hien thi gia tri cac phan tu la so chan
// 				printf("Gia tri: a[%d][%d] =%d \n", i, j, *(*(p + i) + j));
// 			}
// 		}
// 	}
// }

// #include<stdio.h>
// 	int f(int a, int b) {
// 	  return b-a;
// 	}
// 	int main() {
// 	   int A[] = {2, 4, 6, 8,10} ;
// int *p = &A[3];
// *p-- =5; *p += 2;
// p += 2; *p += 2;
// for (size_t i = 0; i < 5; i++)
// {
// 	printf("%d ", A[i]);
// }

// 	   return 0;
// 	}
// #include<stdio.h>
//  int main(){
//    char s1[]="abc", *s2="abc";
//     // s1[1]='X'; s2=s1;
// 	// gets(s1); s1[1]=s2[1];
// 	// s2=s1; gets(s2);
// 	*(s1+1)='X'; s2[1]='X';
// 	printf("%s %s",s1,s2);
//     return 0;
//  }

// #include<stdio.h>
// 	int f(int a, int b) {
// 	  return b+a;
// 	}
// 	int main() {
// 	    int j,i[5] = {3,5,7,9,11}, *p;
// 	   p=i+1;
// 	   j= f(*i, *p++);
// 	   printf("%d\n", j);
// 	   return 0;
// 	}
// #include<stdio.h>
// 	int f(int a, int b) {
// 	  return b+a;
// 	}
// 	int main() {
// 	   int i = 10, *p;
// 	   p=&i;
// 	   i= f(i, --*p);
// 	   printf("%d\n", i);}
// 	 int M[2][3];
// 	 int i =2,j =6;
// 	 *(*(M+i)+j) = 17;
// 	 printf("%d",sizeof(M));
// 	   return 0;
// 	}
// #include <stdio.h>
// int f(int a, int b)
// {
// 	return b - a;
// }
// int main()
// {
// 	int i = 10, *p;
// 	p = &i;
// 	i = f(--i, *p);
// 	printf("%d\n", *p);
// 	return 0;
// }

// #include <stdio.h>
// int main()
// {
// 	float x = 2.5;
// 	char *p = &x;
// 	printf("%d\n", *(p + 3));
// 	return 0;
// }

// #include <stdio.h>
// int main()
// {
// 	float i = 10, *j;
// 	void *k;
// 	k = &i;
// 	j = k;
// 	printf("%.2f\n", *j);
// 	return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #define INCREMENT(x) ++x
// int main()
// {
// 	char *ptr = "DHBK-HN";
// 	int x = 10;
// 	printf("%s  ", INCREMENT(ptr + 1));
// 	printf("%d", INCREMENT(1 + x));
// 	return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// char* increment_ptr(char* ptr) {
//     return ptr + 1;
// }

// int increment_int(int x) {
//     return x + 1;
// }

// int main() {
//     char *ptr = "DHBK-HN";
//     int x = 10;

//     // Tăng con trỏ để lấy phần chuỗi từ vị trí thứ hai
//     printf("%s  ", increment_ptr(ptr+1));

//     // Tăng giá trị của x
//     printf("%d", increment_int(x+1));

//     return 0;
// }

// #include <stdio.h>
// int f(int a, int b)
// {
// 	return b + a;
// }
// int main()
// {
// 	int j, i[5] = {10, 12, 14, 16, 18}, *p, *q;
// 	p = i;
// 	q = p;
// 	*q = f(i[0], *p++);
// 	printf("%d %d \n", *p, *q);
// 	return 0;
// }

// #include <stdio.h>
// int main()
// {
// 	int x = 6;
// 	printf("%c", (x >= 5) ? (x >= 7) ? (x >= 9) ? 'A' : 'B' : 'C' : 'D');
// 	return 0;
// }

// #include <stdio.h>
// int main()
// {
// 	float i = 10, *j;
// 	void *k;
// 	k = &i;
// 	j = k;
// 	printf("%.2f\n", *j);
// 	return 0;
// }

// #include <stdio.h>
// int sum(int a, int b)
// {
//     return a + b;
// }
// int main()
// {

//     printf("%d\n", sum(2.7, 4.8));
//     return 0;
// }
// #include<stdio.h>
// void ktra( int *a,int *b, int c){
//     *((*a+1==1)?b:a) = *a?*b:c;
// }
// int main(){
//     int a=1,b=2,c=0;
//     ktra(&c,&a,b);
//     printf("%d %d %d",a,b,c);
//     return 0;
// }
// #include <stdio.h>
// void foo(int *a, int b, int &c)
// {
//     a += 5;
//     b += 6;
//     c += 7;
// }
// int main()
// {
//     int a = 5, b = 6, c = 7;
//     foo(&b, c, &a);
//     printf("%d %d %d", a, b, c);
//     return 0;
// }