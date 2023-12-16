#ifndef POURING_H
#define POURING_H

#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
using namespace std;

#define capacity0 10
#define capacity1 7
#define capacity2 4

int bottleMax[3] = {capacity0, capacity1, capacity2};
struct status
{
    int bottle[3];
    //bool visited = false;
};
// vector<status> stateSequence;

status pouring(int start, int finish, vector<status> &stateSequence)
{
    status new_status;
    if (stateSequence.back().bottle[start] + stateSequence.back().bottle[finish] > bottleMax[finish])
    {
        new_status.bottle[finish] = bottleMax[finish];
        new_status.bottle[start] = stateSequence.back().bottle[start] + stateSequence.back().bottle[finish] - bottleMax[finish];
        new_status.bottle[3 - start - finish] = stateSequence.back().bottle[3 - start - finish];
        // stateSequence.push_back(new_status);
    }
    else if (stateSequence.back().bottle[start] + stateSequence.back().bottle[finish] <= bottleMax[finish])
    {
        new_status.bottle[finish] = stateSequence.back().bottle[start] + stateSequence.back().bottle[finish];
        new_status.bottle[start] = 0;
        new_status.bottle[3 - start - finish] = stateSequence.back().bottle[3 - start - finish];
        // stateSequence.push_back(new_status);
    }
    return new_status;
}
bool check_exited(status newStatus, vector<status> &stateSequence)
{
    for (int i = 0; i < stateSequence.size() - 1; i++)
    {
        if (newStatus.bottle[0] == stateSequence[i].bottle[0] && newStatus.bottle[1] == stateSequence[i].bottle[1] && newStatus.bottle[2] == stateSequence[i].bottle[2])
        {
            return true;
        }
    }
    return false;
}
void print(fstream &output, vector<status> &stateSequence)
{

    output << "\ndigraph dfs {\n";
    for (int i = 0; i < stateSequence.size() - 1; i++)
    {
        output << i << "[label=\"(";
        output << stateSequence[i].bottle[0] << "," << stateSequence[i].bottle[1] << "," << stateSequence[i].bottle[2];
        output << ")\""
               << "]"
               << ";" << endl;
    }
    output << stateSequence.size()-1 << "[fillcolor =\"yellow\", style = filled, label=\"(";
    output << stateSequence.back().bottle[0] << "," << stateSequence.back().bottle[1] << "," << stateSequence.back().bottle[2];
    output << ")\""
           << "]"
           << ";" << endl;
    for (int i = 0; i < stateSequence.size() - 1; i++)
    {
        output << i << " -> " << i + 1 << ";" << endl;
    }

    for (int i = 0; i < 1; i++)
    {
        output << "}" << endl;
    }
    exit(1);
}
void dfs(fstream &output, vector<status> &stateSequence)
{
    if (stateSequence.back().bottle[1] == 2 || stateSequence.back().bottle[2] == 2)
    {
        print(output, stateSequence);
        cout << " success";

        // return;
    }

    for (int start = 0; start <= 2; start++)
    {
        for (int finish = 0; finish <= 2; finish++)
        {
            if (start != finish && stateSequence.back().bottle[start] != 0 && stateSequence.back().bottle[finish] != bottleMax[finish])
            {
                status newStatus = pouring(start, finish, stateSequence);
                if (!check_exited(newStatus, stateSequence))
                {
                    stateSequence.push_back(newStatus);
                    // continue;
                    dfs(output, stateSequence);
                    stateSequence.pop_back();
                }
            }
        }
    }
}

#endif