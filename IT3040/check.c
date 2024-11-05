#include <iostream>
using namespace std;
int main()
{
    int a = 10, b = 15;
    int *p = &a, *q = &b;
    a++ = ~a + b;
    p--;
    *p -= a ^ 2;
    cout << a << ", " << b;
}
