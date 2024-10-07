/*
Perform a sequence of operations over a stack, each element is an integer:
PUSH v: push a value v into the stack
POP: remove an element out of the stack and print this element to stdout (print NULL if the stack is empty)
Input
Each line contains a command (operration) of type
PUSH  v
POP
Output
Write the results of POP operations (each result is written in a line)
Example
Input
PUSH 1
PUSH 2
PUSH 3
POP
POP
PUSH 4
PUSH 5
POP
#
Output
3
2
5
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    stack<int> s;
    string control;

    while (control != "#")
    {
        cin >> control;
        if (control == "PUSH")
        {
            int a;
            cin >> a;
            s.push(a);
        }
        else if (control == "POP")
        {
            if (s.empty())
            {
                cout << "NULL" << endl;
            }
            else
            {
                cout << s.top() << endl;
                s.pop();
            }
        }
    }

    return 0;
}