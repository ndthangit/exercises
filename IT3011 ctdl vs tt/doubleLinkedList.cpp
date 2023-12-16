#include<iostream>
#include"doubleLinkedList.h"
using namespace  std;


int main(){
    Node *head = (Node*)malloc(sizeof(Node));
    cout <<" enter an element as the start of list: ";
    cin >> head -> value;
    
    Node *tail = (Node*)malloc(sizeof(Node));
    cout <<" enter an element as the end of list: ";
    cin >> tail -> value;
    
    head -> previous =NULL;
    head -> next = tail;
    tail -> next =NULL;
    tail -> previous =head;
    
    printList(head);
    
    int choice;
    while (1)
    {
        cout << "choose your operations"<< endl;
        cout << " 1. add an element in begin of list " << endl;
        cout << " 2. add an element in end of list " << endl;
        cout << " 3. delete an element" << endl;
        cout << " 4. replace elements" << endl;
        //cout << " 4. replace elements" << endl;
        cout << " enter your choice: " ;
        cin >> choice;
        switch (choice)
        {
        case 1:
            head = insertBegin(head);
            break;
        case 2:
            tail = insertEnd(tail);
            break;
        case 3:
            //head = deleteElement(head);
            break;
        case 4:
            //replace(head);
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