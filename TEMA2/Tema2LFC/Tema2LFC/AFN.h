#pragma once
#include <unordered_set>
#include <iostream>
#include <map>



class AFN
{
	std::unordered_set<char> m_stari; //starile automatului(o sa fie doar q) 
	std::unordered_set<char> m_alfabet; //alfabetul automatului
	std::vector<std::pair<std::pair<char, char>, char>> m_tranzitii;
	char m_stareInitiala; //starea initiala
	char m_nullcharacter;
	std::unordered_set<char> m_stariFinale;

public:
	std::unordered_set<char> EpsilonClosure(std::unordered_set<char> states);
	std::unordered_set<char> GetTransition(char state, char symbol);

	bool IsFinalState(char state);
	friend std::ostream& operator<<(std::ostream& out, const AFN& finiteAutomaton);
	void inchidereKleene(char contor);

	bool VerifyAutomaton();
	bool CheckWord(std::string word);
	bool IsDeterministic();
	std::map<char, std::vector<char>> makeTable();

	void getLambdaClosures(char stare, std::unordered_set<char>& stariInchise);

	//setters
	void SetStari(const std::unordered_set<char>& stari);
	void SetAlfabet(const std::unordered_set<char>& alfabet);
	void SetTranzitii(const std::vector<std::pair<std::pair<char, char>, char>>& tranzitii);
	void SetStareInitiala(const char& stareInitiala);
	void SetStariFinale(const std::unordered_set<char>& stariFinale);
	void SetNullChar(const char& nullChar);

	std::unordered_set<char> GetStari()const;
	std::unordered_set<char> GetAlfabet()const;
	std::vector<std::pair<std::pair<char, char>, char>> GetTranzitii()const;
	char GetStareInitiala()const;
	std::unordered_set<char> GetStariFinale()const;
};

