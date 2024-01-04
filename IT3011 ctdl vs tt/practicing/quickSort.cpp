#include <iostream>
using namespace std;
void swap(int &element1, int &element2)
{
    int tmp;
    tmp = element1;
    element1 = element2;
    element2 = tmp;
}
int partition(int array[], int begin, int end, int pivotSituation)
{
    int pivot = array[pivotSituation];
    swap(array[pivotSituation], array[end]);
    int indexSituation = begin;
    for (int i = begin; i < end; i++)
    {
        if (array[i] < pivot)
        {
            swap(array[i], array[indexSituation]);
            indexSituation++;
        }
    }
    swap(array[end], array[indexSituation]);
    return indexSituation;
}
void quickSort(int array[], int begin, int end)
{
    if (begin < end)
    {
        int index = (begin + end) / 2;
        index = partition(array, begin, end, index);
        if (begin < index)
        {
            quickSort(array, begin, index - 1);
        }
        if (index < end)
        {
            quickSort(array, index + 1, end);
        }
    }
}
int main()
{
    int array[20] = {76, 12, 97, 64, 45, 9, 81, 32, 58, 86, 27, 93, 40, 69, 62, 19, 3, 90, 14, 48};
    quickSort(array, 0, 19);
    for (int i = 0; i < 20; i++)
    {
        cout << array[i] << " ";
    }
    return 0;
}