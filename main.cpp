#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "scanner.cpp"
#include "parser.cpp"
#include "Evalution.cpp"
using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream tok("tokens.txt");

    if (!in || !tok) {
        cout << "Error opening files Scanner.\n";
        return 1;
    } else {
        cout << "Files open successfully Scanner.\n";
    }

    
    string expression;
    string line;
    while (getline(in, line)) {
        if (!line.empty()) {
            expression += line;
            scan(line, tok);   
        }
    }

    tok.close();
    in.close();

   
    parser p;
    p.loadTremails("termails.txt");
    p.loadnonTremails("nontermails.txt");
    p.loadTokens("tokens.txt");
    p.loadpredectivetable("predectivetable.txt");

    bool success = p.parse("E");

    if (success) {
        cout << "Parsing successful" << endl;

        ExpressionConverter conv;

        
        string postfix = conv.infixToPostfix(expression);
        

        try {
            double value = conv.Evalation(postfix);
            cout << "Evaluation Result = " << value << endl;
        } catch (const exception &e) {
            cerr << "Evaluation error: " << e.what() << endl;
        }
    } else {
        cout << "Parsing failed. Skipping postfix conversion and evaluation." << endl;
    }

    return 0;
}
