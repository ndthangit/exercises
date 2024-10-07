/*
Given a BST initialized by NULL. Perform a sequence of operations on a BST including:
insert k: insert a key k into the BST (do not insert if the key k exists)
Input
•Each line contains command under the form: “insert k”
•The input is terminated by a line containing #
Output
•Write the sequence of keys of nodes visited by the pre-order traversal (separated by a SPACE character)
Example
Input
insert 20
insert 10
insert 26
insert 7
insert 15
insert 23
insert 30
insert 3
insert 8
#
Output
20 10 7 3 8 15 26 23 30
*/
#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int val)
    {
        key = val;
        left = nullptr;
        right = nullptr;
    }
};

// A Simple BST Insert
Node *insertBST(Node *root, int key)
{
    if (root == nullptr)
        return new Node(key);
    if (root->key > key)
        root->left = insertBST(root->left, key);
    else if (root->key < key)
        root->right = insertBST(root->right, key);
    return root;
}

// A function to print BST in inorder
void inorder(Node *root)
{
    if (root != nullptr)
    {
        cout << root->key << " ";

        inorder(root->left);
        inorder(root->right);
    }
}

// Driver code
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Node *root = nullptr;
    string control;

    while (control != "#")
    {
        cin >> control;
        if (control == "insert")
        {
            int a;
            cin >> a;
            root = insertBST(root, a);
        }
    }
    inorder(root);
    return 0;
}