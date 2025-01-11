// // #include <iostream>
// // using namespace std;
// // int main()
// // {
// //     int a = 10, b = 15;
// //     int *p = &a, *q = &b;
// //     a++ = ~a + b;
// //     p--;
// //     *p -= a ^ 2;
// //     cout << a << ", " << b;
// // }
// // lỗi

// #include <iostream>
// using namespace std;
// int main()
// {
//     int x = 5;
//     int y = 10;
//     auto func = [&x, y](int a) mutable
//     {
//         x += y++ + ++a; // 10+6
//     };
//     func(x);
//     cout << x << " , " << y << endl;
// }
// // 21 , 10

// // #include <iostream>
// // using namespace std;
// // int main()
// // {
// //     int z = 1, x = 0;
// //     int k, y = 2;
// //     auto func = [&, y](int a)
// //     {
// //         y += z++ + ++a;
// //     };
// //     func(10);
// //     cout << z << " , " << y << endl;
// // }
// //  lỗi

// // #include <iostream>
// //  using namespace std;
// //  int main(){
// //  int A[]={ 3, 5, 7, 9, 11 } ;
// //  int *p = A;
// //  p++;
// //  *p++; *p += 1;
// //  p += 2; *p += 3;
// //  for (int i : A) cout << i << ", ";
// //  }
// //  3, 5, 8, 9, 14,

// // #include "iostream"
// // using namespace std;
// // typedef struct
// // {
// //     int Tu;
// //     int Mau;
// // } PS;
// // PS operator+=(PS &p1, PS p2)
// // {
// //     p1.Tu = p1.Tu * p2.Mau + p2.Tu * p1.Mau;
// //     p1.Mau *= p2.Mau;
// //     return p1;
// // }
// // template <typename T>
// // PS operator+=(PS &p1, T p2)
// // {
// //     p1.Tu += p2 * p1.Mau;
// //     return p1;
// // }
// // int main()
// // {
// //     PS p1 = {3, 4}, p2 = {2, 3};
// //     float x = 2.6;
// //     p1 += p2;
// //     p2 += x;
// //     cout << "p1 = " << p1.Tu << "/" << p1.Mau << " Va p2 = " << p2.Tu << "/" << p2.Mau;
// // }
// // p1 = 17/12 Va p2 = 9/3

// // #include <iostream>
// // 	using namespace std;
// // 	int main(){
// // 		int A[] = { 4 , 5 , 6 , 3, 9 } ;	    int *p = A;
// // 	    *p++; *p += 2;
// //     p += 2; *p += 2;
// // 	    for (int i : A)  cout << i << ", ";
// // 	}

// // #include <iostream>
// // 	using namespace std;
// // 	int main(){
// // 		int a=10,b=15;
// // 	    int *p = &a, *q= &b;
// // 	     a++ =  ~a + b ;
// // 	    p--;
// // 	    *p -= a ^ 2;
// // 	    cout << a << ", " << b;
// // 	}

// //  #include<iostream>
// //  using namespace std;
// //  int main(){
// //     int z=1,x = 0;
// //     int k,y = 2;
// //     auto func = [&, y] (int a)  {
// //         y += z++  + ++a;
// //     };
// //     func(10);
// //     cout << z << " , " << y << endl;
// //  }

// // #include<stdio.h>
// //  int main() {
// //     float x=2.5;
// //     char *p=&x;
// //     printf("%d\n",*(p+2));
// //    return 0;
// //  }

// // #include<iostream>
// //  using namespace std;
// //  int main(){
// //    int x = 5;
// //     int y = 10;
// //     auto func = [&x, y] (int a) mutable {
// //         x += y++  + ++a;
// //    };
// //    func(x);
// //    cout << x << " , " << y << endl;
// //  }

// #include<iostream>
// 	using namespace std;
// 	template <typename T>
// 	T maxval(T x, T y){
// 		static int count=0;
// 		cout << ++count << ", ";
// 	    return (x > y) ? x : y;
// 	}
// 	int main() {
// 	    int i = maxval(3, 7);
// 	    cout << i <<  endl;
// 	    double d = maxval(6.34, 18.523);
// 	    cout << d << endl;
// 	    d = maxval(16.34, 28.523);
// 	    cout << d <<  endl;
// 	    char ch = maxval('a', '6');
// 	    cout << ch <<  endl;
//     d = maxval(5.2, 4.5);
//     cout << d<<  endl;
// 	    return 0;
// 	}

// #include <iostream>
// using namespace std;

