#include <iostream>
#include <cstdlib>
#include <queue>

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
// node *parentNode(node *tree, dataType valueDescendant)
// {
//     if (tree->leftChild == NULL || tree->rightChild == NULL)
//     {
//         return tree;
//     }

//     node *leftParent = parentNode(tree->leftChild, valueDescendant);
//     node *rightParent = parentNode(tree->rightChild, valueDescendant);
// }

// void insertNode(node *tree, dataType childNode, dataType parentNode)
// {
//     node *parent = findNode(tree, parentNode);
//     while (parent != NULL)
//     {
//         if (parent->leftChild != NULL)
//         {
//             node *add = makeNode(childNode);
//             parent->leftChild = add;
//             return;
//         }
//         if (parent->rightChild != NULL)
//         {
//             node *add = makeNode(childNode);
//             parent->rightChild = add;
//             return;
//         }
//         parent = parent->leftChild;
//     }
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
    node *tree = NULL;
    queue<dataType> array;

    tree = makeTree(0);
    node *nut1 = makeNode(1);
    node *nut2 = makeNode(2);
    node *nut3 = makeNode(3);
    node *nut4 = makeNode(4);
    node *nut5 = makeNode(5);
    node *nut6 = makeNode(6);
    node *nut7 = makeNode(7);
    node *nut8 = makeNode(8);
    node *nut9 = makeNode(9);

    tree->leftChild = nut1;
    nut1->rightSibling = nut2;
    nut2->rightSibling = nut3;

    nut1->leftChild = nut4;
    nut4->rightSibling = nut5;

    nut2->leftChild = nut6;
    nut6->rightSibling = nut7;

    nut3->leftChild = nut8;
    nut8->leftChild = nut9;

    node *find = findNode(tree, 4);
    node *find2 = findNode(tree, 8);
    // if (find != NULL)
    // {
    //     cout << find->identification << find2->identification;
    // }
    // else
    //     cout << "NOT FOUND";
    // insertNode(tree, 10, 8);
    // cout << endl;
    // node *findTest = findNode(tree, 9);
    // cout << findTest->rightSibling->identification;
    preOrder(tree, array);
    while (!array.empty())
    {
        cout << array.front() << " ";
        array.pop();
    }
    // cout << endl;
    // inOder(tree, array);
    // while (!array.empty())
    // {
    //     cout << array.front() << " ";
    //     array.pop();
    // }
    // cout << endl;
    // PostOrder(tree, array);
    // while (!array.empty())
    // {
    //     cout << array.front() << " ";
    //     array.pop();
    // }
    // cout << endl;

    return 0;
}