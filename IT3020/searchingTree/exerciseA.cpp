#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <stack>

using namespace std;

typedef struct verticesList
{
    vector<string> vertex;
} verticesList;

bool check2differentWords(const string &word1, const string &word2)
{
    if (word1.length() != word2.length())
        return false;
    if (word1.compare(word2) == 0)
    {
        return false;
    }

    int different = 0;
    for (int i = 0; i < word1.length(); i++)
    {
        if (word1[i] != word2[i])
        {
            different++;
        }
    }
    if (different == 1)
    {
        return true;
    }
    else
        return false;
}

void setupTree(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList)
{
    for (auto &word1 : visitedEdgeList)
    {
        for (auto &word2 : visitedEdgeList)
        {
            if (check2differentWords(word1.first, word2.first))
            {
                edgeList[word1.first].vertex.push_back(word2.first);
            }
        }
    }
}
void explore(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList, const string currentVertex)
{
    visitedEdgeList[currentVertex] = true;
    for (int i = 0; i < edgeList[currentVertex].vertex.size(); i++)
    {
        if (visitedEdgeList[edgeList[currentVertex].vertex[i]] == false)
        {
            explore(edgeList, visitedEdgeList, edgeList[currentVertex].vertex[i]);
        }
    }
}
int findTheNumberOfConnectedComponent(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList)
{
    map<string, bool> visitedEdgeListCopy = visitedEdgeList;
    // dfs algorithm find the number of connected component
    int coutTheNUmberOfConnectedComponent = 0;
    for (auto &word : visitedEdgeListCopy)
    {
        if (visitedEdgeListCopy[word.first] == false)
        {
            coutTheNUmberOfConnectedComponent++;
            explore(edgeList, visitedEdgeListCopy, word.first);
        }
    }
    return coutTheNUmberOfConnectedComponent;
}

void findTheMinimumPath(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList, const string begin, const string end)
{
    // bfs algorithm find the minimum path from a vertex to another
    map<string, bool> visitedEdgeListCopy = visitedEdgeList;
    queue<string> edgeQueue;
    stack<string> arrayPrint;
    map<string, string> parentMap;
    visitedEdgeListCopy[begin] = true; //
    edgeQueue.push(begin);             //

    while (!edgeQueue.empty())
    {
        string currentVertex = edgeQueue.front();
        edgeQueue.pop();

        if (currentVertex == end) //
        {
            string pathVertex = end; //
            while (pathVertex != begin)
            {
                arrayPrint.push(pathVertex);
                pathVertex = parentMap[pathVertex];
            }
            arrayPrint.push(pathVertex);
            cout << pathVertex << endl;
            cout << "Shortest Path: ";
            while (!arrayPrint.empty())
            {
                cout << arrayPrint.top();
                arrayPrint.pop();
                if (!arrayPrint.empty())
                {
                    cout << " -> ";
                }
            }
            cout << endl;

            return;
        }

        for (const string &vertex : edgeList[currentVertex].vertex)
        {
            if (!visitedEdgeListCopy[vertex])
            {
                visitedEdgeListCopy[vertex] = true;
                parentMap[vertex] = currentVertex;
                edgeQueue.push(vertex);
            }
        }
    }

    cout << "No path found!" << endl;
}
int main()
{
    map<string, bool> visitedEdgeList;
    map<string, verticesList> edgeList;

    ifstream inputFile("sgb-words 3.txt");
    string word;
    while (inputFile >> word)
    {
        visitedEdgeList.insert({word, false});
    }
    inputFile.close();

    setupTree(edgeList, visitedEdgeList);
    string control;
    while (1)
    {
        cout << "Enter a : Finding the quantity of connected component" << endl;
        cout << "Enter b : finding the minimum path from a vertex to another" << endl;
        cout << "Enter # : impeding the program" << endl;
        cout << "what is your control? ";
        getline(cin, control);
        if (control == "a")
        {
            cout << "a)the number of connected component in graph: " << findTheNumberOfConnectedComponent(edgeList, visitedEdgeList) << endl;
        }
        else if (control == "b")
        {
            string begin;
            string end;
            cout << "b)find the minimum path from a vertex to another" << endl;
            cout << "begin vertex: ";
            getline(cin, begin);
            cout << "end vertex: ";
            getline(cin, end);

            findTheMinimumPath(edgeList, visitedEdgeList, begin, end);
        }
        else if (control == "#")
        {
            break;
        }
    }
    // cout << visitedEdgeList["spumy"] << endl;
    return 0;
}
