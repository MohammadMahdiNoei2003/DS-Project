#include <bits/stdc++.h>

using namespace std;

class TreeNode {
    public:
        int value;
        TreeNode* right;
        TreeNode* left;

        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* buildForPostOrderTree(int inOrder[], int preOrder[], int size) {
    if (size == 0) {
        return nullptr;
    }

    int rootValue = preOrder[0];
    TreeNode* root = new TreeNode(rootValue);

    int indexInOrder = 0;
    for (; indexInOrder < size; indexInOrder++) {
        if (inOrder[indexInOrder] == rootValue) {
            break;
        }
    }

    root->left = buildForPostOrderTree(inOrder, preOrder + 1, indexInOrder);
    root->right = buildForPostOrderTree(inOrder + indexInOrder + 1, preOrder + 1 + indexInOrder, size - indexInOrder -1);

    return root;
}

void postOrderTraversal(TreeNode* root) {
    if (!root) {
        return;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);

    cout << root->value << " ";
}

void generatePostOrder(int inOrder[], int preOrder[], int size) {
    TreeNode* root = buildForPostOrderTree(inOrder, preOrder, size);

    cout << "PostOrder sequence: ";
    postOrderTraversal(root);
    cout << endl;
}

TreeNode* buildForPreOrderTree(int inOrder[], int postOrder[], int size) {
    if (size == 0) {
        return nullptr;
    }

    int rootValue = postOrder[size - 1];
    TreeNode* root = new TreeNode(rootValue);
    
    int indexInOrder = 0;
    for (; indexInOrder < size; indexInOrder++) {
        if (inOrder[indexInOrder] == rootValue) {
            break;
        }
    }

    root->left = buildForPreOrderTree(inOrder, postOrder, indexInOrder);
    root->right = buildForPreOrderTree(inOrder + indexInOrder + 1, postOrder + indexInOrder, size - indexInOrder -1);

    return root;
}

void preOrderTraversal(TreeNode* root) {
    if (!root) {
        return;
    }

    cout << root->value << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void generatePreOrder(int inOrder[], int postOrder[], int size) {
    TreeNode* root = buildForPreOrderTree(inOrder, postOrder, size);

    cout << "PreOrder sequence: ";
    preOrderTraversal(root);
    cout << endl;
}