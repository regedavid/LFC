
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
    std::ifstream fin("text.txt");
    grammar.readGrammar(fin);

    if (grammar.verifyGrammar() && grammar.isIDC()) 
    {
        Grammar simplified = grammar;
        simplified.getSimplifiedGrammar();
        Grammar grammarFNG = simplified;
        grammarFNG.ChomskyNormalForm();
        grammarFNG.GreibachNormalForm();
        GrammarToPDAutomaton(grammarFNG, pdautomaton);

        std::cout << "The grammar is valid and IDC! :)" << std::endl<< std::endl;
        while (true) {
            std::cout << "1. Display grammar" << std::endl;
            std::cout << "2. Generate word in grammar" << std::endl;
            std::cout << "3. Display simplified grammar" << std::endl;
            std::cout << "4. Display grammar in FNG" << std::endl;
            std::cout << "5. Generate a word in grammar and verify if it is accepted in automaton" << std::endl;
            std::cout << "6. Verify if a input word is accepted by the automaton" << std::endl;
            std::cout << "7. Display Push-Down Automaton" << std::endl;
            std::cout << "8. Exit" << std::endl;

            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "You chose to display grammar:" << std::endl;
                std::cout << grammar;
                break;
            case 2:
                std::cout << "You chose to generate word in grammar:" << std::endl;
                std::cout << "Generated word: " << grammar.generateWord() << std::endl;
                break;
            case 3:
                std::cout << "You chose to display simplified grammar:" << std::endl;                             
                std::cout << simplified;
                break;
            case 4:
                std::cout << "You chose to display grammar in FNG:" << std::endl;      
                std::cout << grammarFNG;
                break;
            case 5:
            {
                std::cout << "You chose to generate a word in grammar and verify if it is accepted in automaton"<< std::endl;
                std::string word = grammar.generateWord();
                std::cout << "Generated word: " << word << std::endl;
                if (pdautomaton.Checkword(word))
                {
                    std::cout << "The word is accepted by the automaton." << std::endl;
                }
                else 
                {
                    std::cout << "The word is not accepted by the automaton." << std::endl;
                }
                break;
            }
            case 6:
            {
                std::cout << "You chose to verify if a input word is accepted by the automaton" << std::endl;
                std::string word;
                std::cout << "Enter a word to check: ";
                std::cin >> word;
                if (pdautomaton.Checkword(word)) {
                    std::cout << "The word is accepted by the automaton." << std::endl;
                }
                else {
                    std::cout << "The word is not accepted by the automaton." << std::endl;
                }
                break;
            }
            case 7:
                std::cout << pdautomaton;
                break;
            case 8:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
        return 0;
    }
    else
    {
        std::cout << "The grammar is not valid or IDC." << std::endl;
            return 0;
    }
    
}


