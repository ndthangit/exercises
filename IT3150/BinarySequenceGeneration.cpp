#include <bits/stdc++.h>
using namespace std;
int arr[1000];

bool check(int n)
{
    // for (int i = 1; i < n; i++)
    // {
    //     if (arr[i] == 1 && arr[i + 1] == 1)
    //     {
    //         return false;
    //     }
    // }
    return true;
}
void printArray(int n)
{
    if (check(n))
    {
        for (int i = 1; i <= n; i++)
        {
            cout << arr[i]<<" ";
        }
        cout << endl;
    }
}
void generateBinarySequence(int k, int n,vector<bool> checkL)
{

    for (int i = 1; i <= n; i++)
    {
        
        if (checkL[i] == false)
        {
            checkL[i] = true;
            arr[k] = i;
            if (k == n)
            {
                printArray(n);
            }
            else{
                generateBinarySequence(k + 1, n, checkL);
            }
            checkL[i] = false;
        }
        
       
    }
}
int main()
{
    int n;
    cin >> n;
    vector<bool> checkL(n + 1, false);
    generateBinarySequence(1, n, checkL);
    return 0;
}