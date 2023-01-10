#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>

class Grammar
{
	std::unordered_set<char> m_neterminale;
	std::unordered_set<char> m_terminale;
	char m_startSymbol;
	std::vector < std::pair<std::string, std::string>> m_productii;

	bool verifyRule1();
	bool verifyRule2();
	bool verifyRule3();
	bool verifyRule4();
	bool verifyRule5();
public:
	Grammar() = default;
	void readGrammar(std::ifstream& inputfile);
	bool verifyGrammar();
	std::string generateWord();
	bool isRegulated();
	bool isIDC();
	void simplify1();
	void simplify2();
	void simplify3();
	void ChomskyNormalForm();
	void GreibachNormalForm();

	friend bool operator<(const std::pair<std::string, std::string>& productie1, const std::pair<std::string, std::string>& productie2);
	friend std::ostream& operator<<(std::ostream& out, const Grammar& grammar);
	void sortGrammar();
	char getMaxNeterminal();
	const std::unordered_set<char> GetTerminale()const;
	const std::unordered_set<char> GetNeterminale()const;
	const char GetStartSymbol()const;
	const std::vector<std::pair<std::string, std::string>> GetProductii()const;
};

