#include<iostream>
#include<stdlib.h>
using namespace std;
typedef struct Node
{
    int value;
    Node *next;
} Node;

int main(){
    Node *head;
    head = NULL;
    
    Node *newNode =(Node*)malloc(sizeof(Node));
    newNode -> value = 1;
    newNode -> next =head;
    head = newNode;
    cout << head -> value; 
    
    newNode = (Node*)malloc(sizeof(Node));
    newNode -> value =2;
    newNode -> next = head;
    head =newNode;
    cout<< head -> value;

    newNode =(Node*)malloc(sizeof(Node));
    newNode -> value =3;
    newNode -> next =head;
    head = newNode;
    cout<< head -> value;

    while (head != NULL)
    {
        head =head ->next;
    }
    
    newNode =(Node*)malloc(sizeof(Node));
    newNode -> value = 0;
    newNode -> next = head -> next;
    head -> next = newNode;
    
    
//     while (head != NULL)
//     {
//         cout<< head -> value;
//         head =head ->next;
//     }
}