
/*
Write a program to compute the number of sudoku solutions (fill the zero elements of a given partial sudoku table)
Fill numbers from 1, 2, 3, .., 9 to 9 x 9 table so that:
Numbers of each row are distinct
Numbers of each column are distinct
Numbers on each sub-square 3 x 3 are distinct
Input
Each line i (i = 1, 2, ..., 9) contains elements of the i
th
 row of the Sudoku table: elements are numbers from 0 to 9 (value 0 means the empty cell of the table)
Output
Write the number of solutions found

Example
Input
0 0 3 4 0 0 0 8 9
0 0 6 7 8 9 0 2 3
0 8 0 0 2 3 4 5 6
0 0 4 0 6 5 0 9 7
0 6 0 0 9 0 0 1 4
0 0 7 2 0 4 3 6 5
0 3 0 6 0 2 0 7 8
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
Output
64

*/

#include <bits/stdc++.h>
using namespace std;

bool check(vector<vector<int>> &table, int row, int column, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (table[row][i] == num || table[i][column])
        {
            return false;
        }
    }
    int startRow = row - row % 3;
    int startCol = column - column % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (table[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}
void countSudokuSolution(vector<vector<int>> &table, int row, int column, int &count)
{
    if (row == 8 && column == 9)
    {
        count++;
        return;
    }
    if (column == 9)
    {
        row++;
        column = 0;
    }
    if (table[row][column] > 0)
    {
        countSudokuSolution(table, row, column + 1, count);
        return;
    }

    for (int i = 1; i < 10; i++)
    {
        if (check(table, row, column, i))
        {
            table[row][column] = i;
            countSudokuSolution(table, row, column + 1, count);
            table[row][column] = 0;
        }
    }
}
int main()
{

    vector<vector<int>> table(9, vector<int>(9));
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> table[i][j];
        }
    }
    int count=0;
    countSudokuSolution(table, 0, 0, count);
    cout<< count;
    return 0;
}