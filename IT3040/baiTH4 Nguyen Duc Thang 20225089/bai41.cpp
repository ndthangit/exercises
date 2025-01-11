/*bai 4.1 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/

#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        next = NULL;
    }
};

Node *prepend(Node *head, int data)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    Node *new_node = new Node(data);
    new_node->next = head;
    head = new_node;
    return head;
}

void print(Node *head)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

Node *reverse(Node *head)
{
    /* Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/
    Node *prev = NULL;
    Node *current = head;
    Node *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    return head;
}

int main()
{
    int n, u;
    cin >> n;
    Node *head = NULL;
    for (int i = 0; i < n; ++i)
    {
        cin >> u;
        head = prepend(head, u);
    }

    cout << "Original list: ";
    print(head);

    head = reverse(head);

    cout << "Reversed list: ";
    print(head);

    return 0;
}
/*bai 4.1 - tuần 15
 * Nguyễn Đức Thắng - 20225089 - 744463 - 20241*/