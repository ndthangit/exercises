/*bai 5.3 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

int par(string str){
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    int a = str.length();
    stack<char> S;
    char x, y;
    for (int i=0; i<a; i++){
        x = str[i];
        if (x == '(' || x == '[' || x == '{'){
            S.push(x);
        }
        else {
            /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
            if (x == ')') {
                if (S.top() == '('){
                    S.pop();
                }
                else return 0;
            }
            else if (x == ']') {
                if (S.top() == '['){
                    S.pop();
                }
                else return 0;
            }
            else if (x == '}') {
                if (S.top() == '{'){
                    S.pop();
                }
                else return 0;
            }
        }
    }
    if (!S.empty()){
        return 0;
    }
    else return 1;
}
 
int main(){
    int n;
    string str;
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> str;
        cout << par(str) << endl;
    }
    
    return 0;
}
/*bai 5.3 - tuần 17
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/