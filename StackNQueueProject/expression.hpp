#include <bits/stdc++.h>

using namespace std;

// Validation part **********

bool isOperator(char c) {
    return (!isalpha(c) && !isdigit(c));
}

bool isOperand(char c) {
    return (isalpha(c));
}

// *********

// Precedence **********

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

// **********

// Infix to other expression conversion **********

string infixToPostfix(string& infix) {
    stack<char> myStack;
    string postfix;

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            myStack.push(c);
        } else if (c == ')') {
            while (!myStack.empty() && myStack.top() != '(') {
                postfix += myStack.top();
                myStack.pop();
            }
            if (myStack.empty()) {
                throw runtime_error("Mismatched parentheses in infix expression");
            }
            myStack.pop(); // Pop '('
        } else if (isOperator(c)) {
            while (!myStack.empty() && prec(myStack.top()) >= prec(c)) {
                postfix += myStack.top();
                myStack.pop();
            }
            myStack.push(c);
        } else {
            throw runtime_error("Invalid character in infix expression");
        }
    }

    while (!myStack.empty()) {
        if (myStack.top() == '(') {
            throw runtime_error("Mismatched parentheses in infix expression");
        }
        postfix += myStack.top();
        myStack.pop();
    }

    return postfix;
}


string infixToPrefix(string& infix) {
    stack<char> myStack;
    string prefix;

    for (int i = infix.length() - 1; i >= 0; --i) {
        char c = infix[i];

        if (isalnum(c)) {
            prefix = c + prefix;
        } else if (c == ')') {
            myStack.push(c);
        } else if (c == '(') {
            while (!myStack.empty() && myStack.top() != ')') {
                prefix = myStack.top() + prefix;
                myStack.pop();
            }
            if (myStack.empty()) {
                throw runtime_error("Mismatched parentheses in infix expression");
            }
            myStack.pop(); // Pop ')'
        } else if (isOperator(c)) {
            while (!myStack.empty() && prec(myStack.top()) > prec(c)) {
                prefix = myStack.top() + prefix;
                myStack.pop();
            }
            myStack.push(c);
        } else {
            throw runtime_error("Invalid character in infix expression");
        }
    }

    while (!myStack.empty()) {
        if (myStack.top() == ')') {
            throw runtime_error("Mismatched parentheses in infix expression");
        }
        prefix = myStack.top() + prefix;
        myStack.pop();
    }

    return prefix;
}

// **********

// Postfix to other expression conversion **********

string postfixToInfix(string& postfix) {
    stack<string> myStack;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isOperand(postfix[i])) {
            string op(1, postfix[i]);
            myStack.push(op);
        } else if (isOperator(postfix[i])) {
            if (myStack.size() < 2) {
                throw runtime_error("Invalid postfix expression.");
            }
            string op2 = myStack.top();
            myStack.pop();
            string op1 = myStack.top();
            myStack.pop();
            myStack.push("(" + op1 + postfix[i] + op2 + ")");
        } else {
            throw runtime_error("Invalid character in postfix expression.");
        }
    }

    if (myStack.size() != 1) {
        throw runtime_error("Invalid postfix expression.");
    }
    
    return myStack.top();
}

string postfixToPrefix(string& postfix) {
    stack<string> myStack;

    for (char c : postfix) {
        if (isalnum(c)) {
            myStack.push(string(1, c));
        } else if (isOperator(c)) {
            if (myStack.size() < 2) {
                throw runtime_error("Invalid postfix expression.");
            }
            string op2 = myStack.top();
            myStack.pop();
            string op1 = myStack.top();
            myStack.pop();
            myStack.push(c + op1 + op2);
        } else {
            throw runtime_error("Invalid character in postfix expression.");
        }
    }

    if (myStack.size() != 1) {
        throw runtime_error("Invalid postfix expression.");
    }

    return myStack.top();
}

// *********

// Prefix to other expression conversion **********

string prefixToInfix(string& prefix) {
    stack<string> myStack;
    
    for (int i = prefix.length() - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            myStack.push(string(1, prefix[i]));
        } else if (isOperator(prefix[i])) {
            if (myStack.size() < 2) {
                throw runtime_error("Invalid prefix expression.");
            }
            string op1 = myStack.top();
            myStack.pop();
            string op2 = myStack.top();
            myStack.pop();
            myStack.push("(" + op1 + prefix[i] + op2 + ")");
        } else {
            throw runtime_error("Invalid character in prefix expression.");
        }
    }

    if (myStack.size() != 1) {
        throw runtime_error("Invalid prefix expression.");
    }

    return myStack.top();
}

string prefixToPostfix(string& prefix) {
    stack<string> myStack;

    for (int i = prefix.length() - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            myStack.push(string(1, prefix[i]));
        } else if (isOperator(prefix[i])) {
            if (myStack.size() < 2) {
                throw runtime_error("Invalid prefix expression.");
            }
            string op1 = myStack.top();
            myStack.pop();
            string op2 = myStack.top();
            myStack.pop();
            myStack.push(op1 + op2 + prefix[i]);
        } else {
            throw runtime_error("Invalid character in prefix expression.");
        }
    }

    if (myStack.size() != 1) {
        throw runtime_error("Invalid prefix expression.");
    }

    return myStack.top();
}

// **********