#include<iostream>
using namespace std;
int main()
{
    long long n, m;
    cin>>n>> m;
    long long arr[n][m];
    for(long long i=0;i<n;i++)
    {
        for (long long j = 0; j < m; j++)
        {
            cin>> arr[i][j];
        }
        
    }
    long long tag;
    cin>>tag;
    long long request[tag][4];
    for(long long i=0;i<tag;i++)
    {
        cin>>request[i][0]>>request[i][1]>>request[i][2]>>request[i][3];
    }

    long long s[tag][m+1];
    
   
    return 0;
}