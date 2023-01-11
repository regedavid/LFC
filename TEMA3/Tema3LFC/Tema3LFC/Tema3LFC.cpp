
#include <iostream>
#include <fstream>
#include "Grammar.h"
#include "PDAutomaton.h"

void GrammarToPDAutomaton(Grammar& grammar, PDAutomaton& automaton) {
    //terminale to alfabet
    automaton.SetAlfabet(grammar.GetTerminale());

    //stare initiala
    std::unordered_set<char> stari;
    stari.insert('q');
    automaton.SetStari(stari);

    //neterminale to stariStiva
    automaton.SetStariStiva(grammar.GetNeterminale());
    
    //stare initiala
    char stareInitiala = 'q';
    automaton.SetStareInitiala(stareInitiala);

    //stare initiala stiva
    automaton.SetStareInitialaStiva(grammar.GetStartSymbol());

    //null character
    char nullchar = '~';
    automaton.SetNullCharacter(nullchar);

    //tranzitii
    std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>> tranzitii;
    auto productii = grammar.GetProductii();
    for (auto& it : productii) {
        if (it.second.size() > 1) {
            std::tuple<char, char, char> membruStang;
            std::pair<char, std::string> membruDrept;
            std::string substr = it.second.substr(1, it.second.size());
            std::get<0>(membruStang) = stareInitiala;
            std::get<1>(membruStang) = it.second[0];
            std::get<2>(membruStang) = it.first[0];

            membruDrept.first = stareInitiala;
            membruDrept.second = substr;
            
            tranzitii.push_back(std::make_pair(membruStang, membruDrept));
        }
        else {
            std::tuple<char, char, char> membruStang;
            std::pair<char, std::string> membruDrept;
            std::string substr = it.second.substr(1, it.second.size());
            std::get<0>(membruStang) = stareInitiala;
            std::get<1>(membruStang) = it.second[0];
            std::get<2>(membruStang) = it.first[0];

            membruDrept.first = stareInitiala;
            membruDrept.second = nullchar;

            tranzitii.push_back(std::make_pair(membruStang, membruDrept));
        }
    }
    automaton.SetTranzitii(tranzitii);
}
int main()
{
    Grammar grammar;
    PDAutomaton pdautomaton;
    std::ifstream fin("Text.txt");
    grammar.readGrammar(fin);
    //grammar.simplify1();
    //grammar.simplify2();
    //grammar.simplify3();
    //grammar.ChomskyNormalForm();
    
    grammar.sortGrammar();
    //grammar.GreibachNormalForm();
    std::cout << grammar;
    if (grammar.isIDC()) {
        std::cout << "idc";
    }
    else std::cout << "notIDC";
   //std::cout << grammar;
    GrammarToPDAutomaton(grammar, pdautomaton);
    std::cout << std::endl << pdautomaton;
}


