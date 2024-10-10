/*
Problem: BST - Insertion and PreOrder Traversal
________________________________________
Description
Given a BST initialized by NULL. Perform a sequence of operations on a BST including:
•	insert k: insert a key k into the BST (do not insert if the key k exists)
Input
•Each line contains command under the form: “insert k”
•The input is terminated by a line containing #
Output
•Write the sequence of keys of nodes visited by the pre-order traversal (separated by a SPACE character)
Example
Input
insert 20
insert 10
insert 26
insert 7
insert 15
insert 23
insert 30
insert 3
insert 8
#
Output
20 10 7 3 8 15 26 23 30
*/
#include <iostream>
#include <cstdlib>
#include <queue>
#include <cstring>
using namespace std;

typedef struct binaryTree
{
    int key;
    binaryTree *leftChild;
    binaryTree *rightChild;
} node;
node *makeNode(int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->key = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

void insert(node *head, int value)
{
    if (head == NULL)
    {
        int element;
        cin >> element;
        head = makeNode(element);
        return;
    }
    if (head->key == value)
    {
        return;
    }

    if (head->key > value && head->leftChild == NULL)
    {
        head->leftChild = makeNode(value);
        return;
    }
    if (head->key < value && head->rightChild == NULL)
    {
        head->rightChild = makeNode(value);
        return;
    }
    if (head->key > value)
    {
        insert(head->leftChild, value);
    }
    else
        insert(head->rightChild, value);
}
void preOrder(node *head)
{
    if (head == NULL)
    {
        return;
    }
    cout << head->key << " ";
    preOrder(head->leftChild);
    preOrder(head->rightChild);
}
int main()
{
    // node *head = makeNode(20);
    //  insert(head,12);
    //  preOrder(head);
    char control[20];
    node *head = NULL;
    while (1)
    {
        cin >> control;
        if (strcmp(control, "insert") == 0)
        {
            int element;
            cin >> element;
            if (head == NULL)
            {
                head = makeNode(element);
            }
            else
                insert(head, element);
        }
        else if (strcmp(control, "#") == 0)
        {
            preOrder(head);
            break;
        }
    }
    return 0;
}