/*
Given a material having the shape rectangle with height H and width W. We need to cut this material into
n smaller rectangle submaterials of size (h1,w1), (h2, w2), ..., (hn, wn). Write a program to check if we can perform this cut.
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

int rec[11][11];
struct material
{
    int height,weight;
};
int H,W,n;
vector<material> listMaterial;


void mark(material c,int a, int b, int xoay, int value)
{
    int h, w;
    if ( xoay ==0)
    {
        h= c.height;
        w =  c.weight;
    }
    else
    {
        w= c.height;
        h =  c.weight;
    }
    for(int i=a; i<a+w; i++)
    {
        for( int j=b; j<b+h; j++)
        {
            rec[i][j]= value;
        }
    }
}

bool check(material a, int x, int y,int xoay)
{
    int h, w;
    if ( xoay ==0)
    {
        h= a.height;
        w =  a.weight;
    }
    else
    {
        w= a.height;
        h =  a.weight;
    }

    if(x+w>W|| y+h>H) return false;

    for(int i=x; i<x+w; i++)
    {
        for( int j=y; j<y+h; j++)
        {
            if(rec[i][j]) return false;
        }
    }

    return true;
}

bool solve( int subTH )
{
    if( subTH== n) return true;

    for( int i=0; i<2; i++)
    {
        int h, w;
        if ( i ==0)
        {
            h= listMaterial[subTH].height;
            w =  listMaterial[subTH].weight;
        }
        else
        {
            w= listMaterial[subTH].height;
            h =  listMaterial[subTH].weight;
        }
        for(int x=0;x<=W-w;x++){
            for( int y=0;y<=H-h;y++){
                if(check(listMaterial[subTH],x,y,i)){
                    mark(listMaterial[subTH],x,y,i,1);
                    if(solve(subTH+1)) return true;
                    mark(listMaterial[subTH],x,y,i,0);
                }
            }
        }

    }

    return false;
}


int main()
{
    cin>>H>>W>>n;
    memset(rec,0,sizeof(rec));
    for( int i=0; i<n; i++)
    {
        material a;
        cin>> a.height>>a.weight;
        listMaterial.push_back(a);
    }
    cout<< solve(0);
    return 0;
}
