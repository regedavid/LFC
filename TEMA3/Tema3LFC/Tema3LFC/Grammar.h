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

	//reguli pt verificare daca e gramatica valida
	bool verifyRule1();
	bool verifyRule2();
	bool verifyRule3();
	bool verifyRule4();
	bool verifyRule5();
public:
	Grammar() = default;
	Grammar& operator=(const Grammar& other);

	void readGrammar(std::ifstream& inputfile);
	bool verifyGrammar();
	std::string generateWord();
	bool isRegulated();
	//verificare gramatica IDC
	bool isIDC();
	//simplificare fara elemente care nu genereaza elemente din VT(terminale)
	void simplify1();
	//simplificare fara elemente inaccesibile
	void simplify2();
	//simplificare fara redenumiri
	void simplify3();

	void getSimplifiedGrammar();
	void ChomskyNormalForm();
	void GreibachNormalForm();

	friend bool operator<(const std::pair<std::string, std::string>& productie1, const std::pair<std::string, std::string>& productie2);
	friend std::ostream& operator<<(std::ostream& out, const Grammar& grammar);
	//sortarea gramaticii in functie de neterminalul din dreapta
	void sortGrammar();
	//ia neterminalul cel mai mare ca sa adauge neterminale in continuare
	char getMaxNeterminal();

	//getters
	const std::unordered_set<char> GetTerminale()const;
	const std::unordered_set<char> GetNeterminale()const;
	const char GetStartSymbol()const;
	const std::vector<std::pair<std::string, std::string>> GetProductii()const;
};

