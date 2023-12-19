#ifndef EXERCISE_H
#define EXERCISE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_set>

using namespace std;

string findASourceVertex(map<string, verticesList> &edgeList)
{
    unordered_set<string> nonSourceVertices;
    for (const auto &word : edgeList)
    {
        nonSourceVertices.insert(word.second.vertex.begin(), word.second.vertex.end());
    }

    for (const auto &word : edgeList)
    {
        if (nonSourceVertices.find(word.first) == nonSourceVertices.end())
        {
            return word.first;
        }
    }

    return "";
}
string findASourceVertex(map<string, verticesList> &edgeList)
{
    for (auto &word1 : edgeList)
    {
        bool isSource = true;
        for (auto &word2 : edgeList)
        {
            if (find(word2.second.vertex.begin(), word2.second.vertex.end(), word1.first) != word2.second.vertex.end())
            {
                isSource = false;
                break;
            }
        }
        if (isSource)
        {
            return word1.first;
        }
    }
    return "";
}

#endif