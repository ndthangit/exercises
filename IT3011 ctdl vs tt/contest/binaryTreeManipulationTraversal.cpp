/*
Description
Mỗi nút của một cây nhị phân T có trường id (định danh của nút, id không trùng lặp nhau). Thực hiện chuỗi các thao tác sau đây trên cây T (ban đầu, T là cây rỗng)
•	MakeRoot u: tạo một nút gốc có id bằng u
•	AddLeft u v: tạo một nút có id = u và chèn vào vị trí con trái của nút có id bằng v trên T (không thực hiện hành động chèn nếu nút có id bằng u đã tồn tại hoặc nút có id bằng v không tồn tại hoặc nút có id bằng v đã có nút con trái rồi)
•	AddRight u v: tạo một nút có id = u và chèn vào vị trí con phải của nút có id bằng v trên T (không thực hiện hành động chèn nếu nút có id bằng u đã tồn tại hoặc nút có id bằng v không tồn tại hoặc nút có id bằng v đã có nút con phải rồi)
•	PreOrder: đưa ra trên 1 dòng mới dãy id của các nút trong phép duyệt cây T theo thứ tự trước (các phần tử cách nhau bởi đúng 1 ký tự cách SPACE)
•	InOrder: đưa ra trên 1 dòng mới dãy id của các nút trong phép duyệt cây T theo thứ tự giữa (các phần tử cách nhau bởi đúng 1 ký tự cách SPACE)
•	PostOrder: đưa ra trên 1 dòng mới dãy id của các nút trong phép duyệt cây T theo thứ tự sau (các phần tử cách nhau bởi đúng 1 ký tự cách SPACE)
Input
•	Mỗi dòng là 1 trong số cách thao tác với định dạng được mô tả ở trên (thao tác MakeRoot chỉ xuất hiện đúng 1 lần và luôn ở ngay dòng đầu tiên). Kết thúc của dữ liệu input là dòng chứa duy nhất ký tự *


Output
•	Ghi ra trên 1 dòng kết quả của 1 trong số 3 thao tác InOrder, PreOrder, PostOrder mô tả ở trên


Example
Input
MakeRoot 1
AddLeft 2 1
AddRight 3 1
AddLeft 4 3
AddRight 5 2
PreOrder
AddLeft 6 5
AddRight 7 5
InOrder
*


Output
1 2 5 3 4
2 6 5 7 1 4 3
*/
#include <iostream>
#include <cstdlib>
#include <queue>
#include <cstring>
using namespace std;

typedef int dataType;

typedef struct node
{
    dataType identification;
    node *rightChild;
    node *leftChild;
} node;

node *makeTree(dataType value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->identification = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}
node *makeNode(dataType value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->identification = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}
node *findNode(node *tree, dataType value)
{
    if (tree == NULL)
    {
        return NULL;
    }

    if (tree->identification == value)
    {
        return tree;
    }

    node *leftResult = findNode(tree->leftChild, value);
    if (leftResult != NULL)
    {
        return leftResult;
    }

    node *rightResult = findNode(tree->rightChild, value);
    return rightResult;
}
void addLeft(node *tree, dataType childNode, dataType parentNode)
{
    node *parent = findNode(tree, parentNode);
    if (parent != NULL && parent->leftChild ==NULL)
    {
        node *newNode = makeNode(childNode);
        parent->leftChild = newNode;
    }
}
void addRight(node *tree, dataType childNode, dataType parentNode)
{
    node *parent = findNode(tree, parentNode);
    if (parent != NULL&& parent->rightChild ==NULL)
    {
        node *newNode = makeNode(childNode);
        parent->rightChild = newNode;
    }
}
void preOrder(node *tree, queue<dataType> &array)
{
    if (tree == NULL)
        return;

    array.push(tree->identification);
    preOrder(tree->leftChild, array);
    preOrder(tree->rightChild, array);
}

void inOrder(node *tree, queue<dataType> &array)
{
    if (tree == NULL)
    {
        return;
    }

    inOrder(tree->leftChild, array);
    array.push(tree->identification);
    inOrder(tree->rightChild, array);
}
void postOrder(node *tree, queue<dataType> &array)
{
    if (tree == NULL)
    {
        return;
    }

    postOrder(tree->leftChild, array);
    postOrder(tree->rightChild, array);
    array.push(tree->identification);
}
int main()
{
    char control[20];
    node *tree = NULL;
    queue<dataType> array;
    while (1)
    {
        cin >> control;
        if (strcmp(control, "MakeRoot") == 0)
        {
            int originalValue;
            cin >> originalValue;
            tree = makeTree(originalValue);
        }
        else if (strcmp(control, "AddRight") == 0)
        {
            int parent, valueDescendant;
            cin >> valueDescendant >> parent;
            addRight(tree, valueDescendant, parent);
        }
        else if (strcmp(control, "AddLeft") == 0)
        {
            int parent, valueDescendant;
            cin >> valueDescendant >> parent;
            addLeft(tree, valueDescendant, parent);
        }
        else if (strcmp(control, "InOrder") == 0)
        {
            inOrder(tree, array);
            array.push(-100);
        }
        else if (strcmp(control, "PreOrder") == 0)
        {
            preOrder(tree, array);
            array.push(-100);
        }
        else if (strcmp(control, "PostOrder") == 0)
        {
            postOrder(tree, array);
            array.push(-100);
        }
        else if (strcmp(control, "*") == 0)
        {
            while (!array.empty())
            {
                if (array.front() != -100)
                {
                    cout << array.front() << " ";
                    array.pop();
                }
                else
                {
                    cout << endl;
                    array.pop();
                }
            }
            // cout << endl;
            break;
        }
    }
    return 0;
}