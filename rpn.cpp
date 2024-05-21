#include "rpn.h"
#include <stack>

using namespace std;

double calculateRPN(const std::string& expr) {
    stack<double> operands;

    for (char c : expr){
        if (isdigit(c)) {
            operands.push(c - '0');
        }else if(c == '+' || c == '-' || c == '*' || c == '/'){
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            switch (c){
                case '+':
                    operands.push(operand1 + operand2);
                    break;
                case '-':
                    operands.push(operand1 - operand2);
                    break;
                case '*':
                    operands.push(operand1 * operand2);
                    break;
                case '/':
                    operands.push(operand1 / operand2);
                    break;
            }
        }
    }
    return operands.top();
}
