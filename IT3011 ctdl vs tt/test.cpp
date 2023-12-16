#include <iostream>
#include <stack>
#include <vector>

using namespace std;

stack<int> capacity;
vector<int> myArray;

void printArray(vector<int> &myArray)
{
    for (int i = 0; i < myArray.size(); i++)
    {
        cout << myArray[i];
    }
    cout << " ";
}
void solution(int current)
{

    if (myArray[current] == 0)
    {
        for (int i = 1; i <= 2; i++)
        {
            myArray[current] = i;
            if (i == 1)
            {
                capacity.push(1);
            }
            else if (!capacity.empty() && i == 2)
            {
                capacity.pop();
            }

            // print appropiate array
            if (current == myArray.size() - 1 && capacity.empty())
            {
                printArray(myArray);
            }
            else if (current == myArray.size() - 1 && !capacity.empty())
            {
            }
            else
            {
                solution(current + 1);
            }

            myArray[current] = 0;
        }
    }
    else
        solution(current + 1);
}
int main()
{
    int quantityOfElement;
    cin >> quantityOfElement;
    for (int i = 0; i < quantityOfElement; i++)
    {
        int element;
        cin >> element;
        myArray.push_back(element);
    }
    // printArray(myArray);
    solution(0);
    return 0;
}