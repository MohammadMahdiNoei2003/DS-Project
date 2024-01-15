/**
 * This is library of string processing in cpp written by Mohammad Mahdi Noei includes 
 * functions for string processing
*/

#include <iostream>
#include <cmath>

using namespace std;

// define structure of string by array. includes data and size.
struct MyString {
    char* data;
    int size;
};

// defining structure of ParseData to converting data type of string into integer type and float type
struct ParsedData {
    int integerData;
    float floatData;
    double doubleData;
};

// convert character to integer type
int paresInt(const char* ch, int& result) {
    int i = 0;
    result = 0;

    while (ch[i] >= '0' && ch[i] <= '9') {
        result = result * 10 + (ch[i] - '0');
        i++;
    }
    return i;
}

// convert character to float type 
int parseFloat(const char* ch, float& result) {
    int i = 0;
    result = 0.0f;
    float decimalPlace = 0.1f;

    while (ch[i] >= '0' && ch[i] <= '9') {
        result = result * 10 + (ch[i] - '0');
        i++;
    }

    if (ch[i] == '.') {
        i++;

        while (ch[i] >= '0' && ch[i] <= '9') {
            result += (ch[i] - '0') * decimalPlace;
            decimalPlace *= 0.1f;
            i++;
        }
    }
    return i;
}

// convert string to integer and float with two above functions 
ParsedData parseString(const MyString& str) {
    ParsedData result;

    int index = paresInt(str.data, result.integerData);

    while (index < str.size && (str.data[index] == ' ' || str.data[index] == '\t')) {
        index++;
    }

    index += parseFloat(str.data + index, result.floatData);

    while (index < str.size && (str.data[index] == ' ' || str.data[index] == '\t')) {
        index++;
    }   

    parseFloat(str.data + index, result.floatData);

    return result;
}

// making string using structure with array of characters 
void stringBuilder(MyString& str, const char* input) {
    str.size = 0;
    while(input[str.size] != '\0') {
        str.size++;
    }

    str.data = new char[str.size + 1];

    for (int i = 0; i < str.size; i++) {
        str.data[i] = input[i];
    }

    str.data[str.size] = '\0';
}

// deleting garbage of string 
void releaseString(MyString& str) {
    delete[] str.data;
}

// calculating length of string 
int length(MyString& str) {
    return str.size;
}

// write string data to output
const char* stringWriter(const MyString& str) {
    return str.data;
}

// concat second string to end of first string
void concat(MyString& str, const char* input) {
    int inputSize = 0;
    while (input[inputSize] != '\0') {
        inputSize++;
    }

    char* temp = new char[str.size + inputSize + 1];

    for (int i = 0; i < str.size; i++) {
        temp[i] = str.data[i];
    }

    for (int i = 0; i < inputSize; i++) {
        temp[str.size + i] = input[i];
    }

    temp[str.size + inputSize] = '\0';

    delete[] str.data;
    str.data = temp;
    str.size += inputSize;
}

