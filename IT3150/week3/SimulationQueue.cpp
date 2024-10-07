/*
Perform a sequence of operations over a queue, each element is 
an integer:
PUSH v: push a value v into the queue
POP: remove an element out of the queue and print this element 
to stdout (print NULL if the queue is empty)
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
1
2
3

Input
PUSH 1
POP
POP
PUSH 4
POP
#
Output
1
NULL
4
*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    queue<int> s;
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
                cout << s.front() << endl;
                s.pop();
            }
        }
    }

    return 0;
}