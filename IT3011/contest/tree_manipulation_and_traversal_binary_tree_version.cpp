/*
Mỗi nút trên cây có trường id (identifier) là một số nguyên (id của các nút trên cây đôi một khác nhau)
Thực hiện 1 chuỗi các hành động sau đây bao gồm các thao tác liên quan đến xây dựng cây và duyệt cây
· MakeRoot u: Tạo ra nút gốc u của cây
· Insert v u: tạo mới 1 nút u và chèn vào cuối danh sách nút con của nút v (nếu nút có id bằng v không tồn tại hoặc nút có id bằng u đã tồn tại thì không chèn thêm mới)
· PreOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự trước
· InOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự giữa
· PostOrder: in ra thứ tự các nút trong phép duyệt cây theo thứ tự sau
Dữ liệu: bao gồm các dòng, mỗi dòng là 1 trong số các hành động được mô tả ở trên, dòng cuối dùng là * (đánh dấu sự kết thúc của dữ liệu).
Kết quả: ghi ra trên mỗi dòng, thứ tự các nút được thăm trong phép duyệt theo thứ tự trước, giữa, sau của các hành động PreOrder, InOrder, PostOrder tương ứng đọc được từ dữ liệu đầu vào
Ví dụ
Dữ liệu
MakeRoot 10
Insert 11 10
Insert 1 10
Insert 3 10
InOrder
Insert 5 11
Insert 4 11
Insert 8 3
PreOrder
Insert 2 3
Insert 7 3
Insert 6 4
Insert 9 4
InOrder
PostOrder
*
Kết quả
11 10 1 3
10 11 5 4 1 3 8
5 11 6 4 9 10 1 8 3 2 7
5 6 9 4 11 1 8 2 7 3 10
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
    node *rightSibling;
    node *leftChild;
} node;

node *makeTree(dataType value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->identification = value;
    newNode->leftChild = NULL;
    newNode->rightSibling = NULL;
    return newNode;
}
node *makeNode(dataType value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->identification = value;
    newNode->leftChild = NULL;
    newNode->rightSibling = NULL;
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

    node *rightResult = findNode(tree->rightSibling, value);
    return rightResult;
}

void preOrder(node *tree, queue<dataType> &array)
{
    if (tree == NULL)
        return;

    array.push(tree->identification);

    node *ptr = tree->leftChild;
    while (ptr != NULL)
    {
        preOrder(ptr, array);
        ptr = ptr->rightSibling;
    }
}

void inOrder(node *tree, queue<dataType> &array)
{
    if (tree == NULL)
    {
        return;
    }

    node *ptr = tree->leftChild;
    inOrder(ptr, array);
    array.push(tree->identification);

    if (ptr != NULL)
        ptr = ptr->rightSibling;
    while (ptr != NULL)
    {
        inOrder(ptr,array);
        ptr = ptr->rightSibling;
    }
}
// void inOrder(node *tree, queue<dataType> &array)
// {
//     if (tree == NULL)
//     {
//         return;
//     }

//     inOrder(tree->leftChild, array);
//     array.push(tree->identification);
//     inOrder(tree->rightSibling, array);
// }
void postOrder(node *tree, queue<dataType> &array)
{
    if (tree == NULL)
    {
        return;
    }

    node *ptr = tree->leftChild;
    while (ptr != NULL)
    {
        postOrder(ptr,array);
        ptr = ptr->rightSibling;
    }

    array.push(tree->identification);
}
// void postOrder(node *tree, queue<dataType> &array)
// {
//     if (tree == NULL)
//     {
//         return;
//     }

//     postOrder(tree->leftChild, array);
//     postOrder(tree->rightSibling, array);
//     array.push(tree->identification);
// }

void insertNode(node *tree, dataType childNode, dataType parentNode)
{
    node *parent = findNode(tree, parentNode);
    if (parent->leftChild == NULL)
    {
        node *newNode = makeNode(childNode);
        parent->leftChild = newNode;
    }
    else
    {
        parent = parent->leftChild;
        while (parent->rightSibling != NULL)
        {
            parent = parent->rightSibling;
        }
        node *newNode = makeNode(childNode);
        parent->rightSibling = newNode;
    }
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
            tree = makeTree( originalValue);
        }
        else if (strcmp(control, "Insert") == 0)
        {
            int parent, valueDescendant;
            cin >> valueDescendant >> parent;
            insertNode(tree, valueDescendant, parent);
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