// show index of substring in string
int indexOf(const MyString& str, const char* subString) {
    int subStringSize = 0;
    while(subString[subStringSize] != '\0') {
        subStringSize++;
    }

    for (int i = 0; i < str.size - subStringSize; i++) {
        bool match = true;
        for (int j = 0; j < subStringSize; j++) {
            if (str.data[i + j] != subString[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;
}

// show substring of string which starts with initialIndex and ends with length
MyString substr(const MyString& str, int initialIndex, int length) {
    if (initialIndex < 0 || initialIndex >= str.size || length < 0) {
        MyString emptyString;
        stringBuilder(emptyString, "");
        return emptyString;
    }

    if (initialIndex + length > str.size) {
        length = str.size - initialIndex;
    }

    MyString subString;
    subString.size = length;
    subString.data = new char[length + 1];

    for (int i = 0; i < length; i++) {
        subString.data[i] = str.data[initialIndex + i];
    }
    subString.data[length] = '\0';
    return subString;
}

// show index of specific character in your string
int find(const MyString& str, const char* search) {
    int searchSize = 0;
    while (search[searchSize] != '\0') {
        searchSize++;
    }

    int strSize= str.size;
    int i, j = 0;

    while(i < strSize && j < searchSize) {
        if (str.data[i] == search[j]) {
            j++;
        } else {
            i -= j;
            j = 0;
        }
        i++;
    }

    if (j == searchSize) {
        return i - j;
    }
    return -1;
}

// replacing character in your string with another character that you passed to function
void replace(MyString& str, const char* search, const char* replace) {
    int searchSize = 0;
    while (search[searchSize] != '\0') {
        searchSize++;
    }

    int replaceSize = 0;
    while(replace[replaceSize] != '\0') {
        replaceSize++;
    }
     int newSize = str.size;
     int count, i = 0;

     while (i <= newSize - searchSize) {
        if (str.data[i] == search[0]) {
            int j = 0;
            while (j < searchSize && str.data[i + j] == search[j]) {
                j++;
            }
            if (j == searchSize) {
                count++;
                newSize += replaceSize -searchSize;
                i += searchSize;
            }
        }
        i++;
     }

     char* newData = new char[newSize + 1];
     int oldIndex, newIndex = 0;

     while (oldIndex < str.size) {
        if (str.data[oldIndex] == search[0]) {
            int j = 0;
            while (j < searchSize && str.data[oldIndex + j] == search[j]) {
                j++;
            }
            if (j == searchSize) {
                for (int k = 0; k < replaceSize; k++) {
                    newData[newIndex] = replace[k];
                    newIndex++;
                }
                oldIndex += searchSize;
            } else {
                newData[newIndex] = str.data[oldIndex];
                oldIndex++;
                newIndex++;
            }
        } else {
            newData[newIndex] = str.data[oldIndex];
            oldIndex++;
            newIndex++;
        }
     }

     newData[newIndex] = '\0';
     delete[] str.data;
     str.data = newData;
     str.size = newSize;
}

bool isEmpty(MyString& str) {
    return (str.size == 0);
}

// remove substring of your string with specific length from start index
void remove(MyString& str, int index, int length) {
    if (index < 0 || index >= str.size || length < 0) {
        return;
    }
    
    int newSize = str.size - length;
    char* newData = new char[newSize + 1];

    int newIndex = 0;

    for (int i = 0; i < str.size; i ++) {
        if (i < index || i >= index + length) {
            newData[newIndex] = str.data[i];
            newIndex++;
        }
    }

    newData[newIndex] = '\0';

    delete[] str.data;
    str.data = newData;
    str.size = newSize;
}

// split string with specific characters into various substrings
void split(MyString& input, char delimiter) {
    int tokenCount = 1; // at least one token
    for (int i = 0; i < input.size; ++i) {
        if (input.data[i] == delimiter) {
            ++tokenCount;
        }
    }

    int tokenIndex = 0;
    int tokenStart = 0;

    for (int i = 0; i <= input.size; ++i) {
        if (input.data[i] == delimiter || input.data[i] == '\0') {
            MyString token;
            token.size = i - tokenStart;
            token.data = new char[token.size + 1];
            for (int j = 0; j < token.size; ++j) {
                token.data[j] = input.data[tokenStart + j];
            }
            token.data[token.size] = '\0';

            // Print each token
            cout << "Element " << tokenIndex + 1 << ": " << token.data << std::endl;

            ++tokenIndex;
            tokenStart = i + 1;

            // Release memory for the token
            delete[] token.data;
        }
    }
}

// join array of characters with specific character in string
void join(char string[], char ch);

// remove starts and ends spaces in string 
MyString trim(const MyString& str) {
    int start = 0;
    int end = str.size - 1;

    while (start <= end && isspace(str.data[start])) {
        start++;
    }

    while (end >= start && isspace(str.data[end])) {
        end--;
    }

    int trimmedSize = end - start + 1;
    MyString trimmedString;
    trimmedString.data = new char[trimmedSize + 1];
    trimmedString.size = trimmedSize;

    for (int i = 0; i < trimmedSize; i++) {
        trimmedString.data[i] = str.data[start + i];
    }
    trimmedString.data[trimmedSize] = '\0';

    return trimmedString;
}

bool equals(const MyString& str1, const MyString& str2) {
    if (str1.size != str2.size) {
        return false;
    }

    for (int i = 0; i < str1.size; i++) {
        if (str1.data[i] != str2.data[i]) {
            return false;
        }
    }

    return true;
}

// show is specific substring in your string
bool contains(const MyString& str, const char* substring) {
    int strLength = str.size;
    int subLength = 0;

    while (substring[subLength] != '\0') {
        subLength++;
    }

    if (subLength > strLength) {
        return false;
    }

    for (int i = 0; i < strLength - subLength; i++) {
        bool found = true;
        for (int j = 0; j <subLength; j++) {
            if (str.data[i + j] != substring[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return true;
        }
    }
    return false;
}

// return character index in your string
char charAt(MyString& str, int index) {
    if (index >= 0 && index < str.size) {
        return str.data[index];
    }
    return '\0';
}

// convert all characters of your string in lowercase
char toLowerCase(char ch) {
    if (ch >= 'A' && ch <='Z') {
        return ch + ('a' - 'A');
    }
    return ch;
}

// convert string to lowercase
void toLowerCase(MyString& str) {
    for (int i = 0; i < str.size; i++) {
        str.data[i] = toLowerCase(str.data[i]);
    }
}

// convert all characters of your string in uppercase
char toUpperCase(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - ('a' - 'A');
    }
    return ch;
}

// convert string to uppercase
void toUpperCase(MyString& str) {
    for (int i = 0; i < str.size; i++) {
        str.data[i] = toUpperCase(str.data[i]);
    }
}

bool startsWith(const MyString& str, const char* prefix) {
    int prefixLength = 0;
    while (prefix[prefixLength] != '\0') {
        prefixLength++;
    }
    
    if (prefixLength > str.size) {
        return false;
    }
    
    for (int i = 0; i < prefixLength; i++) {
        if (str.data[i] != prefix[i]) {
            return false;
        }
    }
    
    return true;
}

bool endsWith(const MyString& str, const char* suffix) {
    int strxLength = str.size;
    int suffixLength = 0;

    while (suffix[suffixLength] != '\0') {
        suffixLength++;
    }

    if (suffixLength > strxLength) {
        return false;
    }

    int suffixStart = strxLength - suffixLength;

    for (int i = 0; i < suffixLength; i++) {
        if (str.data[suffixStart + i] != suffix[i]) {
            return false;
        }
    } 
    return true;
}

// convert string into hash code
int hashCode(MyString& str) {
    int hash = 0;
    int prime = 31;

    for (int i = 0; i < str.size; i++) {
        hash = (hash * prime) + str.data[i];
    }
    return hash;
}

// reverse string 
void reverse(MyString& str) {
    int start = 0;
    int end = str.size - 1;

    while (start < end) {
        char temp = str.data[start];
        str.data[start] = str.data[end];
        str.data[end] = temp;
        start++;
        end--;
    }
}

// convert integer to string 
MyString toString(int number) {
    const int bufferSize = 16; // Maximum supported number of digits in an int
    char buffer[bufferSize];
    int length = snprintf(buffer, bufferSize, "%d", number);

    MyString result;
    result.size = length;
    result.data = new char[length + 1];

    for (int i = 0; i < length; ++i) {
        result.data[i] = buffer[i];
    }

    result.data[length] = '\0';

    return result;
}

// remover specific character from string 
void removeChar(MyString& str, char c) {
    int writeIndex = 0;
    for (int i = 0; i < str.size; i++) {
        if (str.data[i] != c) {
            str.data[writeIndex++] = str.data[i];
        }
    }

    str.data[writeIndex] = '\0';
    str.size = writeIndex;
}

// count number of specific character in string 
int countChar(MyString& str, char targetChar) {
    int count = 0;
    for (int i = 0; i < str.size; i++) {
        if (str.data[i] == targetChar) {
            count++;
        }
    }
    return count;
}

// first character in string will be uppercase
void capitalize(MyString& str) {
    if (str.size != 0) {
        str.data[0] = toUpperCase(str.data[0]);

        for (int i = 1; i < str.size; i++) {
            str.data[i] = toLowerCase(str.data[i]);
        }
    }
    
}

void sortStringAlphabetically(MyString& str) {
    for (int i = 0; i < str.size - 1; i++) {
        for (int j = 0; j < str.size - i - 1; j++) {
            if (str.data[j] > str.data[j + 1]) {
                char temp = str.data[j];
                str.data[j] = str.data[j + 1];
                str.data[j + 1] = temp;
            }
        }
    }
}

// function that check character is alphabet 
char AlphaNum(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '1' && ch <= '9')) 
        return ch;

    return '\0'; // Return a null character if ch is not alphabetic
}

// check string includes alphabets and numbers
bool isAlphaNum(MyString& str) {
    for (int i = 0; i < str.size; i++) {
        if (AlphaNum(str.data[i]) != '\0') {
            return true;
        }
    }  
    return false; 
}

// check string includes alphabets only
bool isAlpha(const MyString& str) {
    for (int i = 0; i < str.size; i++) {
        char currentChar = str.data[i];
        if (not((currentChar >= 'a' and currentChar <= 'z') or (currentChar >= 'A' and currentChar <= 'Z'))) {
            return false;
        }
    }
    return true;
}

// function to encoding string: replacing characters with other characters 
char encodeString(char ch) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        return (ch + 1 - 'a') % 26 + 'a';
    }
    return ch;
}

void encode(MyString& str) {
    for (int i = 0; i < str.size; i++) {
        str.data[i] = encodeString(str.data[i]);
    }
}

// check all character of string is ASCII code
bool isAscii(const MyString& str) {
    for (int i = 0; i < str.size; i++) {
        char currentChar = str.data[i];
        if (!(currentChar >= 0 && currentChar <= 127)) {
            return false;
        }
    }
    return true;
}

// check all character of string is number 
bool isDigit(const MyString& str) {
    for (int i = 0; i < str.size; i++) {
        char currentChar = str.data[i];
        if (!(currentChar >= '0' && currentChar <= '9')) {
            return false;
        }
    }
    return true;
}

// check first character of string is uppercase
bool isSuper(MyString& str) {
    for (int i = 0; i < str.size; i++) {
        char currentChar = str.data[i];
        if (!(currentChar >= 'A' && currentChar <= 'Z')) {
            return false;
        }
    }
    return true;
}

// justify string from left
void lJust(MyString& str, int width) {
    if (width <= str.size) {
        return;
    }

    char* newString = new char[width + 1];

    int i;
    for (i = 0; i < str.size; i++) {
        newString[i] = str.data[i];
    }

    for (; i < width; i++) {
        newString[i] = ' ';
    }
    newString[width] = '\0';
    delete[] str.data;

    str.data = newString;
    str.size = width;
}

// justify string from right
void rJust(MyString& str, int width) {
    if (width <= str.size) {
        return;
    }

    char* newString = new char[width + 1];

    for (int i = 0; i < width - str.size; i++) {
        newString[i] = ' ';
    }

    int j = 0;
    for (int i = width - str.size; i < width; i++) {
        newString[i] = str.data[j++];
    }

    newString[width] = '\0';
    delete[] str.data;

    str.data = newString;
    str.size = width;
}

// justify string in center
void cJust(MyString& str, int width) {
    if (width <= str.size) {
        return;
    }

    char* newString = new char[width + 1];
    int leadingSpace = (width - str.size) / 2;

    for (int i = 0; i < leadingSpace; i++) {
        newString[i] = ' ';
    }

    int j = 0;
    for (int i = leadingSpace; i < leadingSpace + str.size; i++) {
        newString[i] = str.data[j++];
    }

    for (int i = leadingSpace + str.size; i < width; i++) {
        newString[i] = ' ';
    }

    newString[width] = '\0';
    delete[] str.data;

    str.data = newString;
    str.size = width;
}

// give string of zero's and one's and calculate decimal value of binary string 
int binaryToDecimal(const MyString& str) {
    int decimalNumber = 0;

    for (int i = 0; i < str.size; i++) {
        char currentBite = str.data[i];
        if (currentBite == '1') {
            decimalNumber += (1 << (str.size - 1 - i));
        } else if (currentBite != '0') {
            return -1;
        }
    }
    return decimalNumber;
}

// replace all characters expect space with zero and replace space with one
void zeroFill(MyString& str) {
    for (int i = 0; i < str.size; i++) {
        if (str.data[i] == ' ') {
            str.data[i] = '1';
        } else {
            str.data[i] = '0';
        }
    }
}

// returns all possible substring in string 
void allSubStr(const MyString& str) {
    cout << "All Substrings: " << endl;

    for (int start = 0; start < str.size; ++start) {
        for (int end = start; end < str.size; ++end) {
            for (int i = start; i <= end; ++i) {
                cout << str.data[i];
            }
            cout << std::endl;
        }
    }
}

// check the string is symmetrical
bool isPalindrome(const MyString& str) {
    int left = 0;
    int right = str.size - 1;

    while (left < right) {
        if (str.data[left] != str.data[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

MyString compress(const MyString& str);

// count number of words in string 
int wordCounter(MyString& str) {
    if (str.size == 0) {
        return 0;
    }
    int count = 0;
    for (int i = 0; i < str.size; i++) {
        if ((str.data[i] >= 'a' && str.data[i] <= 'z') || 
        (str.data[i] >= 'A' && str.data[i] <= 'Z') || 
        (str.data[i] != '.') || (str.data[i] != ',') || 
        (str.data[i] != ';') || (str.data[i] != '\'') || 
        (str.data[i] != '\"')) {
            count++;
        }
    }
    return count;
}

// count number of sentences in string 
int sentenceCounter(MyString& str) {
    if (str.size == 0) {
        return  0;
    }

    int count = 0;
    for (int i = 0; i < str.size; i++) {
        if (str.data[i] == '.') {
            count++;
        }
    }
    return count;
}

// start with spaces in specific length 
void startPadding(MyString& str, char paddingChar, int length) {
    int paddingLength = length - str.size;

    char* newString = new char[paddingLength + 1];

    for (int i = 0; i < paddingLength; i++) {
        newString[i] = paddingChar;
    }

    for (int i = paddingLength; i < length; i++) {
        newString[i] = str.data[i - paddingLength]; 
    }

    newString[length] = '\0';
    delete[] str.data;

    str.data =  newString;
    str.size = length; 
}

// end with spaces with specific length
void endPadding(MyString& str, char paddingChar, int length) {
    int paddingLength = length - str.size;

    char* newString = new char[paddingLength + 1];

    for (int i = str.size; i < length; i++) {
        newString[i] = paddingChar;
    }

    for (int i = 0; i < paddingLength; i++) {
        newString[i] = str.data[i];
    }   

    newString[length] = '\0';
    delete str.data;

    str.data = newString;
    str.size = length; 
}

void drawDonut(const MyString& str) {
    const double A = 0.2, B = 0.1;
    const int width = 40, height = 20;

    for (int k = 0; k < 360; k += 5) {
        double a = sin(k * 3.141592653589 / 180.0);
        double b = cos(k * 3.141592653589 / 180.0);

        for (int i = 0; i < 360; i += 2) {
            double phi = i * 3.141592653589 / 180.0;
            double cosPhi = cos(phi);
            double sinPhi = sin(phi);

            for (int j = 0; j < 360; j += 1) {
                double theta = j * 3.141592653589 / 180.0;
                double cosTheta = cos(theta);
                double sinTheta = sin(theta);

                double x = cosTheta * (cosPhi * (A * cosTheta + B * sin(k + theta)) - b * sinPhi * (A * cosTheta + B * sin(k + theta))) + width / 2;
                double y = sinTheta * (cosPhi * (A * cosTheta + B * sin(k + theta)) - b * sinPhi * (A * cosTheta + B * sin(k + theta))) + height / 2;

                int screenX = static_cast<int>(x);
                int screenY = static_cast<int>(y);

                if (screenX >= 0 && screenX < width && screenY >= 0 && screenY < height) {
                    std::cout << str.data[(screenY * width) + screenX % str.size];
                } else {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
        }

        std::cout << "\033[2J\033[1;1H"; // Clear the console for the next frame
    }
}

void drawTriangle(const MyString& str) {
    const int width = 40, height = 20;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j <= i || j >= width - i - 1) {
                std::cout << str.data[(i * width + j) % str.size];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void drawSquare(const MyString& str) {
    const int size = 15;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << str.data[(i * size + j) % str.size];
        }
        std::cout << std::endl;
    }
}