Infix to Postfix Parser & Evaluator

This C++ project reads mathematical expressions from a text file, tokenizes them, 
validates them using a predictive parser, 
and if the syntax is correct, converts them to postfix notation and evaluates the result.

Features

- Reads expressions from input.txt.

- Tokenizes expressions and saves tokens to tokens.txt.

- Loads grammar definitions from:

   1- termails.txt (terminals)

   2- nontermails.txt (non-terminals)

   3- predectivetable.txt (LL(1) predictive parsing table)

 - Validates expressions with an LL(1) parser.

 - Converts valid infix expressions to postfix (Reverse Polish Notation).

 - Evaluates postfix expressions and prints the result.
