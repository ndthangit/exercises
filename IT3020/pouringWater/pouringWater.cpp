#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include "pouringWater.h"
using namespace std;

int main()
{
    vector<status> stateSequence;

    fstream output;
    output.open("result.dot", ios ::out);

    status begin_status;
    begin_status.bottle[0] = 0;
    begin_status.bottle[1] = 7;
    begin_status.bottle[2] = 4;
    stateSequence.push_back(begin_status);
    //cout<< stateSequence[0].bottle[1];
    dfs(output, stateSequence);
    output.close();
    return 0;
}