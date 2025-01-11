#include<bits/stdc++.h>
using namespace std;
long n;
struct seg
{
    long a,b;
};


vector<seg> segs;
int main()
{
    cin>> n;
    for( int i=0; i<n; i++)
    {
        seg c;
        cin>>c.a>>c.b;
        segs.push_back(c);
    }

    sort(segs.begin(), segs.end(),[]( const seg &x, const  seg &y)
    {
        if(x.b != y.b) return x.b< y.b;
        else return x.a< y.a;
    });
//    for( auto & x : segs) cout<< x.a<<" "<<x.b<< endl;

    long last =-1;
    long dem =0;
    for(auto & i : segs){
        if(i.a>last){
            dem++;
            last= i.b;
        }
    }
    cout<< dem;
    return 0;
}
