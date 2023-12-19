#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <cstddef>
#include <stack>
#include <unordered_set>

using namespace std;

typedef struct verticesList
{
    vector<string> vertex;
} verticesList;

bool check2differentWords(const string &word1, const string &word2)
{
    // Checking whether the four alphabets of word1 exist in word2
    if (word1 == word2)
    {
        return false;
    }
    size_t len = word1.length();
    string lastFour = word1.substr(len - 4);
    for (char alphabet : lastFour)
    {
        if (word2.find(alphabet) == string::npos)
        {
            return false;
        }
    }
    return true;
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
void reverseGraph(map<string, verticesList> &edgeList, map<string, verticesList> &reversedEdgeList)
{
    for (auto &word1 : edgeList)
    {
        for (auto &word2 : word1.second.vertex)
        {
            reversedEdgeList[word2].vertex.push_back(word1.first);
        }
    }
}

void exploreFindAnInternalLink(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList, const string currentVertex, stack<string> &result)
{
    visitedEdgeList[currentVertex] = true;
    result.push(currentVertex);
    for (int i = 0; i < edgeList[currentVertex].vertex.size(); i++)
    {
        if (visitedEdgeList[edgeList[currentVertex].vertex[i]] == false)
        {
            exploreFindAnInternalLink(edgeList, visitedEdgeList, edgeList[currentVertex].vertex[i], result);
        }
    }
}

void findStrongAnInternalLink(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList, const string Vertex)
{
    map<string, verticesList> reverseDiagram;
    reverseGraph(edgeList, reverseDiagram);
    for (auto &word1 : edgeList)
    {
        for (auto &word2 : word1.second.vertex)
        {
            reverseDiagram[word2].vertex.push_back(word1.first);
        }
    }

    stack<string> result;
    stack<string> print;

    map<string, bool> &visitedEdgeListCopy1 = visitedEdgeList;
    map<string, bool> &visitedEdgeListCopy2 = visitedEdgeList;

    exploreFindAnInternalLink(edgeList, visitedEdgeListCopy1, Vertex, result);
    exploreFindAnInternalLink(reverseDiagram, visitedEdgeListCopy2, Vertex, print);

    while (!print.empty())
    {
        if (visitedEdgeListCopy1[print.top()] = true)
        {
            cout << print.top() << " ";
        }
        print.pop();
    }
}
int findTheNumberOfInternalLink(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList)
{
    map<string, bool> visitedEdgeListCopy = visitedEdgeList;
    // dfs algorithm find the number of internal link
    int coutTheNUmberOfInternalLink = 0;
    for (auto &word : visitedEdgeListCopy)
    {
        if (visitedEdgeListCopy[word.first] == false)
        {
            coutTheNUmberOfInternalLink++;
            explore(edgeList, visitedEdgeListCopy, word.first);
        }
    }
    return coutTheNUmberOfInternalLink;
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

    ifstream inputFile("sgb-words.txt");

    string word;
    while (inputFile >> word)
    {
        visitedEdgeList.insert({word, false});
    }
    inputFile.close();

    setupTree(edgeList, visitedEdgeList);
    // check the exiting destination
    // for (auto &word : visitedEdgeList)
    // {
    //     if (edgeList[word.first].vertex.empty() == true)
    //     {
    //         cout << " exiting" << endl;
    //     }
    // }

    // findStrongAnInternalLink(edgeList, visitedEdgeList, "belli");
    // cout << check2differentWords("words", "torso");
    // string vertexToPrint = "words";

    // cout << "Edges for vertex '" << vertexToPrint << "':" << endl;
    // for (const auto &neighbor : edgeList[vertexToPrint].vertex)
    // {
    //     cout << vertexToPrint << " -> " << neighbor << endl;
    // }
    string control;
    while (1)
    {
        cout << "Enter a : Finding the quantity of internal Link" << endl;
        cout << "Enter b : Finding a strong internal link" << endl;
        cout << "Enter c : Finding the minimum path from a vertex to another" << endl;
        cout << "Enter # : exiting the program" << endl;
        cout << "what is your control? ";
        getline(cin, control);
        if (control == "a")
        {
            cout << "a) the number of internal link in graph: " << findTheNumberOfInternalLink(edgeList, visitedEdgeList) << endl;
        }
        else if (control == "b")
        {
            string vertex;

            cout << "b)Finding a strong internal link" << endl;
            cout << "Enter a vertex: ";
            getline(cin, vertex);
            cout << "The strong internal link: ";
            findStrongAnInternalLink(edgeList, visitedEdgeList, vertex);
            cout << endl;
        }
        else if (control == "c")
        {
            string begin;
            string end;
            cout << "c)find the minimum path from a vertex to another" << endl;
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
    return 0;
}