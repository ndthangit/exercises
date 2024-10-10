#include<iostream>

using namespace std;

void transport(int numberOfDisk, char departure ,char destination){
    cout << "Transport " << numberOfDisk << " from " << departure << " to " << destination << endl;
}

void solution(int numberOfDisk, char departure, char transitStation, char destination){
    if (numberOfDisk == 1) {
        transport(1, departure, destination);
    } else {
        solution(numberOfDisk-1, departure, destination, transitStation);
        transport(numberOfDisk, departure, destination);
        solution(numberOfDisk-1, transitStation, departure, destination);
    }
}

int main(){
    int numberOfDisk;
    cout << "Enter number of disks: ";
    cin >> numberOfDisk;

    solution(numberOfDisk, 'A', 'B', 'C');
}