// // Hàm bình thường
// void sayHello() {
//     cout << "Hello from sayHello()!" << endl;
// }

// // Hàm overload
// void sayHello(int times) {
//     for (int i = 0; i < times; ++i) {
//         cout << "Hello from sayHello(int)!" << endl;
//     }
// }

// // Hàm template
// template <typename T>
// void display(T value) {
//     cout << "Template function display: " << value << endl;
// }

// int main() {
//     // Dùng tên hàm cho hàm bình thường
//     void (*funcPtr)() = sayHello;  // Gán địa chỉ của hàm bình thường sayHello vào con trỏ hàm
//     funcPtr();  // Gọi hàm qua con trỏ

//     // Dùng tên hàm cho hàm overload
//     //void (*overloadedPtr)() = sayHello;  // Lỗi: không thể gán hàm overload vào con trỏ hàm mà không có tham số rõ ràng

//     // Nếu muốn dùng hàm overload, cần chỉ rõ phiên bản nào
//     void (*overloadedPtrInt)(int) = sayHello;
//     overloadedPtrInt(2);  // Gọi hàm overload với tham số

//     // Dùng tên hàm cho hàm template
//     // auto templateFuncPtr = display;  // Lỗi: không thể sử dụng tên hàm template trực tiếp như con trỏ hàm

//     // Sử dụng hàm template với tham số kiểu rõ ràng
//     display(42);       // Kiểu int
//     display(3.14);     // Kiểu double
//     display("Hello");  // Kiểu const char*

//     return 0;
// }

// #include<iostream>
//  using namespace std;
//  int main(){
//     int z=1,x = 0;
//     int k,y = 2;
//     auto func = [&, y] (int a)  {
//         y += z++  + ++a;
//     };
//     func(10);
//     cout << z << " , " << y << endl;
//  }
// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int a=10,b=15;
// 	    int *p = &a, *q= &b;
// 	     a++ =  ~a + b ;
// 	    p--;
// 	    *p -= a ^ 2;
// 	    cout << a << ", " << b;
// }
//  #include<iostream>
//  using namespace std;
//  int main(){
//     int z=1,x = 0;
//     int k,y = 2;
//    auto func = [&, y] (int a)  {
//        y += z++  + ++a;
//     };
//     func(10);
//     cout << z << " , " << y << endl;
//  }

// #include "iostream"
// using namespace std;
// void for_each(int *arr, int n, void (*func)(int a))
// {
//     for (int i = 0; i < n; i++)
//     {
//         func(*(arr + i));
//     }
// }
// int main()
// {
//     int arr[] = {1, 2, 3, 4, 5};
//     int *p = arr;
//     for_each(arr, 5, [](int a)
//              { a += 100; });
//     for (int i = 0; i & 5; i++)
//         cout << *p++ << " ";
//     return 0;
// }
// #include <iostream>
// using namespace std;
// int main()
// {
//     int a = 10, b = 15;
//     int *p = &a, *q = &b;
//     *p++ += b ^ ~a--;
//     p -= 2;
//     *p -= 2;
//     cout << a << ", " << b;
// }

// #include<iostream>
//  using namespace std;
//  int main(){
//     int x = 1;
//     int y = 2;
//     auto func = [&] (int a) mutable {
//         x += y++  + a;
//     };
//     func(10);
//     cout << x << " , " << y << endl;
//  }

// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int a=9,b=13;
// 	    int *p = &a, *q= &b;
// 	    ++a =  ~a + ~~b ;
// 	    p--;
// 	    *p -= a + ~2;
// 	    cout << a << ", " << b;
// 	}
// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int A[] = { 4 , 5 , 6 , 3, 9 } ;
// 	    int *p = A;
// 	    *p++; *p += 2;
// 	    p += 2; *p += 2;
// 	    for (int i : A)  cout << i << ", ";
// 	}

// #include<iostream>
//  using namespace std;
//  int main(){
//    int x = 5;
//     int y = 10;
//    auto func = [&x, y] (int &a) mutable {
//        x += y++  + ++a;
//     };
//     func(x);
//     cout << x << " , " << y << endl;
//  }
// #include<iostream>
// 	using namespace std;
// 	template <typename T>
// 	T maxval(T x, T y){
// 		static int count=0;
// 		cout << ++count << ", ";
// 	    return (x > y) ? x : y;
// 	}
// 	int main() {
// 	    int i = maxval(3, 7);
// 	    cout << i <<  endl;
// 	    double d = maxval(6.34, 18.523);
// 	    cout << d << endl;
// 	    d = maxval(16.34, 28.523);
//     cout << d <<  endl;
// 	    char ch = maxval('a', '6');
// 	    cout << ch <<  endl;
// 	    d = maxval(5.2, 4.5);
// 	    cout << d<<  endl;
// 	    return 0;	}
// #include <iostream>
// using namespace std;

