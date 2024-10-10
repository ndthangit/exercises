#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Hàm để đọc một số thực từ xâu và di chuyển con trỏ đến sau số đó
double readNumber(const char **expression) {
    double result = 0.0;
    while (isdigit(**expression) || **expression == '.') {
        result = result * 10 + (**expression - '0');
        (*expression)++;
    }
    if (**expression == '.') {
        double decimal = 10.0;
        (*expression)++;
        while (isdigit(**expression)) {
            result += (**expression - '0') / decimal;
            decimal *= 10;
            (*expression)++;
        }
    }
    return result;
}

// Hàm để đọc và tính giá trị của một biểu thức
double evaluateExpression(const char **expression);

// Hàm để đọc và tính giá trị của một factor (nhân, chia)
double evaluateFactor(const char **expression) {
    double result = readNumber(expression);
    while (**expression == '*' || **expression == '/') {
        char operator = **expression;
        (*expression)++;
        double operand = readNumber(expression);
        if (operator == '*') {
            result *= operand;
        } else if (operator == '/') {
            if (operand != 0) {
                result /= operand;
            } else {
                fprintf(stderr, "Error: Division by zero.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return result;
}

// Hàm để đọc và tính giá trị của một term (cộng, trừ)
double evaluateTerm(const char **expression) {
    double result = evaluateFactor(expression);
    while (**expression == '+' || **expression == '-') {
        char operator = **expression;
        (*expression)++;
        double operand = evaluateFactor(expression);
        if (operator == '+') {
            result += operand;
        } else if (operator == '-') {
            result -= operand;
        }
    }
    return result;
}

// Hàm để đọc và tính giá trị của một biểu thức (có thể có ngoặc)
double evaluateExpression(const char **expression) {
    if (**expression == '(') {
        (*expression)++;
        double result = evaluateTerm(expression);
        if (**expression == ')') {
            (*expression)++;
            return result;
        } else {
            fprintf(stderr, "Error: Missing closing parenthesis.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        return evaluateTerm(expression);
    }
}

int main() {
    char expression[1000];
    fgets(expression, sizeof(expression), stdin);

    const char *exprPtr = expression;
    double result = evaluateExpression(&exprPtr);

    printf("%.1f\n", result);

    return 0;
}
