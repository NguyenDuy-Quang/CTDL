#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};
Node* initial_BST() {
    return nullptr;
}
Node* createNode(int x) {
    Node* newNode = new Node();
    newNode->data = x;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}
Node* add_node(Node* root, int x) {
    if (root == nullptr) {
        return createNode(x);
    }
    if (x <= root->data) {
        root->left = add_node(root->left, x);
    } else {
        root->right = add_node(root->right, x);
    }
    return root;
}
Node* Search_BST(Node* root, int x) {
    if (root == nullptr || root->data == x) {
        return root;
    }
    if (x <= root->data) {
        return Search_BST(root->left, x);
    }
    return Search_BST(root->right, x);
}
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        inorderTraversal(root->right);
    }
}
int main() {
    Node* root = initial_BST();
    vector<int> namSinh = {2001, 2002, 2006, 2007, 2003, 2004, 2005, 2001, 1999, 2004};
    for (int nam : namSinh) {
        root = add_node(root, nam);
    }
    inorderTraversal(root);
    int target = 2004;
    Node* result = Search_BST(root, target);
    if (result != nullptr) {
        cout << "==> Tim thay sinh vien sinh nam " << target << " trong cay BST!" << endl;
    } else {
        cout << "==> Khong tim thay sinh vien sinh nam " << target << "." << endl;
    }
    
    return 0;
}