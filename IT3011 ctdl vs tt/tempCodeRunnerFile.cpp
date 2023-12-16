#include <iostream>
#include <cstring>
using namespace std;

typedef struct node
{
    int data;
    node *next;
} node;

void printList(node *head)
{
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void addLast(node *head, int k)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = k;
    newNode->next = head->next;
    head->next = newNode;
}
node *addFirst(node *head, int k)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = k;
    newNode->next = head;
    return newNode;
}

void addAfter(node *head, int k, int situation)
{

    while (head != NULL)
    {
        if (head->data == situation)
        {
            node *newNode = (node *)malloc(sizeof(node));
            newNode->data = k;
            newNode->next = head->next;
            head->next = newNode;
            break;
        }

        head = head->next;
    }
}
void addBefore(node *&head, int k, int situation)
{
    node *previousNode = NULL;
    node *currentNode = head;

    if (head->data == situation)
    {
        head = addFirst(head, k);
    }
    else
    {
        while (currentNode != NULL)
        {

            if (currentNode->data == situation)
            {
                addAfter(previousNode, k, situation);
                break;
            }
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }
}
void remove(node *&head, int k)
{

    node *previousNode = NULL;
    node *currentHead = head;

    if (head->data == k)
    {
        head = currentHead->next;
        currentHead = NULL;
        delete currentHead;
    }
    else
    {
        while (currentHead->data != k)
        {
            previousNode = currentHead;
            currentHead = currentHead->next;
        }
        previousNode->next = currentHead->next;
        currentHead = NULL;
        delete currentHead;
    }
}

node *reverse(node *head)
{

    node *previous = NULL;
    node *current = head;
    node *nextNode = NULL;

    while (current != NULL)
    {
        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    head = previous;
    return head;
}

int main()
{

    node *head = NULL;
    char control[20];

    int quality;
    cin >> quality;

    int firstElement;
    cin >> firstElement;
    head = addFirst(head, firstElement);

    for (int i = 1; i < quality; i++)
    {
        int element, previousElement;
        cin >> element;
        if (i == 1)
        {
            addAfter(head, element, firstElement);
        }
        else
            addAfter(head, element, previousElement);

        previousElement = element;
    }
    printList(head);
    while (1)
    {
        cin >> control;
        if (strcmp(control, "addlast") == 0)
        {
            int k;
            cin >> k;
            addLast(head, k);
        }
        else if (strcmp(control, "addfirst") == 0)
        {
            int k;
            cin >> k;
            head = addFirst(head, k);
        }
        else if (strcmp(control, "addafter") == 0)
        {
            int k, situation;
            cin >> k >> situation;
            addAfter(head, k, situation);
        }
        else if (strcmp(control, "addbefore") == 0)
        {
            int k, situation;
            cin >> k >> situation;
            addBefore(head, k, situation);
        }
        else if (strcmp(control, "remove") == 0)
        {
            int k;
            cin >> k;
            remove(head, k);
        }
        else if (strcmp(control, "reverse") == 0)
        {
            head = reverse(head);
        }
        else if (strcmp(control, "#") == 0)
        {
            break;
        }
        printList(head);
    }
}