/*
Problem: Replace ? To Find Real Expression
Description
Viết chương trình thực hiện công việc sau:
Một biểu thức chứa các kí tự ngoặc mở '(' hoặc ngoặc đóng ')' được gọi là biểu thức ngoặc đúng nếu chúng đóng mở hợp lý, ví dụ biểu thức (()) hoặc ()() đều là biểu thức ngoặc đúng. Với đầu vào là một xâu kí tự độ dài n lưu trong dãy a1, a2, ..., an
 gồm 3 số 0, 1, 2 ứng với 3 loại kí tự là dấu hỏi '?' hoặc  kí tự ngoặc mở '(' hoặc ngoặc đóng ')' , yêu cầu in ra tất cả các trường hợp là biểu thức ngoặc đúng khi thay kí tự dấu hỏi bằng ngoặc đóng hoặc ngoặc mở dưới dạng các con số tương ứng.
Ví dụ 1002 ứng với (??) sẽ in ra 1122 và 1212 ứng với (()) và ()().
Input
Dòng 1: ghi số nguyên dương n (1 <= n <= 100)
Dòng 2: ghi các số nguyên dương a
Output
Ghi ra dãy các biểu thức ngoặc đúng
-----------------------------------
Example:
Input
4
1 0 0 2
Output
1122 1212

4
0 0 0 0
*/
#include <iostream>
#include <vector>

using namespace std;

vector<int> myArray;

void printArray(vector<int> &printArray)
{
    for (int i = 0; i < printArray.size(); i++)
    {
        cout << printArray[i];
    }
    cout << " ";
}
void solution(int current, int capacity)
{
    if (myArray[current] == 0)
    {
        for (int i = 1; i <= 2; i++)
        {
            myArray[current] = i;
            if (i == 1)
            {
                capacity++;
            }
            else if (i == 2 && capacity > 0)
            {
                capacity--;
            }
            else if (i == 2 && capacity <= 0)
            {
                myArray[current] = 0;
                continue;
            }

            if (current == myArray.size() - 1)
            {
                // printArray(myArray);
                if (capacity == 0)
                {
                    printArray(myArray);
                }
            }
            else
            {
                solution(current + 1, capacity);
            }

            if (i == 1)
            {
                capacity--;
            }
            else if (i == 2)
            {
                capacity++;
            }
            myArray[current] = 0;
        }
    }
    else
    {
        if (myArray[current] == 1)
        {
            capacity++;
        }
        else if (myArray[current] == 2)
        {
            capacity--;
        }

        if (current == myArray.size() - 1)
        {
            // printArray(myArray);
            if (capacity == 0)
            {
                printArray(myArray);
            }
        }
        else
        {
            solution(current + 1, capacity);
        }
        if (myArray[current] == 1)
        {
            capacity--;
        }
        else if (myArray[current] == 2)
        {
            capacity++;
        }
    }
}


// if (myArray[current] == 0)
// {
//     for (int i = 1; i <= 2; i++)
//     {
//         myArray[current] = i;
//         if (i == 1)
//         {
//             capacity.push(10);
//             cout << "add" << endl;
//         }
//         else if (!capacity.empty() && i == 2)
//         {
//             capacity.pop();
//             cout << "remove" << endl;
//         }

//         // print appropiate array
//         if (current == myArray.size() - 1 && capacity.empty())
//         {
//             cout << capacity.empty() << " ";
//             printArray(myArray);
//             cout << "accepted"
//                  << " ";
//         }
//         else if (current == myArray.size() - 1 && !capacity.empty())
//         {
//             cout << capacity.empty() << " ";
//             printArray(myArray);
//         }
//         else
//         {
//             //capacity.pop();
//             solution(current + 1);
//             //myArray[current] = 0;
//         }

//     }
//     myArray[current] = 0;
// }

// else
// {

//     solution(current + 1);
//     //myArray[current] = 0;
// }
//}

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
    // cout<< myArray.size();
    // printArray(myArray);
    solution(0, 0);
    return 0;
}