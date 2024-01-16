#include <iostream>
#include "Tree.hpp"

using namespace std;

int main() {
    int inOrderSequence[] = {4, 3, 2, 5, 1, 6, 8, 7, 9};
    int preOrderSequence[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int postOrderSequence[] = {4, 3, 5, 2, 8, 9, 7, 6, 1};
    int size = sizeof(inOrderSequence) / sizeof(inOrderSequence[0]);

    generatePostOrder(inOrderSequence, preOrderSequence, size);
    generatePreOrder(inOrderSequence, postOrderSequence, size);

    return 0;
}