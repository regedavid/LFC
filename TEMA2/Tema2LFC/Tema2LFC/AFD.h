#pragma once
#include <unordered_set>
#include <iostream>
#include <queue>
#include "AFN.h"

struct hashFunction
{
    size_t operator()(const std::pair<char,
        int>& x) const
    {
        return x.first ^ x.second;
    }
};

class AFD
{
    std::unordered_set<std::pair<char, int>, hashFunction> m_stari;
    std::unordered_set<char> m_alfabet;
    std::vector<std::tuple<std::pair<char, int>, char, std::pair<char, int>>> m_tranzitii;
    std::pair<char,int> m_stareInitiala;
    std::unordered_set<std::pair<char,int>,hashFunction> m_stariFinale;

public:
    AFD() = default;

    void makeAFD(AFN& afn);
    friend std::ostream& operator<<(std::ostream& out, const AFD& finiteAutomaton);
    bool checkWord(std::string word);
    bool VerifyAutomaton();
    bool IsDeterministic();

    std::map<char, std::vector<std::pair<char, int>>> makeMap();

    ~AFD() = default;
};

