#include <iostream>
#include "expression.hpp"

using namespace std;

int main() {
    string exp = "a+b*c-(d/e+f)*g";
    cout << "Infix: " << exp << endl;;
    cout << "Postfix: " << infixToPostfix(exp) << endl;
    cout << "Prefix: " << infixToPrefix(exp) << endl; 
    return 0;
}