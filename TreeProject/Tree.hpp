#include <bits/stdc++.h>

using namespace std;

class TreeNode {
    public:
        int value;
        TreeNode* right;
        TreeNode* left;

        TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* buildTree(int inOrder[], int preOrder[], int size) {
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

    root->left = buildTree(inOrder, preOrder + 1, indexInOrder);
    root->right = buildTree(inOrder + indexInOrder + 1, preOrder + 1 + indexInOrder, size - indexInOrder -1);

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
    TreeNode* root = buildTree(inOrder, preOrder, size);

    cout << "PostOrder sequence: ";
    postOrderTraversal(root);
    cout << endl;
}