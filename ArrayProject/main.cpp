#include <iostream>
#include "string.h"

using namespace std;

int main() {
    MyString str;
    stringBuilder(str, "hello");
    drawSquare(str);
    // cout << "Original String: " << c_string(str) << endl;
    
    // endPadding(str, '*', 10);

    // cout << "Modified String: " << c_string(str) << endl;

    // bool result = isPalindrome(str);

    // cout << "String is Palindrome? " << (result ? "true" : "false") << endl;

    // int decimalResult = binaryToDecimal(str);
    
    // if (decimalResult != -1) {
    //     cout << "Decimal Result: " << decimalResult << endl;
    // } else {
    //     cout << "Invalid binary string." << endl;
    // }


    releaseString(str);

    return 0;
}
