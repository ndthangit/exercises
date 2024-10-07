/*
Given a string containing only characters (, ), [, ] {, }. Write a program that checks whether the string is correct in expression.
Example
 ([]{()}()[]): correct
 ([]{()]()[]): incorrect
Input
One line contains the string (the length of the string is less than or equal to $10^6$)One line contains the string (the length of the string is less than or equal to 10
6
)
Output
Write 1 if the sequence is correct, and write 0, otherwise
Example
Input
(()[][]{}){}{}[][]({[]()})
Output
1
*/
#include <bits/stdc++.h>
using namespace std;
bool check(string s)
{
    stack<char> a;
    long length = s.length();
    if(length==0){
        return 1;
    }
    if(length%2!=0){
        return 0;
    }

    long point=0;
    while (point<length)
    {
        if(s[point]== '(' || s[point]=='{'||s[point]=='['){
            a.push(s[point]);
        }
        else if(s[point]==')'){
            if(a.empty()||a.top()!='('){
                return 0;
            }
            a.pop();
        }
        else if(s[point]=='}'){
            if(a.empty()||a.top()!='{'){
                return 0;
            }
            a.pop();
        }
        else if(s[point]==']'){
            if(a.empty()||a.top()!='['){
                return 0;
            }
            a.pop();
        }
        point++;
    }
    if(a.empty()){
        return 1;
    }
    
}
int main()
{
    string s;
    cin >> s;
    cout << check(s);
    return 0;
}