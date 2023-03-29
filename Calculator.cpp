#include <iostream>

//function to calculate the length of the expression
int expLength(char exp[]) {
    int expLength = 0;
    while(exp[expLength] != '\0') {
        ++expLength;
    }
    return expLength;
}

//function that turns char to integer
int charToInt(char c) {
    return (c - '0');
}

//function that turns string into a floating number
float strToNum(char str[]) {
    float digits[100] = {0};
    bool isFloat = false;
    float res = 0;
    for(int i = expLength(str) - 1; i >= 0; --i) {
        if(str[i] == '.') {
            isFloat = true;
            digits[expLength(str) - 1 - i] = 10;
            continue;
        }
        digits[expLength(str) - 1 - i] = charToInt(str[i]);
    }
    int dotIndex = 0;
    if(!isFloat) {
        dotIndex = -1;
    }
    else {
        for (int i = 0; i < expLength(str); ++i) {
            if(digits[i] == 10) {
                dotIndex = i;
                break;
            }
        }
    }
    float ten = 1;
    for(int i = dotIndex + 1; i < expLength(str); ++i) {
        res = res + digits[i] * ten;
        ten *= 10;
    }
    if(isFloat) {
        ten = 0.1;
        for(int i = dotIndex - 1; i >= 0; --i) {
            digits[i] *= ten;
            res += digits[i];
            ten *= 0.1;
        }
    }
    return res;
}

//function that calculates the result
bool calc(float n1, float n2, char op, float& res) {
    if(op == '+') {
        res = (n1 + n2);
    }
    if(op == '-') {
        res = n1 - n2;
    }
    if(op == '*') {
        res = n1 * n2;
    }
    if(op == '/') {
        if(n2 == 0) {
            return false;
        }
        res = n1 / n2;
    }
    if(op != '+' && op != '-' && op != '*' && op != '/') {
        return false;
    }
    return true;
}

int main() {

    std::cout << "Enter a mathematical expression: " << std::endl;
    std::cout << "1. Expression should have two operands and one mathematical binary operation. " << std::endl;
    std::cout << "2. Operands and the operator should be seperated with spaces." << std::endl;
    std::cout << "3. Write floating numbers with a dot. " << std::endl;
    std::cout << "4. Operands should be positive. " << std::endl << std::endl;
    std::cout << "You can input as many expressions as you want. " << std::endl;
    std::cout << "If you want to end the program, input -1. " << std::endl << std::endl;
    char exp[100] = {0};

    do {
        //inputting the expression and setting the operands and operator
        std::cout << std::endl << "Your expression: ";
        std::cin.getline(exp, 100);
        char n1[100] = {0};
        char n2[100] = {0};
        char op = '\0';
        for(int i = 0; i < expLength(exp); ++i) {
            if(exp[i] == ' ' && expLength(n1) == 0) {
                for(int j = 0; j < i; ++j) {
                    n1[j] = exp[j];
                }
                continue;
            }
            if(exp[i] == ' ' && expLength(n2) == 0 && expLength(n1) > 0) {
                op = exp[i - 1];
                continue;
            }
            if(expLength(n1) > 0 && op != '\0') {
                for(int j = i; j < expLength(exp); ++j) {
                    n2[j - i] = exp[j];
                }
            }
            if(expLength(n1) > 0 && op != '\0' && expLength(n2) > 0) {
                break;
            }
        }

        //checking if the expression is correct
        if((strToNum(n1) == 0 && strToNum(n2) == 0 && op == '\0') && 
           (exp[0] != '-' || exp[1] != '1' || expLength(exp) > 2)) {
            std::cout << "Invalid expression, try again. " << std::endl;
            continue;
        }
        
        //calculating the result of the expression
        float res = 0;
        if(calc(strToNum(n1), strToNum(n2), op, res)) {
            std::cout << "Result: " << res << std::endl;
        }
        else {
            if(strToNum(n2) == 0 && expLength(n2) > 0) {
                std::cout << "Can't divide by zero." << std::endl;
            }
            else if(exp[0] != '-' || exp[1] != '1' || expLength(exp) > 2) {
                std::cout << "Invalid expression, try again. " << std::endl;
            }
        }
    }
    while (exp[0] != '-' || exp[1] != '1' || expLength(exp) > 2);
    return 0;
}

