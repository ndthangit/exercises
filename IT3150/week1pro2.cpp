#include <bits/stdc++.h>
#include <string>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    string s;
    cin >> s;
    if (s == "*")
    {
        while (true)
        {
            string s;
            cin >> s;
            if (s == "***")
            {
                break;
            }
            else if (s == "find-max")
            {
                // find max
                int max = v[0];
                for (int i = 1; i < n; i++)
                {
                    if (v[i] > max)
                    {
                        max = v[i];
                    }
                }
                cout << max << endl;
            }
            else if (s == "find-min")
            {
                // find min
                int min = v[0];
                for (int i = 1; i < n; i++)
                {
                    if (v[i] < min)
                    {
                        min = v[i];
                    }
                }
                cout << min << endl;
            }
            else if (s == "find-max-segment")
            {
                int i, j;
                cin >> i >> j;
                // find max segment
                int max = v[i];
                for (int k = i+1; k <= j; k++)
                {
                    if (v[k] > max)
                    {
                        max = v[k];
                    }
                }
                cout << max << endl;
            }
            else if (s == "sum")
            {
                int sum = 0;
                for (int i = 0; i < n; i++)
                {
                    sum += v[i];
                }
                cout << sum << endl;
            }
        }
        return 0;
    }
}