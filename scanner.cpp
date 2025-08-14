#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void scan(const string& x, ofstream& out) {
    stringstream ss(x);
    char c;
    while (ss >> c) {
        if (isdigit(c)) {
            ss.putback(c);
            double n;
            ss >> n; 
            out << "Number ( " << n << " )\n";
        }
        else if (c == '+') out << "Plus ( + )\n";
        else if (c == '-') out << "Minus ( - )\n";
        else if (c == '*') out << "Mult ( * )\n";
        else if (c == '/') out << "Div ( / )\n";
        else if (c == '(') out << "LParen ( ( )\n";
        else if (c == ')') out << "RParen ( ) )\n";
        else out << "Unknown ( " << c << " )\n";
    }
}
