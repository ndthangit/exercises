#include<bits/stdc++.h>
using namespace std;
int n, q;
const int mod = 1e9+7;
const int N= 1e4+5;
int dem =0;
int a[N];
int main()
{
    cin>> n>> q;
    for( int i=1; i<=n; i++)
    {
        cin>> a[i];
    }
    sort(a+1, a+n+1);
    for( int j =2; j< n; j++)
    {
        int i= 1, k=n;

        while( i< j && j< k)
        {
            int sum = a[i]+a[j]+a[k];



            if( sum ==q)
            {
                int l=1, r=1;
                while(i<j && a[i]== a[i+1])
                {
                    i++;
                    l++;
                }

                while( j<k && a[k] == a[k-1])
                {
                    k--;
                    r++;
                }

                dem += l*r;
                k--;
                i++;
            }
            else if( sum > q)
            {
                k--;
            }
            else
            {
                i++;
            }
        }


    }
    cout<< dem;


}