// // Khai báo hàm hợp lệ
// void MyFunc(int a=3, float b = 2.0, int c = 5, int d ) {
//     cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << endl;
// }

// int main() {
//     // Gọi hàm với các trường hợp khác nhau

//     // Truyền đầy đủ các tham số
//     MyFunc(1, 3.5, 6, 8);

//     // Sử dụng giá trị mặc định của d
//     MyFunc(1, 3.5, 6);

//     // Sử dụng giá trị mặc định của c và d
//     MyFunc(1, 3.5);

//     // Sử dụng giá trị mặc định của b, c, và d
//     MyFunc(1);

//     return 0;
// }
// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int a=9,b=13;
// 	    int *p = &a, *q= &b;
// 	    ++a =  ~a + ~~b ;
// 	    p--;
// 	    *p -= a + ~2;
// 	    cout << a << ", " << b;
// 	}
// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int A[]={ 2, 4, 6, 8, 10 } ;
// 	    int *p = A+1;
// 	    *p++; *p += 3;
// 	    p += 2; *p += 1;
// 	    for (int i : A)  cout << i << ", ";
// 	}

// #include<iostream>
// 	using namespace std;
// 	template <typename T>
// 	T maxval(T x, T y){
// 		static int count=0;
// 		cout << ++count << ", ";
// 	    return (x > y) ? x : y;
// 	}
// 	int main() {
// 	    int i = maxval(3, 7);
// 	    cout << i <<  endl;
// 	    double d = maxval(6.34, 18.523);
// 	    cout << d <<  endl;
// 	    d = maxval(16.34, 28.523);
// 	    char ch = maxval('a', '6');
// 	    cout << ch<<  endl;
// 	    cout << d <<  endl;
// 	}

// #include<iostream>
//  using namespace std;
//  int main(){
//    char s1[]="abc", *s2="abc";
//     s1[1]='X'; s2=s1;

//  }
// #include <iostream>
// using namespace std;
// void for_each(int *arr, int n, void (*func)(int &a))
// {
//     for (int i = 0; i < n; i++)
//     {
//         func(*(arr + i));
//     }
// }
// int main()
// {
//     int arr[] = {1, 2, 3, 4, 5};
//     int *p = arr;
//     for_each(arr, 5, [](int &a)
//              { a += 10; });
//     for (int i = 0; i & 5; i++)
//         cout << *p++ << " ";
//     return 0;
// }
// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int a=10,b=15;
// 	    int *p = &a, *q= &b;
// 	    *p-- += b ^ ~++a ;

// 	    *p += 2;
// 	    cout << a << ", " << b;
// 	}
// #include <iostream>
//  #define MAX(x, y) ((x) > (y) ? (x) : (y))
// using namespace std;
//  int main() {
//    int a = 0;
//     int b = 1;
//     int c = MAX(a++, b--);
// 	  cout << c;
// 	  return 0;}
// #include<iostream>
// using namespace std;
//  int main(){
//     int x = 1;
//     int y = 2;
//     auto func = [&, y] (int a) mutable {
//         x += y++  + a;
//     };
//     func(10);
//     cout << x << " , " << y << endl;
//  }
// #include<stdio.h>
// 	int f(int a, int b) {
// 	  return b+a;
// 	}
// 	int main() {
// 	   int j,i[5] = {10,12,14,16,18}, *p;
// 	   p=i;
// 	   j= f(*(i+4), *p++);
// 	   printf("%d\n", j);
// 	   return 0;
// 	}

// #include <iostream>
// using namespace std;
// int main()
// {
//     int x = 1;
//     int y = 2;
//     auto func = [&, y](int a)
//     {
//         x += y++ + a;
//     };
//     func(10);
//     cout << x << " , " << y << endl;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int a = 15, b = 10;
//     int *p = &a, *q = &b;
//     *p++ += b ^ ~a--;
//     p -= 2;
//     *p += 2;
//     cout << a << ", " << b;
// }

