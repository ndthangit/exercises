#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int countWords(const string &text)
{
    int wordCount = 0;
    bool inWord = false;
    for (char c : text)
    {
        if (!isspace(c))
        {
            if (!inWord)
            {
                inWord = true;
                wordCount++;
            }
        }
        else
        {
            inWord = false;
        }
    }
    return wordCount;
}

int main()
{
    string inputText;
    int n = 20;

    int sum = 0;
    while (n > 0)
    {
        getline(cin, inputText);
        int wordCount = countWords(inputText);
        sum += wordCount;
        n--;
    }
    cout << sum;
    return 0;
}
