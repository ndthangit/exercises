#include <iostream>
#include <set>
using namespace std;

int main()
{

    int n, m;
    cin >> n >> m;
    multiset<int> myMultiset;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        myMultiset.insert(a);
    }
    int count = 0;
    
    while (myMultiset.size() >1)
    {
        if (*myMultiset.begin() + *myMultiset.rbegin() == m)
        {
            myMultiset.erase(myMultiset.begin());
            myMultiset.erase(std::prev(myMultiset.end()));
            count++;
        }
        else
        {
            if (*myMultiset.begin() + *myMultiset.rbegin() < m)
            {
                myMultiset.erase(myMultiset.begin());
            }
            else
            {
                myMultiset.erase(std::prev(myMultiset.end()));
            }
        }
    }
    cout << count << endl;

    return 0;
    
}