#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;

typedef struct tree{
    int id;
    tree* leftChild;
    tree*  rightChild;
} tree;

tree *makeRoot(tree* root, int value){
    tree *newElement = (tree*)malloc(sizeof(tree));
    newElement ->id = value;
    newElement->leftChild =NULL;
    newElement->rightChild=NULL;
    return newElement; 
}
bool checkExistedElement(tree *root, int value){

}
tree *insert(tree *root,int ancestor, int desetor){
    if (!checkExistedElement(root, value))
    {
        /* code */
    }
    
}

int main(){
    tree *root =NULL;
    char control[20];

    while (1)
    {
        cin >> control;
        if (strcmp(control, "MakeRoot") == 0)
        {
            int valueRoot;
            cin>> valueRoot;
            root = makeRoot(root, valueRoot);
            cout << root->id;
        }
        else if (strcmp(control, "dSort") == 0)
        {
            break;
        }
        else if (strcmp(control, "#") == 0)
        {
            break;
        }
    }

}
