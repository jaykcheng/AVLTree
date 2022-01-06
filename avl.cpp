#include "avl.h"
#include <iostream>
#include <queue>

using namespace std;

int getHeight(Node *node) {
    return node == nullptr ? -1 : node->height;
}

void AVL::rotateLeft(Node *& node) {
    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node = tmp;
    return;
}

void AVL::rotateRight(Node *& node) {
    Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node = tmp;
    return;
}

void AVL::rotateLeftRight(Node *& node) {
    rotateLeft(node->left);
    rotateRight(node);
    return;
}

void AVL::rotateRightLeft(Node *& node) {
    rotateRight(node->right);
    rotateLeft(node);
    return;
}

int computeHeight(Node *root){

    if (root == nullptr) {

        return -1;

    } else {

        int hLeft = computeHeight(root->left);

        int hRight = computeHeight(root->right);

        return std::max(hLeft, hRight) + 1;

    }
}

int balanceHelper(Node *node){
    if(node == nullptr)
    {
        return 0;
    }
    int balance = computeHeight(node -> left) - computeHeight(node -> right);
    return balance;
}

Node* leftRotateRecursive(Node *& node)
{
    Node *tmp = node -> right;
    Node *tmp2 = tmp -> left;
    tmp -> left = node;
    node -> right = tmp2;
    return tmp;
}

Node* rightRotateRecursive(Node *& node)
{
    Node *tmp = node -> left;
    Node *tmp2 = tmp -> right;
    tmp -> right = node;
    node -> left = tmp2;
    return tmp;
}

Node* insertHelper(Node* node, const int &v){
    // if node is a null pointer, return node as a new Node with value as its parameter
    if(node == nullptr)
    {
        Node* rootNode = new Node(v);
        node = rootNode;
        return node;
    }
    // if the node value is greater than v (v is smaller), we insert values on the left
    if(node -> val > v)
    {
        // if node does not have a left child, insert it
        if(node -> left == nullptr)
        {
            Node* leftNode = new Node(v);
            node -> left = leftNode;
        }
        // else if it does have a left child, recursively insert it
        else
        {
        node -> left = insertHelper(node -> left, v);
        }
    }
    // if the node value is less than v (v is bigger), we insert values on the right
    else if(node -> val < v)
    {
        // if node does not have a right child, insert it
        if(node -> right == nullptr)
        {
            Node* rightNode = new Node(v);
            node -> right = rightNode;
        }
        // else if it does have a right child, recursively insert it
        else
        {
        node -> right = insertHelper(node -> right, v);
        }
    }
    // update height of the node and find balancefactor of the node
    node -> height = computeHeight(node);
    int rootBalance = balanceHelper(node);
    
    // Left Rotation Case
    if(rootBalance == -2 && balanceHelper(node -> right) == -1)
    {
        return leftRotateRecursive(node);
    }
    // Left Right Rotation Case
    else if(rootBalance == 2 && balanceHelper(node -> left) != 1)
    {
        node -> left = leftRotateRecursive(node -> left);
        return rightRotateRecursive(node);
    }
    // Right Rotation Case
    else if(rootBalance == 2 && balanceHelper(node -> left) == 1)
    {
        return rightRotateRecursive(node);
    }
    // Right Left Rotation Case
    else if(rootBalance == -2 && balanceHelper(node -> right) != 1)
    {
        node -> right = rightRotateRecursive(node -> right);
        return leftRotateRecursive(node);
    }
    return node;
}

void AVL::insert(const int &v){
    root = insertHelper(root, v);
}

void printBT(const string& prefix, const Node* node, bool isLeft)
{
    if(node != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "├──" : "└──" );

        int balance = getHeight(node->left) - getHeight(node->right);
        // print the value of the node
        cout << " " << node->val << "," << node->height << "," << balance << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const Node* node)
{
    printBT("", node, false);    
}

int main() 
{
    AVL tree = AVL();
    Node* root = nullptr;
    // root = tree.insert(8);
    tree.insert(1);
    tree.insert(8);
    tree.insert(6);
    tree.insert(9);
    tree.insert(10);
    tree.insert(12);

}