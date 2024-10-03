#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;
    vector<int> v(n);
    int numOdd=0;
    int numEven=0;
    for (int i = 0; i < n; i++)
    {
        cin>>v[i];
        if(v[i]%2==0){
            numEven++;
        }
        else{
            numOdd++;
        }
    }
    cout<< numOdd<<" "<< numEven;

    return 0;
}