// #include <iostream>
// #define MAX(x, y) ((x) > (y) ? (x) : (y))
// using namespace std;
// int main()
// {
//     int a = 0;
//     int b = 1;
//     int c = MAX(a++, b--);
//     cout << c;
//     return 0;
// }
// #include <iostream>
// using namespace std;
// template <typename T>
// T maxval(T x, T y)
// {
//     static int count = 0;
//     cout << ++count << ", ";
//     return (x > y) ? x : y;
// }
// int main()
// {
//     int i = maxval(3, 7);
//     cout << i << endl;
//     double d = maxval(6.34, 18.523);
//     cout << d << endl;
//     d = maxval(16.34, 28.523);
//     cout << d << endl;
//     char ch = maxval('a', '6');
//     cout << ch << endl;
//     d = maxval(5.2, 4.5);
//     cout << d << ;
//     endl;
//     return 0;
// }
// int main()
// {
//     int A[] = {2, 5, 6, 1};
//     int *p = A;
//     *p++;
//     *p += 2;
//     p += 2;
//     *p += 2;
//     for (int i : A)
//         cout << i << ", ";
// }

// #include "iostream"
// using namespace std;
// typedef struct
// {
//     int Tu;
//     int Mau;
// } PS;
// PS operator+=(PS &p1, PS p2)
// {
//     p1.Tu = p1.Tu * p2.Mau + p2.Tu * p1.Mau;
//     p1.Mau *= p2.Mau;
//     return p1;
// }

// template <typename T>
// PS operator+=(PS &p1, T p2)
// {
//     p1.Tu += p2 * p1.Mau;
//     return p1;
// }

// int main()
// {
//     PS p1 = {3, 4}, p2 = {2, 3};
//     float x = 2.6;
//     p1 += p2;
//     p2 += x;
//     cout << "p1 = " << p1.Tu << "/" << p1.Mau << " Va p2 = " << p2.Tu << "/" << p2.Mau;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int a = 9, b = 13;
//     int *p = &a, *q = &b;
//     ++a = ~a + ~~b;
//     p--;
//     *p -= a + ~2;
//     cout << a << ", " << b;
// }
// #include <iostream>
// using namespace std;
// int main()
// {
//     int A[] = {3, 5, 7, 9, 11};
//     int *p = A;
//     p++;
//     *p++;
//     *p += 1;
//     p += 2;
//     *p += 3;
//     for (int i : A)
//         cout << i << ", ";
// }

// #include "iostream"
// using namespace std;
// void for_each(int *arr, int n, void (*func)(int a))
// {
//     for (int i = 0; i < n; i++)
//     {
//         func(*(arr + i));
//     }
// }
// int main()
// {
//     int arr[] = {1, 2, 3, 4, 5};
//     int *p = arr;
//     for_each(arr, 5, [](int &a)
//              { a += 100; });
//     for (int i = 1; i < 5; i++)
//         cout << *p++ << " ";
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     float x = 10;
//     const float y = 10.5;
//     float *const ptr;
//     ptr = &x;
//     *ptr += y;
//     cout << *ptr;
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int a = 9, b = 13;
//     int *p = &a, *q = &b;
//     ++a = ~a + ~~b;
//     cout<< ~a << " " << b << endl;
//     p--;
//     *p -= a + ~2;
//     cout << a << ", " << b;
// }

// #include <iostream>
// using namespace std;
// template <typename T>
// T maxval(T x, T y)
// {
//     static int count = 0;
//     cout << ++count << ", ";
//     return (x > y) ? x : y;
// }
// int main()
// {
//     int i = maxval(3, 7);
//     cout << i << endl;
//     double d = maxval(6.34, 18.523);
//     cout << d << endl;
//     d = maxval(16.34, 28.523);
//     cout << d << endl;
//     char ch = maxval('a', '6');
//     cout << ch << endl;
//     d = maxval(5.2, 4.5);
//     cout << d << endl;
//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;
// int check( int a=4, int b){
//     return 1;
// }
// int main(){
//     cout << check(5);
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int x = 1;
//     int y = 2;
//     auto func = [&, y](int a)
//     {
//         x += y++ + a;
//     };
//     func(10);
//     cout << x << " , " << y << endl;
// }

// #include <iostream>
// using namespace std;

