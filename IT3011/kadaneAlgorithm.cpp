#include <iostream>
using namespace std;
int main()
{

    // create an array
    cout << " enter the quantity of element in an array: ";
    int quantityOfElements;
    cin >> quantityOfElements;

    int array[quantityOfElements];
    for (int i = 0; i < quantityOfElements; i++)
    {
        cout << "enter the element " << i << ":";
        cin >> array[i];
    }

    // algorithm
    int sum1 = 0;
    int sum2 = 0;
    int firstPositiveElement = 0;
    for (firstPositiveElement = 0; array[firstPositiveElement] <= 0; firstPositiveElement++)
        ;
    // kadane algorithm
    for (; firstPositiveElement < quantityOfElements; firstPositiveElement++)
    {
        sum1 = sum1 + array[firstPositiveElement];
        if (sum1 > sum2)
        {
            sum2 = sum1;
        }
    }
    // print
    cout << "the maximum sum of substring of array: " << sum2 << endl;
}