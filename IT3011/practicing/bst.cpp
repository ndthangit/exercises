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

node *insert(node *head, int value)
{
    if (head == NULL)
    {
        return makeNode(value);
    }
    if (head->key > value)
    {
        head->leftChild = insert(head->leftChild, value);
    }
    if (head->key < value)
    {
        head->rightChild = insert(head->rightChild, value);
    }
    return head;
}
node *search(node *head, int value)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (head->key == value)
    {
        return head;
    }
    else if (head->key > value)
    {
        return search(head->leftChild, value);
    }
    return search(head->rightChild, value);
}
node *findMin(node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    node *min = head;

    node *leftMin = findMin(head->leftChild);
    if (leftMin != NULL && leftMin->key < min->key)
    {
        min = leftMin;
    }

    node *rightMin = findMin(head->rightChild);
    if (rightMin != NULL && rightMin->key < min->key)
    {
        min = rightMin;
    }
    return min;
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
node *deleteNode(node *head, int value)
{
    if (head == NULL)
    {
        return NULL;
    }
    // repeated condition
    if (head->key > value)
    {
        head->leftChild = deleteNode(head->leftChild, value);
        return head;
    }
    if (head->key < value)
    {
        head->rightChild = deleteNode(head->rightChild, value);
        return head;
    }
    // phenomenons
    if (head->leftChild == NULL)
    {
        node *tmp = head->rightChild;
        delete head;
        return tmp;
    }
    else if (head->rightChild == NULL)
    {
        node *tmp = head->leftChild;
        delete head;
        return tmp;
    }
    else
    {
        node *parent = head;
        node *child = head->rightChild;
        while (child->leftChild != NULL)
        {
            parent = child;
            child = child->leftChild;
        }
        if (parent != head)
        {
            parent->leftChild = child->rightChild;
        }
        else
            parent->rightChild = child->rightChild;

        head->key = child->key;
        delete child;
        return head;
    }
}

int main()
{
    //  insert(head,12);
    //  preOrder(head);
    // char control[20];
    node *head = NULL;
    // node *head = makeNode(20);

    head = insert(head, 20);
    head = insert(head, 10);
    head = insert(head, 26);
    head = insert(head, 7);
    head = insert(head, 15);
    head = insert(head, 23);
    head = insert(head, 30);
    head = insert(head, 3);
    head = insert(head, 8);
    head = insert(head, 12);
    head = insert(head, 17);

    cout << head->key << endl;
    node *min = findMin(head);
    cout << min->key << endl;
    node *test = search(head, 23);
    cout << test->key << endl;
    preOrder(head);
    cout << endl;
    head = deleteNode(head, 10);
    preOrder(head);

    return 0;
}