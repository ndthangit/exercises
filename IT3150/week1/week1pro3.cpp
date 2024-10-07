/*
Given a positive integer n, find all integer having 3 digits which is divisible by n.
Input
Line 1: contains a positive integer n (1 <= n <= 999)
Output
Write the sequence of numbers found (elements are separated by a SPACE character)

Example
Input
200
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int start=100;
    while (start % n != 0)
    {
        start++;
    }
    

    while (start < 1000)
    {
        cout << start << " ";
        start += n;
    }

    return 0;
}