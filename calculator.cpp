#include "calculator.h"
#include <cmath>
#include <stack>
#include <iostream>
#include <sstream>



using namespace std;

int prior(char c)
{
    switch (c)
    {
        case '^':
            return 0;
        case '~':
            return 1;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 3;
        case '(':
            return 4;
        default:
            throw exception();
    }
}
double calculateRPN(istream& in)
{

   stack<double> s;
    while (in.peek() != EOF && in.peek() != '\n')
    {
        char c = in.peek();
        if (isdigit(c))
        {
            double d;
            in >> d;
            s.push(d);
        }
        else
        {
            double a, b;
            in.get();
            switch (c)
            {
                case '+':
                    if (s.size() < 2)
                        throw exception();
                    b = s.top(); s.pop();
                    a = s.top(); s.pop();
                    s.push(a + b);
                    break;
                case '-':
                    if (s.size() < 2)
                        throw exception();
                    b = s.top(); s.pop();
                    a = s.top(); s.pop();
                    s.push(a - b);
                    break;
                case '*':
                    if (s.size() < 2)
                        throw exception();
                    b = s.top(); s.pop();
                    a = s.top(); s.pop();
                    s.push(a * b);
                    break;
                case '/':
                    if (s.size() < 2)
                        throw exception();
                    b = s.top(); s.pop();
                    a = s.top(); s.pop();
                    s.push(a / b);
                    break;
                case '^':
                    if (s.size() < 2)
                        throw exception();
                    b = s.top(); s.pop();
                    a = s.top(); s.pop();
                    s.push(pow(a, b));
                    break;
                case '~':
                    if (s.size() < 1)
                        throw exception();
                    a = s.top(); s.pop();
                    s.push(-a);
                    break;
                case ' ':
                    break;
                default:
                    throw exception();
            }
        }
    }
    if (s.size() > 1)
        throw exception();
    return s.top();
}

double ConvertionToRPN(istream& in)
{
    int lastBracket = 0;
    bool state = false;
    stringstream out;
    stack<char> s;
    while (in.peek() != EOF && in.peek() != '\n')
    {
        char c = in.peek();
        if (isdigit(c))
        {
            if (state)
                throw exception();
            double d;
            in >> d;
            out << d << ' ';
            state = true;
        }
        else
        {
            in.get();
            switch (c)
            {
                case ' ':
                    break;
                case '^':
                case '*':
                case '/':
                case '+':
                    if (!state)
                        throw exception();
                    while (!s.empty() && prior(s.top()) <= prior(c))
                    {
                        out << s.top() << ' ';
                        s.pop();
                    }
                    s.push(c);
                    state = false;
                    break;
                case '(':
                    if (state)
                        throw exception();
                    lastBracket = in.tellg();
                    s.push(c);
                    break;
                case ')':
                    if (!state)
                        throw exception();
                    while (!s.empty() && s.top() != '(')
                    {
                        out << s.top() << ' ';
                        s.pop();
                    }
                    if (s.empty())
                        throw exception();
                    s.pop();
                    break;
                case '-':
                    if (!state)
                        c = '~';
                    while (!s.empty() && prior(s.top()) <= prior(c))
                    {
                        out << s.top() << ' ';
                        s.pop();
                    }
                    s.push(c);
                    state = false;
                    break;
                default:
                    throw exception();
            }
        }
    }
    if (!state)
        throw exception();
    while (!s.empty())
    {
        if (s.top() == '(')
            throw exception();
        out << s.top() << ' ';
        s.pop();
    }
    return calculateRPN(out);
}



double calculate(const std::string& expr) {
    stringstream str(expr);
    return ConvertionToRPN(str);

}
