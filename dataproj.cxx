#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

class Calculator {
public:
    // Perform basic arithmetic operations
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) { 
        if (b == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        return a / b; 
    }
    double power(double a, double b) { return std::pow(a, b); }

    // Convert infix expression to postfix
    std::string infixToPostfix(const std::string& infix) {
        std::stack<char> stack;
        std::string postfix;

        for (char c : infix) {
            if (isdigit(c)) {
                postfix += c;
            } else if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.empty() && stack.top() != '(') {
                    postfix += stack.top();
                    stack.pop();
                }
                if (!stack.empty() && stack.top() == '(') {
                    stack.pop();
                }
            } else {
                while (!stack.empty() && getPriority(c) <= getPriority(stack.top())) {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.push(c);
            }
        }

        while (!stack.empty()) {
            postfix += stack.top();
            stack.pop();
        }

        return postfix;
    }

    // Evaluate postfix expression
    double evaluatePostfix(const std::string& postfix) {
        std::stack<double> stack;

        for (char c : postfix) {
            if (isdigit(c)) {
                stack.push(c - '0');
            } else {
                double b = stack.top();
                stack.pop();
                double a = stack.top();
                stack.pop();

                switch (c) {
                    case '+':
                        stack.push(add(a, b));
                        break;
                    case '-':
                        stack.push(subtract(a, b));
                        break;
                    case '*':
                        stack.push(multiply(a, b));
                        break;
                    case '/':
                        stack.push(divide(a, b));
                        break;
                    case '^':
                        stack.push(power(a, b));
                        break;
                    default:
                        throw std::runtime_error("Invalid operator");
                }
            }
        }

        if (stack.size() != 1) {
            throw std::runtime_error("Invalid expression");
        }

        return stack.top();
    }

private:
    int getPriority(char op) {
        switch (op) {
            case '^':
                return 3;
            case '*':
            case '/':
                return 2;
            case '+':
            case '-':
                return 1;
            default:
                return -1;
        }
    }
};

int main() {
    Calculator calc;

    std::string expression;
    std::cout << "Enter a mathematical expression: ";
    std::getline(std::cin, expression);

    try {
        std::string postfix = calc.infixToPostfix(expression);
        std::cout << "Postfix expression: " << postfix << std::endl;
        double result = calc.evaluatePostfix(postfix);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}