#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <queue>
#include <cstddef>
#include <stack>
using namespace std;

typedef struct verticesList
{
    vector<string> vertex;
} verticesList;

bool check2differentWords(const string &word1, const string &word2)
{
    // Kiểm tra xem mỗi ký tự trong bốn chữ cuối của word1 có xuất hiện trong word2 hay không
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
void findAnInternalLink(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList, const string currentVertex)
{
    stack<string> result;
    visitedEdgeList[currentVertex] = true;
    result.push(currentVertex);

    for (int i = 0; i < edgeList[currentVertex].vertex.size(); i++)
    {
        if (visitedEdgeList[edgeList[currentVertex].vertex[i]] == false)
        {
            findAnInternalLink(edgeList, visitedEdgeList, edgeList[currentVertex].vertex[i]);
        }
    }

    while (!result.empty())
    {
        cout << result.top() << " ";
        result.pop();
    }
}
int findTheNumberOfInternalLink(map<string, verticesList> &edgeList, map<string, bool> &visitedEdgeList)
{
    // dfs algorithm find the number of internal link
    int coutTheNUmberOfInternalLink = 0;
    for (auto &word : visitedEdgeList)
    {
        if (visitedEdgeList[word.first] == false)
        {
            coutTheNUmberOfInternalLink++;
            explore(edgeList, visitedEdgeList, word.first);
        }
    }
    // for (auto &word : visitedEdgeList)
    // {
    //     visitedEdgeList[word.first] = false;
    // }
    return coutTheNUmberOfInternalLink;
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
    cout << "the number of internal link in graph: " << findTheNumberOfInternalLink(edgeList, visitedEdgeList) << endl;
    //cout << check2differentWords("words", "dross");
    // cout << "exercise 4B"<<endl;
    // cout << "a) find the number of internal link"<<endl;
    // cout << "b) find the internal link containing a word "<<endl;
    // cout << "c) find minimum path from a vertex to another "<<endl;
    // char control[20];
    // while (1)
    // {
    //     cout<< "your control: ";
    //     cin >> control;
    //     if (strcmp(control, "addlast") == 0)
    //     {
    //         int k;
    //         cin >> k;
    //         addLast(head, k);
    //     }
    //     else if (strcmp(control, "addfirst") == 0)
    //     {
    //         int k;
    //         cin >> k;
    //         head = addFirst(head, k);
    //     }
    //     else if (strcmp(control, "#") == 0)
    //     {
    //         break;
    //     }
    // }

    // cout << " find an internal link" << endl;
    // cout << " what word you want to find? ";
    // string internalLink;
    // getline(cin, internalLink);
    // cout << "the internal link contains word \"" << internalLink << "\": ";

    // findAnInternalLink(edgeList, visitedEdgeList, "words");
    return 0;
}