/*
Given a material having the shape rectangle with height H and width W.
We need to cut this material into n smaller rectangle submaterials of size
(h1,w1), (h2, w2), ..., (hn, wn). Write a program to check if we can perform this cut.
Input
Line 1: contains two positive integers H, W (1 <= H, W <= 10)
Line 2: contains a positive integer n (1 <= n <= 10)
Line i+2 (i= 1,...,n): contains two positive integer hi and wi (1 <= hi, wi <= 10)
Output
Write 1 if we can perform the cut and write 0, otherwise.
Example
Input
7 5
4
1 5
6 2
2 2
4 3
Output
1
*/
#include<bits/stdc++.h>
using namespace std;
int heightN, widthN;
int num;
struct SubRectangle {
    int height;
    int width;
};
vector<SubRectangle> subRec;
bool area[10][10];

void mark(int x, int y, int kth, int state, bool value) {
    int h, w;
    if (state == 1) {
        h = subRec[kth].width;
        w = subRec[kth].height;
    } else {
        h = subRec[kth].height;
        w = subRec[kth].width;
    }
    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            area[i][j] = value;
        }
    }
}
bool check(int x, int y, int kth, int state) {
    int h, w;
    if (state == 1) {
        h = subRec[kth].width;
        w = subRec[kth].height;
    } else {
        h = subRec[kth].height;
        w = subRec[kth].width;
    }

    if (x + w > widthN || y + h > heightN) return false;

    for (int i = x; i < x + w; i++) {
        for (int j = y; j < y + h; j++) {
            if (area[i][j]) return false;
        }
    }
    return true;
}

bool solve(int kth) {
    if (kth == num) {
        return true;
    }
    for (int i = 0; i < 2; i++) {
        int h, w;
        if (i == 1) {
            h = subRec[kth].width;
            w = subRec[kth].height;
        } else {
            h = subRec[kth].height;
            w = subRec[kth].width;
        }
        for (int x = 0; x <= widthN - w; x++) {
            for (int y = 0; y <= heightN - h; y++) {
                if (check(x, y, kth, i)) {
                    mark(x, y, kth, i, true);
                    if (solve(kth + 1)) return true;
                    mark(x, y, kth, i, false);
                }
            }
        }
    }
    return false;
}

int main(){

    cin>> heightN>> widthN;

    cin>> num;
    subRec.resize(num);
    memset(area, false, sizeof(area));

    for(int i=0;i<num;i++){
        cin>> subRec[i].height>> subRec[i].width;
    }

    cout<<solve(0);
    return 0;
}
