#include<bits/stdc++.h>
using namespace std;
int n;
int arr[1000];

void print(){
    for( int i=0;i<n;i++){
        cout<< arr[i];
    }
    cout<< endl;
}

void solve(int k)
{
    if( k== n){
        print();
        return;
    }
    for( int i=0; i<2; i++)
    {
        arr[k]= i;
        solve(k+1);

    }
}
int main()
{
    cin >> n;
    solve(0);


    return 0;
}
