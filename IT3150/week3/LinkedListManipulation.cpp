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
bool existent(node *head, int k)
{
    while (head != NULL)
    {
        if (head->data == k)
        {
            return true;
        }
        else
            head = head->next;
    }
    return false;
}
void addLast(node *head, int k)
{
    if (!existent(head, k))
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
}
node *addFirst(node *head, int k)
{
    if (!existent(head, k))
    {
        node *newNode = (node *)malloc(sizeof(node));
        newNode->data = k;
        newNode->next = head;
        return newNode;
    }
    else
        return head;
}

void addAfter(node *head, int k, int location)
{
    if (!existent(head, k))
    {
        while (head != NULL)
        {
            if (head->data == location)
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
}
void addBefore(node *&head, int k, int location)
{
    node *previousNode = NULL;
    node *currentNode = head;
    if (!existent(head, k))
    {
        if (head->data == location)
        {
            head = addFirst(head, k);
        }
        else
        {

            while (currentNode != NULL && currentNode->data != location)
            {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }

            if (currentNode != NULL)
            {
                node *newNode = (node *)malloc(sizeof(node));
                newNode->data = k;
                newNode->next = currentNode;
                previousNode->next = newNode;
            }
        }
    }
}

node *remove(node *head, int k)
{

    if (existent(head, k))
    {

        if (head->data == k)
        {

            node *newH = head;
            head = head->next;
            delete newH;
            return head;
        }
        else
        {
            node *previousNode = head;
            node *newH = head;
            while (head->data != k)
            {
                previousNode = head;
                head = head->next;
            }

            previousNode->next = head->next;
            head = NULL;
            delete head;
            return newH;
        }
    }
    else
        return head;
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
            int k, location;
            cin >> k >> location;
            addAfter(head, k, location);
        }
        else if (strcmp(control, "addbefore") == 0)
        {
            int k, location;
            cin >> k >> location;
            addBefore(head, k, location);
        }
        else if (strcmp(control, "remove") == 0)
        {

            int k;
            cin >> k;
            head = remove(head, k);
        }
        else if (strcmp(control, "reverse") == 0)
        {
            head = reverse(head);
        }
        else if (strcmp(control, "#") == 0)
        {
            break;
        }
    }
    printList(head);
}