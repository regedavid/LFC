#pragma once
#include <unordered_set>
#include <iostream>
#include"AFN.h"
class AFD : public AFN
{
    std::unordered_set<std::unordered_set<char>> m_stari;
    std::unordered_set<char> m_alfabet;
    std::vector<std::pair<std::pair<std::unordered_set<char>, char>, std::unordered_set<char>>> m_tranzitii;
    std::unordered_set<char> m_stareInitiala;
    std::unordered_set<char> m_stariFinale;
public:
    void TransformToAFD(AFN& afn);
};

