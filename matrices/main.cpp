#include <iostream>
#include <stack>
#include <vector>

void printStack(std::stack<int>& trainStack) {
    std::stack<int> tempStack;

    while (!trainStack.empty()) {
        tempStack.push(trainStack.top());
        trainStack.pop();
    }

    while (!tempStack.empty()) {
        std::cout << tempStack.top() << " ";
        trainStack.push(tempStack.top());
        tempStack.pop();
    }

    std::cout << std::endl;
}

void generateWagonModes(std::stack<int>& trainStack, std::vector<int>& wagons, std::vector<bool>& used, int n) {
    if (trainStack.size() == n) {
        printStack(trainStack);
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            trainStack.push(wagons[i]);
            used[i] = true;

            generateWagonModes(trainStack, wagons, used, n);

            trainStack.pop();
            used[i] = false;
        }
    }
}

int main() {
    std::vector<int> wagons = {1, 2, 3};
    int n = wagons.size();

    std::stack<int> trainStack;
    std::vector<bool> used(n, false);

    std::cout << "Possible Wagon Modes:\n";
    generateWagonModes(trainStack, wagons, used, n);

    return 0;
}