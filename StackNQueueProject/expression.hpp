#include <bits/stdc++.h>

using namespace std;

bool isOperator(char c) {
    return (c == '+' or c == '-' or c == '*' or c == '/' or c == '^');
}

int prec(char c) {
    if (c == '^') 
        return 3;
    else if (c == '/' or c == '*' or c == '%') 
        return 2;
    else if (c == '-' or c == '+')
        return 1;
    else    
        return -1;
}

char associativity(char c) {
    if (c == '^') 
        return 'R';
    return 'L';
}

string infixToPostfix(string infix) {
    stack<char> myStack;
    string result;

    for (char c : infix) {
        
        if (isalnum(c)) {
            result += c;
        }
        else if (c == '(') {
            myStack.push('(');
        }
        else if (c == ')') {
            while (myStack.top() != '(') {
                result += myStack.top();
                myStack.pop();
            }
            myStack.pop();
        }
        else {
            while (!myStack.empty() and prec(c) < prec(myStack.top()) or !myStack.empty() and
                prec(c) == prec(myStack.top()) and associativity(c) == 'L') {
                    result += myStack.top();
                    myStack.pop();
                }
                myStack.push(c);
        }
    }

    while (!myStack.empty()) {
        result += myStack.top();
        myStack.pop();
    }

    return result;
}

string infixToPrefix(string infix) {
    std::string prefix;
    std::stack<char> operatorStack;

    // Reverse the infix expression
    std::string reversedInfix = infix;
    std::reverse(reversedInfix.begin(), reversedInfix.end());

    for (char c : reversedInfix) {
        if (isalnum(c)) {
            // If operand, add to the prefix expression
            prefix += c;
        } else if (c == ')') {
            // If ')', push onto the operator stack
            operatorStack.push(c);
        } else if (c == '(') {
            // If '(', pop operators from stack and add to prefix until ')'
            while (!operatorStack.empty() && operatorStack.top() != ')') {
                prefix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop(); // Pop the corresponding ')'
        } else if (isOperator(c)) {
            // If operator, pop operators with higher or equal precedence and add to prefix
            while (!operatorStack.empty() && prec(operatorStack.top()) >= prec(c)) {
                prefix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }

    // Pop any remaining operators from the stack and add to prefix
    while (!operatorStack.empty()) {
        prefix += operatorStack.top();
        operatorStack.pop();
    }

    // Reverse the prefix expression to get the final result
    std::reverse(prefix.begin(), prefix.end());

    return prefix;
}

