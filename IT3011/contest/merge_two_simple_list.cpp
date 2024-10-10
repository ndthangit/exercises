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

node *create_list(node *head, int n)
{
    // node *firstHead =NULL;
    int firstElement;
    cin >> firstElement;
    head = addFirst(head, firstElement);
    for (int i = 2; i <= n; i++)
    {
        int addElement;
        cin >> addElement;
        addLast(head, addElement);
    }
    return head;
}
void insert(node *head, node *insertHead)
{
    // Insert the nodes from insertHead to the end of the list
    while (head->next != NULL)
    {
        head = head->next;
    }
    head->next = insertHead;
}

void sortList(node *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        // Empty list or a single-node list is already sorted
        return;
    }

    bool swapped;
    node *ptr1;
    node *lptr = nullptr;

    do
    {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            {
                // Swap the nodes if they are in the wrong order
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
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

void iSort(node *head1, node *head2)
{
    // Merge two lists in ascending order
    // Create a new list to store the merged result
    // cout << "success" << endl;
    node *result = NULL;

    if (head1->data <= head2->data)
    {
        result = addFirst(result, head1->data);
        head1 = head1->next;
    }

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data <= head2->data)
        {
            addLast(result, head1->data);
            head1 = head1->next;
        }
        else
        {
            addLast(result, head2->data);
            head2 = head2->next;
        }
    }

    // Add remaining nodes from head1
    while (head1 != NULL)
    {
        addLast(result, head1->data);
        head1 = head1->next;
    }

    // Add remaining nodes from head2
    while (head2 != NULL)
    {
        addLast(result, head2->data);
        head2 = head2->next;
    }

    printList(result);
}
void dSort(node *head1, node *head2)
{
    node *result = NULL;

    if (head1->data <= head2->data)
    {
        result = addFirst(result, head1->data);
        head1 = head1->next;
    }

    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data <= head2->data)
        {
            addLast(result, head1->data);
            head1 = head1->next;
        }
        else
        {
            addLast(result, head2->data);
            head2 = head2->next;
        }
    }

    // Add remaining nodes from head1
    while (head1 != NULL)
    {
        addLast(result, head1->data);
        head1 = head1->next;
    }

    // Add remaining nodes from head2
    while (head2 != NULL)
    {
        addLast(result, head2->data);
        head2 = head2->next;
    }
    result = reverse(result);
    printList(result);
}
int main()
{
    char control[20];

    int quantityOfList1;
    int quantityOfList2;

    cin >> quantityOfList1;
    node *head1 = NULL;
    head1 = create_list(head1, quantityOfList1);

    cin >> quantityOfList2;
    node *head2 = NULL;
    head2 = create_list(head2, quantityOfList2);

    sortList(head1);
    // cout << "1:";
    //  printList(head1);
    sortList(head2);
    // cout << "2:";
    // printList(head2);
    // iSort(head1, head2);
    // cout >> "new head1: ";
    // printList(head1);
    while (1)
    {
        cin >> control;
        if (strcmp(control, "iSort") == 0)
        {
            if (head1->data < head2->data)
            {
                iSort(head1, head2);
            }
            else
            {
                iSort(head2, head1);
            }
        }
        else if (strcmp(control, "dSort") == 0)
        {

            if (head1->data > head2->data)
            {
                dSort(head2, head1);
            }
            else
            {
                dSort(head1, head2);
            }
        }
        else if (strcmp(control, "#") == 0)
        {
            break;
        }
    }

    return 0;
}