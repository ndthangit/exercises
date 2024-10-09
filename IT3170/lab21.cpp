#include<bits/stdc++.h>

using namespace std;
int n,m;
int a[1000];
int dem;
int solution[1000];
int sum;
int rangeMin[1000];
void check(){
    if(sum == m) dem++;
    return;
}

void solve(int point){
    for(int i=1;i< (m -sum -(rangeMin[n]-rangeMin[point]) )/a[point];i++){
        solution[point] =i;
        sum+= a[point]*solution[point];
        if(point==n-1){
            check();
        }
        else{
            solve(point +1);
        }

        sum-= a[point]*solution[point];

    }
}
int main(){
    cin>> n >>m;
    for(int i=0;i<n;i++){
        cin>> a[i];
    }
    for(int i=1;i<n;i++){
        rangeMin[i]= rangeMin[i-1] + a[i];
    }
    sum=0;
    dem=0;


    solve(0);
    cout<< dem;
    return 0;
}
