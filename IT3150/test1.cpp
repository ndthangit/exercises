#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

void vidu(int x, int &y, int &z)
{
    x += 10;
    y += 15;
    z += 2;
}
int main()
{

    int x = 2, y = 3, z = 4;
    vidu(y, z, x);
    cout << x <<" "<< y<<" " << z;
    return 0;
}