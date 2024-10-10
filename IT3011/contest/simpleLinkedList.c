#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

void printList(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

node *addFirst(node *head, int number)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = number;
    newNode->next = head;
    return newNode;
}
void addLast(node *head, int number)
{
    while (head->next != NULL)
    {
        head = head->next;
    }
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = number;
    head->next = newNode;
    newNode->next = NULL;
}
void addAfter(node *head, int location, int number)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = number;
    node *nodeAfter = head->next;
    while (head->value != location)
    {
        head = head->next;
        nodeAfter = head->next;
    }
    head->next = newNode;
    newNode->next = nodeAfter;
}

node *reverse(node *head)
{
    node *previousNode = NULL;
    node *currentNode = head;
    while (currentNode != NULL)
    {
        node *nextNode = currentNode->next;
        currentNode->next = previousNode;
        previousNode = currentNode;
        currentNode = nextNode;
    }
    return previousNode;
}

node *removeElement(node *head, int number)
{
    node *current = head;
    node *previous = NULL;

    // Check if the node to be removed is the head
    if (current != NULL && current->value == number)
    {
        head = current->next;
        free(current);
        current =head;
        //return head;
    }

    // Search for the node to be removed
    // while (current != NULL)
    // {
    //     if (current->value == number)
    //     {
    //         previous->next = current->next;
    //         //free(current);
    //         //break;
    //     }

    //     previous = current;
    //     current = current->next;
    // }
    while (current != NULL)
    {
        if (current->value == number)
        {
            previous->next = current->next;
            free(current);
            current = previous->next;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    // if (current != NULL)
    // {
    //     previous->next = current->next;
    //     free(current);
    // }

    return head;
}
int main()
{
    node *head = NULL;
    char control[20];

    while (1)
    {
        scanf("%s", control);

        if (strcmp(control, "addFirst") == 0)
        {
            int number;
            scanf("%d", &number);
            head = addFirst(head, number);
        }
        else if (strcmp(control, "addLast") == 0)
        {
            int number;
            scanf("%d", &number);
            addLast(head, number);
        }
        else if (strcmp(control, "addAfter") == 0)
        {
            int location;
            scanf("%d", &location);
            int number;
            scanf("%d", &number);
            addAfter(head, location, number);
        }
        if (strcmp(control, "remove") == 0)
        {
            int number;
            scanf("%d", &number);
            head = removeElement(head, number);
        }
        if (strcmp(control, "reverse") == 0)
        {
            head = reverse(head);
        }
        else if (strcmp(control, "#") == 0)
        {
            //break;
            printList(head);
        }
    }

    // Print the linked list after all operations
    //printList(head);

    // Free memory for the linked list
    while (head != NULL)
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
