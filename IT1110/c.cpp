#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t>0){
		int n;
		cin>>n;
		int a[n],i;
		int b[1000000];
		for(i=0;i<n;i++){
			cin>>a[i];
			if(a[i]>0)b[a[i]]=1;
		}
		for(i=1;;i++){
			if(b[i]==0){
				cout<<i<<endl;
				break;
			}
		}
	}
	return 0;
}