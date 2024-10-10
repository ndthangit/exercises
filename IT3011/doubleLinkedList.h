#ifndef doubleLinkedList_H
#define doubleLinkedList_H

#include<iostream>

using namespace std;

typedef struct Node
{
    int value;
    Node *previous;
    Node *next;
} Node;

void printList(Node *head){
    while (head -> next != NULL)
    {
        cout << head -> value <<" -> ";
        head = head -> next; 
    }
    cout << head -> value<< endl;  
}
Node *insertBegin(Node *head){
    Node *newNode = (Node*)malloc(sizeof(Node));
    cout << " enter an element to add to begin of list: ";
    cin >> newNode -> value;
    
    newNode -> next = head;
    head -> previous = newNode;
    newNode -> previous =NULL;
    
    return newNode;
}

Node *insertEnd(Node *tail){
    Node *newNode = (Node*)malloc(sizeof(Node));
    cout << " enter an element to add to end of list: ";
    cin >> newNode -> value;

    newNode -> previous = tail;
    tail -> next =newNode;
    newNode -> next = NULL;
    return newNode;

}


#endif