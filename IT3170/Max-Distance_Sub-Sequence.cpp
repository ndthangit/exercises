/*
Given N elements (2≤ N ≤100,000) on a straight line at positions x
1
,…, x
N
 (0≤ x
i
≤1,000,000,000).
The distance of a subset of N elements is defined to be the minimum distance between two elements.
Find the subset of N given elements containing exactly C elements such that the distance is maximal.
Input
The first line contains a positive integer T (1 <= T <= 20) which is the number of test cases.
Subsequent lines are T test cases with the following format:
Line 1: Two space-separated integers: N and C
Lines 2: contains  x1, x
2
, . . . , x
N

Output
For each test case output one integer: the distance of the subset found.

Example
input
1
5 3
1
2
8
4
9
output
3

Explain: Jonh can put his 3 cows in the stalls at positions 1, 4 and 8, resulting in a minimum distance of 3.
*/
#include<bits/stdc++.h>

using namespace std;
int n, c, numTest;
vector<int> arr;

bool check( int minDis)
{
    int last =1;
    int start =0;
    int dem =1;
    while( last< n)
    {

        if( arr[last]- arr[start] >= minDis)
        {
            start = last;
            dem++;
        }


        last++;
    }
    return dem>=c;
}
int solve(){
     sort(arr.begin(), arr.end());
    int r = arr[n-1]- arr[0];
    int l =0;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l;
}

int main(){

    cin >> numTest;
    while (numTest--) {
        cin >> n >> c;
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cout << solve() << endl;
    }


    return 0;
}
