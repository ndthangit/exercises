#include<bits/stdc++.h>
using namespace std;
int main(){
    string t1,t2, sentence;
    getline(cin,t1);
    getline(cin,t2);
    getline(cin,sentence);
    size_t pos = 0;

    while ((pos = sentence.find(t1, pos)) != string::npos) {
        sentence.replace(pos, t1.length(), t2);
        pos += t2.length();
    }
    cout<<sentence;

    return 0;
}