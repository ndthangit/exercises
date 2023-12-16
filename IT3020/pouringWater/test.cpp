#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int alreadyExist[11][8][5] = {0};
int bottleMax[4] = {0, 10, 7, 4};
int tempFrom = 0, tempTo = 0;

struct node
{
    int bottle[4];
    int begin;
    int end;
};
node condition;

void pouring(int start, int finish, vector<node> &stateSequence)
{
    if (stateSequence.back().bottle[start] + stateSequence.back().bottle[finish] > bottleMax[finish])
    {
        condition.bottle[start] = stateSequence.back().bottle[start] + stateSequence.back().bottle[finish] - bottleMax[finish];
        condition.bottle[finish] = bottleMax[finish];
        condition.bottle[6 - start - finish] = stateSequence.back().bottle[6 - start - finish];
        condition.begin = start;
        condition.end = finish;

        stateSequence.push_back(condition);
    }

    else if (stateSequence.back().bottle[start] + stateSequence.back().bottle[finish] <= bottleMax[finish])
    {

        condition.bottle[finish] = stateSequence.back().bottle[start] + stateSequence.back().bottle[finish];
        condition.bottle[start] = 0;
        condition.bottle[6 - start - finish] = stateSequence.back().bottle[6 - start - finish];
        condition.begin = start;
        condition.end = finish;
        stateSequence.push_back(condition);
    }
    tempFrom = start;
    tempTo = finish;
};
void printSolution(vector<node> &stateSequence)
{
    ofstream dotFile;
    dotFile.open("graph.txt", ios::trunc);
    dotFile << "graph Graph {\n";
    for (int k = 0; k < stateSequence.size(); k++)
    {
        dotFile << k << " [color = yellow, style = filled, label = \"" << stateSequence[k].bottle[1] << ", " << stateSequence[k].bottle[2] << ", " << stateSequence[k].bottle[3] << "\"];\n";
    }
    for (int h = 0; h < stateSequence.size() - 1; h++)
    {
        dotFile << h << " -- " << h + 1 << ";" << endl;
    }
    dotFile << "}";
    dotFile.close();
    cout << "FOUND SUCCESSFULLY!!!";
}
void dfsSearching(vector<node> &stateSequence)
{

    if (stateSequence.back().bottle[2] == 2 || stateSequence.back().bottle[3] == 2)
    {
        printSolution(stateSequence);
        exit(0);
    }

    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            if (i != j && stateSequence.back().bottle[j] < bottleMax[j] && stateSequence.back().bottle[i] > 0)
            {
                if (tempFrom != j || tempTo != i)
                {
                    pouring(i, j, stateSequence);
                    if (alreadyExist[stateSequence.back().bottle[1]][stateSequence.back().bottle[2]][stateSequence.back().bottle[3]] == 0)
                    {
                        alreadyExist[stateSequence.back().bottle[1]][stateSequence.back().bottle[2]][stateSequence.back().bottle[3]] = 1;
                        dfsSearching(stateSequence);
                        alreadyExist[stateSequence.back().bottle[1]][stateSequence.back().bottle[2]][stateSequence.back().bottle[3]] = 0;
                    }
                    stateSequence.pop_back();
                }
            }
        }
    }
}

int main()
{
    node status;
    status.bottle[1] = 0;
    status.bottle[2] = 7;
    status.bottle[3] = 4;

    vector<node> stateSequence;
    stateSequence.push_back(status);
    alreadyExist[stateSequence.back().bottle[1]][stateSequence.back().bottle[2]][stateSequence.back().bottle[3]] = 1;

    dfsSearching(stateSequence);
    return 0;
}