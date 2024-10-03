#include <bits/stdc++.h>
using namespace std;
int getHour(string input)
{
    return 10 * (input[0] - '0') + input[1] - '0';
}
int getMinutes(string input)
{
    return 10 * (input[3] - '0') + input[4] - '0';
}
int getSeconds(string input)
{
    return 10 * (input[6] - '0') + input[7] - '0';
}
void solve(string input)
{
    if (input[2] != ':' || input[5] != ':')
    {
        cout << "INCORRECT";
        return;
    }

    int hours, minutes, seconds;
    hours = getHour(input);
    minutes = getMinutes(input);
    seconds = getSeconds(input);
    if (hours > 24 || minutes > 59)
    {
        cout << "INCORRECT";
        return;
    }
    cout << 3600 * hours + 60 * minutes + seconds;
}
int main()
{
    string input;
    cin >> input;
    solve(input);
    return 0;
}