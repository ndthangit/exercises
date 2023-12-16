#include<iostream>
#include<math.h>
using namespace std;
int range;
int location[10000];// 10000 presents for the location of a specific column
bool check(int row, int column){
    for (int currentColumn = 1; currentColumn < column; currentColumn++)
    {
        if (location[currentColumn] == row) return false;
        if (row -location[currentColumn] ==  column - currentColumn) return false;
        if (row - location[currentColumn] == currentColumn - column) return false;;
    }
    return true;
}
int ordinalSolution = 0;
void printToScreen(){
    ordinalSolution++;
    cout<< ordinalSolution <<":";
    for (int i = 1; i <= range; i++)
    {
        cout << location[i]<< " ";
    }
    
    cout<< endl;
    
}
void backTracking(int column){
    for (int row = 1; row <= range; row++)
    {
        if (check(row, column))
        {
            location[column] = row;
            if (column == range){               
                printToScreen();
            } else backTracking( column +1);            
        }        
    }    
}

int main(){
    cin >> range; 
    backTracking(1);
}