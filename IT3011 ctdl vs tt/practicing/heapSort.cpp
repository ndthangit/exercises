#include <iostream>
using namespace std;
void swap(int &element1, int &element2)
{
    int tmp;
    tmp = element1;
    element1 = element2;
    element2 = tmp;
}
void makeHeap(int array[], int elementSituation, int quantityElement)
{
    int leftChild = 2 * elementSituation+1;
    int rightChild = 2 * elementSituation + 2;
    int max = elementSituation;
    if (leftChild < quantityElement && array[leftChild] > array[elementSituation])
    {
        max = leftChild;
    }
    if (rightChild < quantityElement && array[rightChild] > array[max])
    {
        max = rightChild;
    }
    if (max != elementSituation)
    {
        swap(array[elementSituation], array[max]);
        makeHeap(array, max, quantityElement);
    }
}
void buildHeap(int array[], int quantityElement)
{
    for (int i = quantityElement / 2 -1; i >= 0; i--)
    {
        makeHeap(array, i, quantityElement);
    }
}
void heapSort(int array[], int quantityElement)
{
    buildHeap(array, quantityElement);
    for (int i = quantityElement-1; i >= 1; i--)
    {
        swap(array[0], array[i]);
        makeHeap(array, 0, i );
    }
}
int main()
{
    int array[20] = {76, 12, 97, 64, 45, 9, 81, 32, 58, 86, 27, 93, 40, 69, 62, 19, 3, 90, 14, 48};
    heapSort(array, 19);
    // swap(array[0],array[1]);
    //makeHeap(array,1,19);
    //buildHeap(array,19);
    for (int i = 0; i < 20; i++)
    {
        cout << array[i] << " ";
    }
    return 0;
}