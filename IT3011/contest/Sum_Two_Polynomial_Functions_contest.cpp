#include <iostream>
#include <math.h>
#include <cstring>
using namespace std;

typedef struct node
{
    int coefficient;
    node *next;
} node;

void printList(node *head)
{
    while (head != NULL)
    {
        cout << head->coefficient << " ";
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
    newNode->coefficient = k;
    newNode->next = head->next;
    head->next = newNode;
}
node *addFirst(node *head, int k)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->coefficient = k;
    newNode->next = head;
    return newNode;
}
bool check_expression_0(node *head)
{
    while (head != NULL && head->coefficient == 0)
    {
        head = head->next;
    }
    return head == NULL;
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

void plusFind(node *head1, node *head2)
{
    node *result = NULL;
    int count = 0;
    result = addFirst(result, head1->coefficient + head2->coefficient);
    if (head1->coefficient + head2->coefficient)
    {
        count = count + 1;
    }

    if (head1->next != NULL && head2->next != NULL)
    {
        head1 = head1->next;
        head2 = head2->next;
    }

    while (head1 != NULL && head2 != NULL)
    {
        addLast(result, head1->coefficient + head2->coefficient);
        if (head1->coefficient + head2->coefficient != 0)
        {
            count = count + 1;
        }

        head1 = head1->next;
        head2 = head2->next;
    }
    while (head1 != NULL)
    {

        addLast(result, head1->coefficient);
        if (head1->coefficient != 0)
        {
            count = count + 1;
        }
        head1 = head1->next;
    }

    while (head2 != NULL)
    {

        addLast(result, head2->coefficient);
        if (head2->coefficient != 0)
        {
            count = count + 1;
        }
        head2 = head2->next;
    }
    if (count == 0)
    {
        count = count + 1;
    }

    cout << count << " ";
    if (check_expression_0(result))
    {
        cout << "0";
    }
    else
        printList(result);
}
void minusFind(node *head1, node *head2)
{
    node *result = NULL;
    int count = 0;
    result = addFirst(result, head1->coefficient - head2->coefficient);
    if (head1->coefficient - head2->coefficient != 0)
    {
        count = count + 1;
    }
    if (head1->next != NULL && head2->next != NULL)
    {
        head1 = head1->next;
        head2 = head2->next;
    }

    while (head1 != NULL && head2 != NULL)
    {

        addLast(result, head1->coefficient - head2->coefficient);
        if (head1->coefficient - head2->coefficient != 0)
        {
            count = count + 1;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    while (head1 != NULL)
    {

        addLast(result, head1->coefficient);
        if (head1->coefficient != 0)
        {
            count = count + 1;
        }
        head1 = head1->next;
    }

    while (head2 != NULL)
    {

        addLast(result, -head2->coefficient);
        if (head2->coefficient != 0)
        {
            count = count + 1;
        }
        head2 = head2->next;
    }
    if (count == 0)
    {
        count = count + 1;
    }

    cout << count << " ";
    if (check_expression_0(result))
    {
        cout << "0";
    }
    else
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

    // cout << "1:";
    // printList(head1);
    // cout << "2:";
    // printList(head2);
    cin >> control;
    if (strcmp(control, "plus") == 0)
    {
        // cout<< head1->coefficient+head2->coefficient;
        // cout<< head1->next->coefficient+head2->next->coefficient;
        plusFind(head1, head2);
    }
    else if (strcmp(control, "minus") == 0)
    {
        minusFind(head1, head2);
    }

    return 0;
}