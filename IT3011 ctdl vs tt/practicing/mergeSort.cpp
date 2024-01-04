#include<iostream>
#include<math.h>
using namespace std;
void merge(int array[],int begin,int middle,int end){
    int i = begin;
    int j =middle+1;
    int medium[end+1];
    for (int k = 0; k < end-begin+1; k++)
    {
        if (i> middle)
        {
            medium[k] =array[j];
            j++;
        }else if (j> end)
        {
            medium[k] = array[i];
            i++;
        } else {
            if (array[i] < array[j])
            {
                medium[k]= array[i];
                i++;
            } else{
                medium[k]= array[j];
                j++;
            }
            
        }      
    }
    for (int i = begin; i <= end; i++)
    {
        array[i] = medium[i- begin];
    }
    
};
void mergeSort(int array[],int begin, int end){
    if (begin < end)
    {
        int middle =(begin+end)/2;
        mergeSort(array,begin,middle);
        mergeSort(array,middle+1,end);
        merge(array,begin,middle,end);
    }
    
}
int main(){
    int array[20] ={76,12,97,64,45,9,81,32,58,86,27,93,40,69,62,19,3,90,14,48};
    mergeSort(array,0,19);
    for (int i = 0; i < 20; i++)
    {
        cout<< array[i]<<" ";
    }
    return 0;
}