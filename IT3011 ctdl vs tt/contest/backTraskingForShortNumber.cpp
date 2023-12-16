#include<iostream>
#include<math.h>
using namespace std;

int rangeOfCapacity;
bool used[100000];
int permutation[100000];

void show(int rangeOfCapacity){
    for (int i = 0; i < rangeOfCapacity; i++)
    {
        cout << permutation[i] << " ";
    }
    cout << endl;
}

void backTracking(int position){
    if (position == rangeOfCapacity){
        show(rangeOfCapacity);
        return;
    }
    for (int i = 1; i <= rangeOfCapacity; i++){
        if (used[i] == false){
            permutation[position] = i;
            used[i] = true;
            backTracking(position + 1);
            used[i] = false;
        }
    }
}

int main(){
    cin >> rangeOfCapacity;
    backTracking(0);
}