#include<iostream>
using namespace std;
int main()
{
    long long n;
    cin>>n;
    long long arr[n];
    for(long long i=0;i<n;i++)
    {
        cin>> arr[i];
    }
    long long tag;
    cin>>tag;
    long long request[tag][2];
    for(long long i=0;i<tag;i++)
    {
        cin>>request[i][0]>>request[i][1];
    }

    long long s[n+1];
    s[0]=0;
    s[1]=arr[0];
    for (long long i = 2; i < n+1; i++)
    {
        s[i]= s[i-1]+arr[i-1]; 
        // cout<<s[i]<<endl;
    }
    
    
    for(long long i=0;i<tag;i++)
    {
        
        long long sum = s[request[i][1]]-s[request[i][0]-1];
        cout<<sum<<endl;
    } 
    return 0;
}