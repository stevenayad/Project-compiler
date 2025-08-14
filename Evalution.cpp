#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <stack>
#include <vector>
#include <set>
#include <cctype>
#include <stdexcept>
using namespace std;
enum operations {
    PLUS = 1,
    MINUS = 1,
    MULTIPLY = 2,
    DIVIDE = 2,
    OPEN_PAREN = 0,
    CLOSE_PAREN = 0
};

class ExpressionConverter {
private:
    stack<char> operators;
    stack<double> cal;   
    string result;

    int getOperationPriority(char op) {
        switch (op) {
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return MULTIPLY;
        case '/': return DIVIDE;
        case '(': return OPEN_PAREN;
        case ')': return CLOSE_PAREN;
        default:  return -1;
        }
    }


    bool parseDouble(const string& s, double& out) {
        std::istringstream iss(s);
        iss >> out;
        return iss && iss.eof();
    }

public:
  
    string infixToPostfix(const string& str) {
        while (!operators.empty()) operators.pop();
        result = "";

        for (int i = 0; i < (int)str.length(); i++) {
            char ch = str[i];

            if (isspace((unsigned char)ch)) continue;

            if (isdigit((unsigned char)ch) || ch == '.') {
                string number;
                bool hasDot = (ch == '.');
                number += ch;
                i++;
                while (i < (int)str.length()) {
                    char d = str[i];
                    if (isdigit((unsigned char)d)) {
                        number += d;
                        i++;
                    } else if (d == '.' && !hasDot) {
                        hasDot = true;
                        number += d;
                        i++;
                    } else {
                        break;
                    }
                }
                result += number;
                result += ' ';
                i--; 
            }
            else if (ch == '(') {
                operators.push(ch);
            }
            else if (ch == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    result += operators.top();
                    result += ' ';
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == '(') operators.pop();
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                while (!operators.empty() &&
                       operators.top() != '(' &&
                       getOperationPriority(ch) <= getOperationPriority(operators.top())) {
                    result += operators.top();
                    result += ' ';
                    operators.pop();
                }
                operators.push(ch);
            }
            else {
            
            }
        }
        while (!operators.empty()) {
            if (operators.top() != '(') {
                result += operators.top();
                result += ' ';
            }
            operators.pop();
        }
        return result;
    }

  
    double Evalation(const string& postfix) {
        while (!cal.empty()) cal.pop();
        istringstream ss(postfix);
        string token;

        while (ss >> token) {
          
            double val;
            if (parseDouble(token, val)) {
                cal.push(val);
            } else if (token == "+" || token == "-" || token == "*" || token == "/") {
                if (cal.size() < 2) throw runtime_error("Invalid postfix expression");
                double b = cal.top(); cal.pop();
                double a = cal.top(); cal.pop();
                if (token == "+") cal.push(a + b);
                else if (token == "-") cal.push(a - b);
                else if (token == "*") cal.push(a * b);
                else if (token == "/") {
                    if (b == 0.0) throw runtime_error("Division by zero");
                    cal.push(a / b);
                }
            } else {
         
                throw runtime_error("Unknown token in postfix: " + token);
            }
        }
        if (cal.empty()) throw runtime_error("Empty evaluation stack");
        return cal.top();
    }
};