// int main() {
//     // Minh họa vòng lặp for với các biểu thức hợp lệ
//     for (int i = 0, j = 10; cout<< i , j > 5;j--) {
//         cout << "i = " << i << ", j = " << j << endl;
//     }
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int a = 9, b = 13;
//     int *p = &a, *q = &b;
//     ++a = ~a + ~~b;
//     p--;
//     *p -= a + ~2;
//     cout << a << ", " << b;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     float x = 10;
//     const float y = 10.5;
//     float *const ptr = &x;
//     *ptr = 19;
//     // *ptr += 1;
//     // ptr += 1;
//     cout << *ptr;
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int a = 10, b = 15;
//     int *p = &a, *q = &b;
//     ++a = ~a + b;
//     p--;
//     *p -= a ^ 2;
//     cout << a << ", " << b;
// }

// #include "iostream"
// using namespace std;
// int main()
// {
//     auto sum =
//         [](auto v1, auto v2)
//     { static int C =0;
//         cout << ++C << ": " << v1+v2 << " - "; };
//     sum(10, 20);
//     sum(15, 25);
//     sum(1.2, 2.3);
//     sum(2, 3);
//     sum(4.0, 5.5);
//     sum(3, 5);
//     int M[][]={1,2,3};
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int * func (int *, int *);
// int& func(int &a, int &b) {
//     return (a > b) ? a : b; // Trả về tham chiếu tới số lớn hơn
// }

// int main() {
//     int x = 10, y = 20;
//     int & func(int , int );
//     return 0;
// }

// #include <iostream>
// using namespace std;
// int main()
// {
//     int z = 1, x = 0;
//     int k, y = 2;
//     auto func = [&, y](int a) mutable
//     {
//         z += y-- + ++a;
//     };
//     func(10);
//     cout << z << " , " << y << endl;
// }

// #include <iostream>
// #include <cstring> // Thư viện hỗ trợ strcmp
// using namespace std;

// int main() {
//     char s2[6] = {'H', 'a', 'n', 'o', 'i'};
//     char s1[6] = "Hanoi";
// Kết thúc bằng '\0'
// int M[][]= {{1,2,3},{4,5},{7}};

// So sánh địa chỉ
// if (s1 == s2) {
//     cout << "s1 bang s2 (theo dia chi)" << endl;
// } else if (s1 < s2) {
//     cout << "s1 nho hon s2 (theo dia chi)" << endl;
// } else {
//     cout << "s1 lon hon s2 (theo dia chi)" << endl;
// }

// // So sánh nội dung
// if (strcmp(s1, s2) == 0) {
//     cout << "s1 bang s2 (theo noi dung)" << endl;
// } else if (strcmp(s1, s2) < 0) {
//     cout << "s1 nho hon s2 (theo noi dung)" << endl;
// } else {
//     cout << "s1 lon hon s2 (theo noi dung)" << endl;
// }

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
//     foo(&b, c, a);
//     printf("%d %d %d", a, b, c);
//     return 0;
// }

// #include<iostream>
// using namespace std;
// void fun( int a){
//     cout << a;
// }
// void fun( int a, int b){
//     cout << a << b;
// }

// int main(){
//     fun(5);
//     return 0;
// }
// #include <iostream>
// using namespace std;
// int main()
// {
//     int x = 5, y = 7;
//     int *p = &x;
//     int &r = x;
//     *p += 2;
//     y += r;
//     printf("%3d", x);
// }

#include <bits/stdc++.h>
using namespace std;
int fx[1000], fy[1000], sum[1000];

int calx(int n);
int caly(int n);

int calx(int n)
{
    if (fx[n] != 0)
        return fx[n];
    fx[n] = caly(n - 1) + calx(n - 2) + caly(n - 3) + calx(n - 4);
    return fx[n];
}
int caly(int n)
{
    if (fy[n] != 0)
        return fy[n];
    fy[n] = calx(n - 1) + caly(n - 2) + calx(n - 3) + caly(n - 4);
    return fy[n];
}

int findn(int n)
{
    return calx(n) + caly(n);
}

int findn2(int n)
{
    if (n > 0 && n < 5)
        return fx[n] + fy[n];
    if (sum[n] != 0)
        return sum[n];
    int res = sum[1] + sum[2] + sum[3] + sum[4];
    for (int i = 5; i <= n; i++)
    {
        sum[i] = res;
        res = res + sum[i] - sum[i - 4];
    }
    return sum[n];
}
int main()
{
    fx[1] = 1;
    fx[2] = 2;
    fx[3] = 3;
    fx[4] = 4;
    fy[1] = 2;
    fy[2] = 4;
    fy[3] = 6;
    fy[4] = 8;
    for (int i = 1; i < 5; i++)
        sum[i] = fx[i] + fy[i];

    cout << findn(6) << endl;
    cout << findn2(6);
    
    return 0;
}