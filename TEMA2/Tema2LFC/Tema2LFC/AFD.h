#pragma once
#include <unordered_set>
#include <iostream>
#include <map>

class AFD
{
	std::unordered_set<char> m_stari; //starile automatului(o sa fie doar q) 
	std::unordered_set<char> m_alfabet; //alfabetul automatului
	std::vector<std::pair<std::pair<char, char>, char>> m_tranzitii;
	char m_stareInitiala; //starea initiala
	char m_nullcharacter;
	std::unordered_set<char> m_stariFinale;

public:
	friend std::ostream& operator<<(std::ostream& out, const AFD& finiteAutomaton);
	void inchidereKleene(char contor);

	bool VerifyAutomaton();
	bool CeckWord(std::string word);
	bool IsDeterministic();
	std::map<char, std::vector<char>> makeTable();

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
};

