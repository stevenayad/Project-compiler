#include <iostream>
#include <stack>
#include <string>
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
        default:
            cout << "Unknown operator: " << op << endl;
            return -1;
        }
    }

public:
    double Evalation(string str) {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];
            if (isdigit(ch) || ch == '.') {
                string numStr = "";
                while (i < str.length() && (isdigit(str[i]) || str[i] == '.')) {
                    numStr += str[i];
                    i++;
                }
                double num = stod(numStr);
                cal.push(num);
                i--;
            }
            else if (ch == '+') {
                double num1 = cal.top();
                cal.pop();
                double num2 = cal.top();
                cal.pop();
                double re = num2 + num1;
                cal.push(re);
            }
            else if (ch == '-') {
                double num1 = cal.top();
                cal.pop();
                double num2 = cal.top();
                cal.pop();
                double re = num2 - num1;
                cal.push(re);
            }
            else if (ch == '/') {
                try {
                    double num1 = cal.top(); cal.pop();
                    double num2 = cal.top(); cal.pop();

                    double re = num2 / num1;
                    cal.push(re);
                }
                catch (const exception& e) {
                    cout << "Error during division: Division by zero is not allowed" << endl;
                }
            }
            else if (ch == '*') {
                double num1 = cal.top();
                cal.pop();
                double num2 = cal.top();
                cal.pop();
                double re = num1 * num2;
                cal.push(re);
            }
        }
        return cal.top();
    }
    string infixToPostfix(string str) {
        result = "";
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];

            if (isdigit(ch) || ch == '.') {
                while (i < str.length() && (isdigit(str[i]) || str[i] == '.')) {
                    result += str[i];
                    i++;
                }
                result += ' ';
                i--;
            }
            else if (ch == '(') {
                if (i > 0 && (isdigit(str[i - 1]) || str[i - 1] == ')')) {
                    while (!operators.empty() && getOperationPriority('*') <= getOperationPriority(operators.top())) {
                        result += operators.top();
                        result += ' ';
                        operators.pop();
                    }
                    operators.push('*');
                }
                operators.push(ch);
            }
            else if (ch == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    result += operators.top();
                    result += ' ';
                    operators.pop();
                }
                if (!operators.empty()) operators.pop();
            }
            else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
                while (!operators.empty() && getOperationPriority(ch) <= getOperationPriority(operators.top())) {
                    result += operators.top();
                    result += ' ';
                    operators.pop();
                }
                operators.push(ch);
            }
        }
        while (!operators.empty()) {
            result += ' ';
            result += operators.top();
            operators.pop();
        }

        return result;
    }
};
//int main() {
//    ExpressionConverter converter;
//
    ////Example 1
    //string infix1 = "10.2*(2.3+1.5+5.6)(2*3)";
    //string postfix1 = converter.infixToPostfix(infix1);
    //double result = converter.Evalation(postfix1);
    //cout << "Infix: " << infix1 << endl;
    //cout << "Postfix: " << postfix1 << endl;
    //cout << "Result: " << result;
    //cout << endl;
//    //Example2
//    /*string infix2 = "2+((8+2*3)/2)-1";
//    string postfix2 = converter.infixToPostfix(infix2);
//    int result2 = converter.Evalation(postfix2);
//    cout << "Infix: " << infix2 << endl;
//    cout << "Postfix: " << postfix2 << endl;
//    cout << "Result: " << result2;*/
//    return 0;
//}