#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int main()
{
    string s;
    int n = 400;

    while (n > 0)
    {
        getline(cin, s);

        for (char &c : s)
        {
            c = toupper(c);
        }
        cout << s << endl;

        n--;
    }

    return 0;
}