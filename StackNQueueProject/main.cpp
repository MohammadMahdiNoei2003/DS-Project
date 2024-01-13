#include <iostream>
#include "expression.hpp"

using namespace std;

int main() {
    string exp = "b-d/(m+k)*g-l+k";
    cout << "Infix: " << exp << endl;;
    cout << "Postfix: " << infixToPostfix(exp) << endl;
    cout << "Prefix: " << infixToPrefix(exp) << endl; 
    return 0;
}