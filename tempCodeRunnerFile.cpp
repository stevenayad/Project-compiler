parser p;
    p.ReadGrammar("grammer.txt");
    p.ExtractTerminals();
    p.loadTokens("tokens.txt");
    p.loadpredectivetable("predectivetable.txt");
    bool success = p.parse("E");