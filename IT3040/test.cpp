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

// //  #include<iostream>
// //  using namespace std;
// //  int main(){
// //  int x = 5;
// //  int y = 10;
// //  auto func = [&x, y] (int a) mutable {
// //  x += y++ + ++a;
// //  };
// //  func(x);
// //  cout << x << " , " << y << endl;
// //  }
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

// // #include <iostream>
// // using namespace std;

// // // Hàm bình thường
// // void sayHello() {
// //     cout << "Hello from sayHello()!" << endl;
// // }

// // // Hàm overload
// // void sayHello(int times) {
// //     for (int i = 0; i < times; ++i) {
// //         cout << "Hello from sayHello(int)!" << endl;
// //     }
// // }

// // // Hàm template
// // template <typename T>
// // void display(T value) {
// //     cout << "Template function display: " << value << endl;
// // }

// // int main() {
// //     // Dùng tên hàm cho hàm bình thường
// //     void (*funcPtr)() = sayHello;  // Gán địa chỉ của hàm bình thường sayHello vào con trỏ hàm
// //     funcPtr();  // Gọi hàm qua con trỏ

// //     // Dùng tên hàm cho hàm overload
// //     //void (*overloadedPtr)() = sayHello;  // Lỗi: không thể gán hàm overload vào con trỏ hàm mà không có tham số rõ ràng

// //     // Nếu muốn dùng hàm overload, cần chỉ rõ phiên bản nào
// //     void (*overloadedPtrInt)(int) = sayHello;
// //     overloadedPtrInt(2);  // Gọi hàm overload với tham số

// //     // Dùng tên hàm cho hàm template
// //     // auto templateFuncPtr = display;  // Lỗi: không thể sử dụng tên hàm template trực tiếp như con trỏ hàm

// //     // Sử dụng hàm template với tham số kiểu rõ ràng
// //     display(42);       // Kiểu int
// //     display(3.14);     // Kiểu double
// //     display("Hello");  // Kiểu const char*

// //     return 0;
// // }

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


//  #include "iostream"
//  using namespace std;
//  void for_each (int *arr, int n, void (*func)(int a)){
//     for (int i = 0; i < n; i++)	{
//        func(*(arr + i));
//    }
//  }
//  int main(){
//     int arr[] ={1, 2, 3, 4, 5} ;
//     int *p=arr;
//     for_each(arr, 5, [] (int a){
//        a += 100;
//    });
//    for(int i=1;i <= 5;i++) cout << *p++ << " ";
//    return 0;
//  }
// #include <iostream>
// 	using namespace std;
// 	int main(){
// 		int a=15,b=10;
// 	    int *p = &a, *q= &b;
// 	    *p++ += b ^ ~a-- ;
// 	    p-=2;
// 	    *p += 2;
// 	    cout << a << ", " << b;  
// 	}

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
#include <iostream>
	using namespace std;
	int main(){
		int a=9,b=13;
	    int *p = &a, *q= &b;
	    ++a =  ~a + ~~b ;
	    p--;
	    *p -= a + ~2;
	    cout << a << ", " << b;  
	}
