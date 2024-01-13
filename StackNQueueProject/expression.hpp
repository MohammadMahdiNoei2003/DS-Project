#include <bits/stdc++.h>

using namespace std;

bool isOperator(char c) {
    return (!isalpha(c) && !isdigit(c));
}

int prec(char c) {
    if (c == '-' or c == '+') {
        return 1;
    } else if (c == '*' or c == '/' or c == '%') {
        return 2;
    } else if (c == '^') {
        return 3;
    }
    return 0;
}

string infixToPostfix(string& infix) {
    infix = '(' + infix + ')';
    stack<char> myStack;
    string postfix;

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            myStack.push('(');
        } else if (c == ')') {
            while (myStack.top() != '(') {
                postfix += myStack.top();
                myStack.pop();
            }
            myStack.pop();
        } else {
            if (isOperator(myStack.top())) {
                if (c == '^') {
                    while (prec(c) <= prec(myStack.top())) {
                        postfix += myStack.top();
                        myStack.pop();
                    }
                } else {
                    while (prec(c) < prec(myStack.top())) {
                        postfix += myStack.top();
                        myStack.pop();
                    }
                }
                myStack.push(c);
            }
        }
    }
    while (!myStack.empty()) {
        postfix += myStack.top();
        myStack.pop();
    }   
    return postfix;
}

string infixToPrefix(string& infix) {
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    string prefix = infixToPostfix(infix);
    reverse(prefix.begin(), prefix.end()); 

    return prefix;
}