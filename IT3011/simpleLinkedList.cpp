#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
typedef struct Node
{
    int data;
    Node *next;
} Node;

void printList(Node *head)
{

    if (head != NULL)
    {
        while (head->next != NULL)
        {
            cout << head->data << " -> ";
            head = head->next;
        }
        cout << head->data; // for last node
    }
    else
    {
        cout << "Empty List!" << endl;
    }
}

void freeList(Node *head)
{
    Node *freeNode;
    while (head != NULL)
    {
        freeNode = head->next;
        free(head);
        head = freeNode;
    }
}

Node *insertBegin(Node *head)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    cout << "enter an element inserted in begin of list: ";
    cin >> newNode->data;
    newNode->next = head;
    head = newNode;
    // delete(head);
    return head;
}
void replace(Node *head)
{
    int choice;
    int alter;
    cout << "enter an element you want to replace: ";
    cin >> choice;
    cout << "enter an element it becomes : ";
    cin >> alter;
    while (head != NULL)
    {
        if (head->data == choice)
            head->data = alter;
        head = head->next;
    }
}

void insertEnd(Node *head)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    cout << "enter an element inserted in end of list: ";
    cin >> newNode->data;
    newNode->next = head->next;
    head->next = newNode;
}

// Node *deleteElement(Node *head){
//     cout << " enter an element you want to delete : ";
//     int deletedElement;
//     cin >> deletedElement;

//     if (head -> data == deletedElement)
//     {
//         /* code */
//         Node *newH =head;
//         head =head ->next;
//         free(newH);
//         return head;
//     }  else {
//         Node *previousNode = head;
//         Node *newH = head;
//         while (head -> data != deletedElement)
//         {
//             previousNode =head;
//             head =head -> next;
//         }
//         //Node* newHead =head;
//         previousNode -> next= head -> next;
//         head =NULL;
//         free(head);
//         return newH;
//     }

// }
void deleteElement(Node *&head)
{
    cout << " enter an element you want to delete : ";
    int deletedElement;
    cin >> deletedElement;

    Node *previousNode = NULL;
    Node *currentHead = head;

    if (head->data == deletedElement)
    {
        /* code */
        head = currentHead->next;
        currentHead = NULL;
        delete currentHead;
    }
    else
    {
        while (currentHead->data != deletedElement)
        {
            previousNode = currentHead;
            currentHead = currentHead->next;
        }
        previousNode->next = currentHead->next;
        currentHead = NULL;
        delete currentHead;
    }
}

int main()
{
    Node *head;
    head = NULL;
    int choice;

    while (1)
    {
        cout << "choose your operations" << endl;
        cout << " 1. add an element in begin of list " << endl;
        cout << " 2. add an element in end of list " << endl;
        cout << " 3. delete an element" << endl;
        cout << " 4. replace elements" << endl;
        // cout << " 4. replace elements" << endl;
        cout << " enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            head = insertBegin(head);
            break;
        case 2:
            insertEnd(head);
            break;
        case 3:
            // head = deleteElement(head);
            deleteElement(head);
            break;
        case 4:
            replace(head);
            break;
        // case 5:
        //     head = deleteElement(head);
        //     break;
        default:
            break;
        }
        printList(head);
    }
}
