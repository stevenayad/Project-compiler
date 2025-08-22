#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stack>
#include <vector>
#include <set>
using namespace std;

class parser {
private:
    map<string, map<string, string> > predictiveTable;
    stack<string> inputtoken;
    set<string> tremails;
    set<string> nontremails;

public:
    bool isTremails(const string& s) {
        return tremails.count(s) > 0;
    }

    bool isnonTremails(const string& s) {
        return nontremails.count(s) > 0;
    }

    void loadTremails(const string& filename) {
        ifstream file(filename.c_str());
        if (!file.is_open()) {
            cerr << "Error: Could not open " << filename << endl;
            return;
        }
        string word;
        while (file >> word) {
            tremails.insert(word);
        }
    }

    void loadnonTremails(const string& filename) {
        ifstream file(filename);
        string word;
        while (file >> word) {
            nontremails.insert(word);
        }
    }

    void loadpredectivetable(const string& filename) {
        ifstream inputfile(filename);
        string line;
        while (getline(inputfile, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string lhs, tremail, word;
            ss >> lhs >> tremail;
            string productions;
            while (ss >> word) {
                if (!productions.empty()) productions += " ";
                productions += word;
            }
            predictiveTable[lhs][tremail] = productions;
        }
    }

    void loadTokens(const string& filename) {
        ifstream input(filename.c_str());
        string line;
        vector<string> tempTokens;

        while (getline(input, line)) {
            if (!line.empty()) {
                stringstream ss(line);
                string tokenType;
                ss >> tokenType;
                tempTokens.push_back(tokenType);
            }
        }

        inputtoken.push("$");
        for (int i = tempTokens.size() - 1; i >= 0; --i) {
            inputtoken.push(tempTokens[i]);
        }
    }

    bool parse(const string& firstSymbol) {
        stack<string> inputstack;
        inputstack.push("$");
        inputstack.push(firstSymbol);

        while (!inputstack.empty()) {
            if (inputtoken.empty()) {
                cout << "Parsing failed: input empty" << endl;
                return false;
            }

            string topStack = inputstack.top();
            string currentInput = inputtoken.top();

            if (isnonTremails(topStack)) {
                if (!predictiveTable[topStack][currentInput].empty()) {

                    inputstack.pop();
                    string production = predictiveTable[topStack][currentInput];

           
                    if (!(production.size() == 1 && production[0] == 'e')) {
                        vector<string> symbols;
                        stringstream ss(production);
                        string sym;
                        while (ss >> sym) {
                            symbols.push_back(sym);
                        }
                        for (int j = symbols.size() - 1; j >= 0; j--) {
                            inputstack.push(symbols[j]);
                        }
                    }
                }
                else {
                    cout << "Error: No rule for (" << topStack << ", " << currentInput << ")" << endl;
                    cout << "Parsing failed" << endl;
                    return false;
                }
            }
            else if (isTremails(topStack)) {
                if (topStack == currentInput) {
                    inputstack.pop();
                    inputtoken.pop();
                }
                else {
                    cout << "Error: Terminal mismatch (" << topStack << " != " << currentInput << ")" << endl;
                    cout << "Parsing failed" << endl;
                    return false;
                }
            }
            else if (topStack == "$" && currentInput == "$") {
                cout << "Parsing success" << endl;
                return true;
            }
            else {
                cout << "Error: Unrecognized symbol on stack: " << topStack << endl;
                cout << "Parsing failed" << endl;
                return false;
            }
        }

        if (inputtoken.size() > 1 || inputtoken.top() != "$") {
            cout << "Parsing failed: Extra input remaining" << endl;
        }
        return false;
    }
};
