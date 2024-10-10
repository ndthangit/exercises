#include<iostream>
using namespace std;
int main (){
    
    long quantityOfElements;
    cin>> quantityOfElements;

    int array[quantityOfElements];
    for (int i = 0; i < quantityOfElements; i++)
    {
        cin>> array[i];
    }

    int sum1 = 0;
    int sum2 = 0;
    int firstPositiveElement = 0;
    for ( firstPositiveElement = 0; array[firstPositiveElement]<= 0; firstPositiveElement++); 
    for (; firstPositiveElement < quantityOfElements; firstPositiveElement++)
    {
        sum1 = sum1 + array[firstPositiveElement];
        if (sum1 < 0) sum1 =0;
        if (sum1 > sum2)
        {
            sum2 = sum1;
        } 
    }
    cout<< sum2 << endl;
}