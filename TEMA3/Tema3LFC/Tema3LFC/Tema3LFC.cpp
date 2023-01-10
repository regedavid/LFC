
#include <iostream>
#include <fstream>
#include "Grammar.h"

int main()
{
    Grammar grammar;
    std::ifstream fin("Text.txt");
    grammar.readGrammar(fin);
    //grammar.simplify1();
    //grammar.simplify2();
    //grammar.simplify3();
    //grammar.ChomskyNormalForm();
    grammar.sortGrammar();
    grammar.GreibachNormalForm();
    std::cout << grammar;
    if (grammar.isIDC()) {
        std::cout << "idc";
    }
    else std::cout << "notIDC";
    //std::cout << grammar;
}


