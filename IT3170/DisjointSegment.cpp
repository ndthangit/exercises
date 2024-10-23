/*Given a set of segments X = {(a
1
, b
1
), . . . , (a
n
, b
n
)} in which ai < bi are coordinates of the segment i on a line, i = 1, …, n.  Find a subset of X having largest cardinality in which no two segments of the subset intersect
Input
Line 1: contains a positive integer n (1 <= n <= 100000)
Line i+1 (i= 1,...,n): contains ai and bi (0 <= a
i
 <= b
i 
<= 1000000)
Output
Number of segments in the solution found.
Example
Input
6
0 10
3 7
6 14
9 11
12 15
17 19

Output
4*/
#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;
int n;
vector<pii> arr;

bool compare(pii a,pii b){ return a.second < b.second;}

void solve(){
    int last =-1;
    int dem =0;
    for( int i=0; i<n;i++){
        if( arr[i].first> last){
            dem++;
            last= arr[i].second;
        }
    }
    cout<< dem;
}

int main(){
    cin>> n;
    arr.resize(n);
    for(int i=0; i<n;i++){
        cin>> arr[i].first>> arr[i].second;
    }
    sort(arr.begin(), arr.end(), compare);
    solve();
    return 0;
}
