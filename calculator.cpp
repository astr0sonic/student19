#include "calculator.h"
#include <cmath>
#include <stack>

using namespace std;

int OPEN_BRACKET=0;
int CLOSE_BRACKET=1;
int PLUS_OR_MINUS=2;
int MULT_OR_DIV=3;
int DEGREE=4;
int UNARY_MINUS=5;


void getPN(const string& expression, stack<string>* postfixNotation)
{
    stack<char> operators;
    int index = 0, openBracketsCounter = 0;
    

    for (char symbol : expression) {
        if (isspace(symbol)) {
            index++;
            continue;
        }
        
        if (isdigit(symbol) || symbol == '.') {
            string digit = "";
            while (index < expression.size() && (isdigit(expression[index]) || expression[index] == '.')) {
                digit += expression[index++];
            }
            index--;
            postfixNotation->push(digit);
        }
        else if (symbol == '(') {
            operators.push(symbol);
            openBracketsCounter++;
        }
        else if (symbol == ')') {
            
            while (operators.top() != '(') {
                postfixNotation->push(string(1, operators.top()));
                operators.pop();
            }
            openBracketsCounter--;
            operators.pop();
        }
        else if (isOperator(symbol)) {
            if (symbol == '-' && (index == 0 || expression[index - 1] == '(')) {
                operators.push('~'); // Unary Minus
            }
            else {
                while (!operators.empty() && getPriorityOperators(operators.top()) >= getPriorityOperators(symbol)) {
                    postfixNotation->push(string(1, operators.top()));
                    operators.pop();
                }
                operators.push(symbol);
            }
        }
        else {
            throw logic_error("invalid");
        }
        index++;
    }

    if (openBracketsCounter > 0) {
        throw logic_error("invalid");
    }

    while (!operators.empty()) {
        postfixNotation->push(string(1, operators.top()));
        operators.pop();
    }
}

bool isOperator(char symbol)
{
    return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^' || symbol == '~');
}

int getPriorityOperators(char symbol)
{
    int priorityOperator = -1;
    switch (symbol)
    {
        case '(':
            priorityOperator = OPEN_BRACKET; 
            break;
        case ')':
            priorityOperator = CLOSE_BRACKET;
            break;
        case '+':
        case '-':
            priorityOperator = PLUS_OR_MINUS;
            break;
        case '*':
        case '/':
            priorityOperator = MULT_OR_DIV;
            break;
        case '^':
            priorityOperator = DEGREE;
            break;
        default:
            priorityOperator = UNARY_MINUS;
            break;
    }

    return priorityOperator;
}

void reverseStack(stack<string> postfixNotation, stack<string>* reversePostfixNotation)
{
    while (!postfixNotation.empty()) {
        reversePostfixNotation->push(postfixNotation.top());
        postfixNotation.pop();
    }
}

double calculatePN(stack<string> postfixNotation)
{
    stack<double> stackRPN;

    while (!postfixNotation.empty()) {

        string symbol = postfixNotation.top();
        postfixNotation.pop();

        while(!isalnum(symbol[0]) && !isOperator(symbol[0])) {
            symbol = postfixNotation.top();
            postfixNotation.pop();
        }

        double operand = 0.0;
        if (isdigit(symbol[0])) {
            operand = stod(symbol);
            stackRPN.push(operand);
        }
        else if (isOperator(symbol[0])) {
            if (symbol[0] == '~') {
                double tempValue = stackRPN.top();
                stackRPN.pop();
                tempValue = -tempValue;
                stackRPN.push(tempValue);
            }
            else {
                if (stackRPN.size() < 2) {
                    throw logic_error("Not enough operands for operation");
                }

                double firstNumber = stackRPN.top();
                stackRPN.pop();
                double secondNumber = stackRPN.top();
                stackRPN.pop();

                double resultOperations = getExpressionValue(secondNumber, firstNumber, symbol);

                stackRPN.push(resultOperations);
            }
        }
    }

    if (stackRPN.size() != 1) {
        throw invalid_argument("Invalid expression: more than one value left in stack");
    }

    return stackRPN.top();
}

double getExpressionValue(double firstNumber, double secondNumber, string operators)
{
    double result = 0.0;
    if (operators == "+") {
        result = firstNumber + secondNumber;
    }
    else if (operators == "-"){
        result = firstNumber - secondNumber;
    }
    else if (operators == "*") {
        result = firstNumber * secondNumber;
    }
    else if (operators == "/") {
        if (secondNumber == 0.0) {
            throw logic_error("Division by zero");
        }
        else {
            result = firstNumber / secondNumber; 
        }
    }
    else if (operators == "^") {
        result = pow(firstNumber, secondNumber);
    } 
    return result;
}

double calculate(const std::string& expr) {
    stack<string> stackPostfixNotation;
    stack <string> reverseStackPostfixNotation;

    getPN(expr, &stackPostfixNotation);

    reverseStack(stackPostfixNotation, &reverseStackPostfixNotation);

    double result = calculatePN(reverseStackPostfixNotation);

    return result;
}
