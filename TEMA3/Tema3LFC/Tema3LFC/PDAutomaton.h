#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>

class PDAutomaton
{
	std::unordered_set<char> m_stari; //starile automatului(o sa fie doar q) 
	std::unordered_set<char> m_alfabet; //alfabetul automatului
	std::unordered_set<char> m_stariStiva; //starile care o sa fie in stiva
	std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>> m_tranzitii; //tranzitiile
	char m_stareInitiala; //starea initiala
	char m_stareInitialaPD; //starea initiala din stiva
	char m_nullcharacter; //caracterul null (care sterge din stiva)
	std::unordered_set<char> m_stariFinale; //nu avem stari finale
	std::stack<char> m_stiva; //stiva automatului

public:
	bool isDeterministic();
	friend std::ostream& operator<<(std::ostream& out, const PDAutomaton& PDAutomaton);
	bool Checkword(std::string word);
	bool Checkwordrec(char currentState, std::string word, std::stack<char> m_stiva);
	//Setteri
	void SetStari(const std::unordered_set<char>& stari);
	void SetAlfabet(const std::unordered_set<char>& alfabet);
	void SetTranzitii(const std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>& tranzitii);
	void SetStareInitiala(const char& stareInitiala);
	void SetStariFinale(const std::unordered_set<char>& stariFinale);
	void SetStariStiva(const std::unordered_set<char>& stariStiva);
	void SetStareInitialaStiva(const char& stareInitialaStiva);
	void SetNullCharacter(const char& nullChar);
	void ClearStiva();
};

