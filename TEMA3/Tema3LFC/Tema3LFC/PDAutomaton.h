#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>

class PDAutomaton
{
	std::unordered_set<char> m_stari;
	std::unordered_set<char> m_alfabet;
	std::unordered_set<char> m_stariStiva;
	std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>> m_tranzitii;
	char m_stareInitiala;
	char m_stareInitialaPD;
	char m_nullcharacter;
	std::unordered_set<char> m_stariFinale;
	std::stack<char> m_stiva;

public:
	bool isDeterministic();
	friend std::ostream& operator<<(std::ostream& out, const PDAutomaton& PDAutomaton);

	void SetStari(const std::unordered_set<char>& stari);
	void SetAlfabet(const std::unordered_set<char>& alfabet);
	void SetTranzitii(const std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>& tranzitii);
	void SetStareInitiala(const char& stareInitiala);
	void SetStariFinale(const std::unordered_set<char>& stariFinale);
	void SetStariStiva(const std::unordered_set<char>& stariStiva);
	void SetStareInitialaStiva(const char& stareInitialaStiva);
	void SetNullCharacter(const char& nullChar);
};

