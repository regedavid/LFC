#pragma once
<<<<<<< Updated upstream
#include <unordered_set>
#include <iostream>

class AFD
{
	std::unordered_set<char> m_stari; //starile automatului(o sa fie doar q) 
	std::unordered_set<char> m_alfabet; //alfabetul automatului
	std::vector<std::pair<std::pair<char, char>, char>> m_tranzitii;
	char m_stareInitiala; //starea initiala
	char m_nullcharacter;
	std::unordered_set<char> m_stariFinale;

public:
<<<<<<<< Updated upstream:TEMA2/Tema2LFC/Tema2LFC/AFD.h
	friend std::ostream& operator<<(std::ostream& out, const AFD& finiteAutomaton);
========
	std::unordered_set<char> EpsilonClosure(std::unordered_set<char> states);
	std::unordered_set<char> GetTransition(char state, char symbol);
	bool IsFinalState(char state);
	friend std::ostream& operator<<(std::ostream& out, const AFN& finiteAutomaton);
>>>>>>>> Stashed changes:TEMA2/Tema2LFC/Tema2LFC/AFN.h
	void inchidereKleene(char contor);

	//setters
	void SetStari(const std::unordered_set<char>& stari);
	void SetAlfabet(const std::unordered_set<char>& alfabet);
	void SetTranzitii(const std::vector<std::pair<std::pair<char, char>, char>>& tranzitii);
	void SetStareInitiala(const char& stareInitiala);
	void SetStariFinale(const std::unordered_set<char>& stariFinale);

	std::unordered_set<char> GetStari()const;
	std::unordered_set<char> GetAlfabet()const;
	std::vector<std::pair<std::pair<char, char>, char>> GetTranzitii()const;
	char GetStareInitiala()const;
	std::unordered_set<char> GetStariFinale()const;
=======
#include<iostream>
#include<unordered_set>
#include"AFN.h"
class AFD :public AFN {
    std::unordered_set<std::unordered_set<char>> m_stari;
    std::unordered_set<char> m_alfabet;
    std::vector<std::pair<std::pair<std::unordered_set<char>, char>, std::unordered_set<char>>> m_tranzitii;
    std::unordered_set<char> m_stareInitiala;
    std::unordered_set<char> m_stariFinale;
public:
    void TransformToAFD(AFN& afn);
>>>>>>> Stashed changes
};

