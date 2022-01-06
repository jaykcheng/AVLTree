#include <iostream>

using namespace std;

class Node {
    public:
        int val;
        int height;
        Node *left;
        Node *right;
        Node(int v):val{v}{  // Node(int v, int h):val{v},height{h} {}
            height = 0;
            left = nullptr;
            right = nullptr;
        };
        Node(){
            val = 0;
            height = 0;
            left = nullptr;
            right = nullptr;
        }
};

class AVL {
    public:
        void insert(const int &v);
        
        AVL(){root = nullptr;};
        static void rotateLeft(Node *& node);
        static void rotateRight(Node *& node);
        static void rotateLeftRight(Node *& node);
        static void rotateRightLeft(Node *& node);

        Node *root;
};

