#include <bits/stdc++.h>

using namespace std;

bool isOperator(char c) {
    return (!isalpha(c) && !isdigit(c));
}

bool isOperand(char c) {
    return (isalpha(c));
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

string postfixToInfix(string& postfix) {
    stack<string> myStack;

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isOperand(postfix[i])) {
            string op(1, postfix[i]);
            myStack.push(op);
        } else {
            string op1 = myStack.top();
            myStack.pop();
            string op2 = myStack.top();
            myStack.pop();
            myStack.push("(" + op2 + postfix[i] + op1 + ')');
        }
    }
    
    return myStack.top();
}

string postfixToPrefix(string& postfix) {
    stack<string> myStack;

    for (int i = 0; i < postfix.length(); i++) {
        if (isOperator(postfix[i])) {
            string op1 = myStack.top();
            myStack.pop();
            string op2 = myStack.top();
            myStack.pop();
            string temp = postfix[i] + op2 + op1;
            myStack.push(temp);
        } else {
            myStack.push(string(1, postfix[i]));
        }
    }
    string prefix = "";
    while (!myStack.empty()) {
        prefix += myStack.top();
        myStack.pop();
    }

    return prefix;
}