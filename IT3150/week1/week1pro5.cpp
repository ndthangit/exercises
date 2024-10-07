#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

int main()
{
    string s;
    
    while (true)
    {

        getline(cin, s);

        for (char &c : s)
        {
            c = toupper(c);
        }
        cout << s << endl;

        if (s == "*****")
        {
            break;
        }
        else if (s[0] == 'B')
        {
            if (s[1] == 'E')
            {

                continue;
            }
            break;
        }
        else if (s[0] == 'W')
        {
            if (s[5] == 'D')
            {
                continue;
            }
            getline(cin, s);
            if (s[0] >= 'A' && s[0] <= 'Z')
            {
                for (char &c : s)
                {
                    c = toupper(c);
                }
                cout << s << endl;
                continue;
            }

            cout << endl;

            getline(cin, s);
            if (s[0] == 'W' || s[0] == 'C')
            {
                for (char &c : s)
                {
                    c = toupper(c);
                }
                cout << s << endl;
                continue;
            }
            else
            {
                break;
            }
            // break;
        }
    }

    return 0;
}