#include "formaPoloneza.h"
#include "AFN.h"
#include "AFD.h"
#include <iostream>
#include <regex>

int verificare_expresie(std::string expresie);
AFN createAFN(const char symbol, const char contor);
AFN Concatenare(const AFN& afn1, const AFN& afn2);
AFN Parallel(const AFN& afn1, const AFN& afn2, const char contor);
AFN CreateAFNFromPolishForm(std::vector<std::string> polishForm);


int main()
{
	std::ifstream in("date.in");
	std::string expresie;
	getline(in, expresie);
	if (verificare_expresie(expresie) == 1)
	{
		formaPoloneza f;
		std::vector<std::string>fp = f(expresie);
		for (auto& it : fp)
		{
			std::cout << it;
		}
		std::cout << std::endl;
		AFN result = CreateAFNFromPolishForm(fp);
		AFD result2;
		result2.makeAFD(result);

		std::cout << "Expresia este valida :)" << std::endl << std::endl;
		while (true)
		{
			std::cout << "1. Afisarea automatului" << std::endl;
			std::cout << "2. Afisarea inteligibila a expresiei regulate din fisier" << std::endl;
			std::cout << "3. Verifcarea unui cuvânt în automat" << std::endl;
			std::cout << "4. Exit" << std::endl;
			int choice;
			std::cin >> choice;
			switch (choice)
			{
			case 1:
			{
				std::cout << "Afisarea automatului este:" << std::endl;
				std::cout << result;
				break;
			}
			case 2:
			{
				std::cout << "Afisarea inteligibila a expresiei regulate din fisier este:" << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "Ai ales sa verifici un cuvânt în automat" << std::endl;
				std::string word;
				std::cout << "Cuvantul de verificat este: ";
				std::cin >> word;
				break;
			}
			case 4:
				return 0;
			default:
				std::cout << "Input gresit. Va rog reincercati." << std::endl;
			}
			return 0;
		}
	}
	else
	{
		std::cout << "Expresia nu este valida." << std::endl;
		return 0;
	}
	

}

int verificare_expresie(std::string expresie)
{
	std::regex find("([*]+)");
	std::string replace("*");
	expresie = std::regex_replace(expresie, find, replace);

	std::string op_cu_paranteze(" ().*|");
	std::string op_fara(".*|");
	std::stack<char> paranteze;
	char prev(' ');
	for (char c : expresie)
	{
		if (isalpha(c)==0 && op_cu_paranteze.find(c)==std::string::npos)
		{
			std::cerr << "Caractere nepermise" << std::endl;
			return 0;
		}
		if (op_fara.find(c) != std::string::npos && (op_fara.find(prev) != std::string::npos || prev=='('))
		{
			std::cerr << "Prea multi operatori" << std::endl;
			return 0;
		}
		else
			if (op_cu_paranteze.find(c) != std::string::npos)
				prev = c;
		if (isalpha(c) != 0)
			prev = ' ';

		if (c == '(')
			paranteze.push(c);
		if (c == ')' && paranteze.top() == '(')
		{
			paranteze.pop();
		}
		if (paranteze.size() != 0)
			if (c == ')' && paranteze.top() != '(')
			{
				std::cerr << "Parantezare gresita"<<std::endl;
				return 0;
			}
	}

	if (paranteze.size() != 0)
	{
		std::cerr << "Parantezare gresita" << std::endl;
		return 0;
	}
	else
		return 1;

}

AFN createAFN(const char symbol, const char contor)
{
	AFN result;
	std::unordered_set<char> symbols;
	symbols.insert(symbol);
	result.SetAlfabet(symbols);

	std::unordered_set<char> stari;
	stari.insert(contor);
	stari.insert(contor + 1);
	result.SetStari(stari);

	result.SetStareInitiala(contor);
	std::unordered_set<char> stariFinale;
	stariFinale.insert(contor + 1);
	result.SetStariFinale(stariFinale);

	std::vector<std::pair<std::pair<char, char>, char>> tranzitii;
	tranzitii.push_back(std::make_pair(std::make_pair(contor, symbol), contor + 1));
	result.SetTranzitii(tranzitii);

	return result;
}

AFN Concatenare(const AFN& afn1, const AFN& afn2)
{
	AFN result;
	result.SetStareInitiala(afn1.GetStareInitiala());
	result.SetStariFinale(afn2.GetStariFinale());
	char stareFinalaAFN1 = *(afn1.GetStariFinale().begin());
	std::vector<std::pair<std::pair<char, char>, char>> tranzitii2;
	std::vector<std::pair<std::pair<char, char>, char>> tranzitiiFinal;
	for (auto& it : afn2.GetTranzitii()) {
		tranzitii2.push_back(it);
	}
	for (auto& it : tranzitii2) {
		if (it.first.first == afn2.GetStareInitiala()) {
			it.first.first = stareFinalaAFN1;
		}
	}
	for (auto& it : afn1.GetTranzitii()) {
		tranzitiiFinal.push_back(it);
	}
	for (auto& it : tranzitii2) {
		tranzitiiFinal.push_back(it);
	}
	result.SetTranzitii(tranzitiiFinal);
	std::unordered_set<char> stariAFN2;
	std::unordered_set<char> stariFinal;
	for (auto& it : afn2.GetStari()) {
		if (it != afn2.GetStareInitiala())
			stariAFN2.insert(it);
	}
	for (auto& it : afn1.GetStari()) {
		stariFinal.insert(it);
	}
	for (auto& it : stariAFN2) {
		stariFinal.insert(it);
	}
	result.SetStari(stariFinal);
	std::unordered_set<char> alfabet;
	for (auto& it : afn1.GetAlfabet()) {
		alfabet.insert(it);
	}
	for (auto& it : afn2.GetAlfabet()) {
		alfabet.insert(it);
	}
	result.SetAlfabet(alfabet);
	return result;
}

AFN Parallel(const AFN& afn1, const AFN& afn2, const char contor) {
	AFN result;
	std::vector<std::pair<std::pair<char, char>, char>> tranzitii;
	for (auto& it : afn1.GetTranzitii()) {
		tranzitii.push_back(it);
	}
	for (auto& it : afn2.GetTranzitii()) {
		tranzitii.push_back(it);
	}
	tranzitii.push_back(std::make_pair(std::make_pair(contor, '~'), afn1.GetStareInitiala()));
	tranzitii.push_back(std::make_pair(std::make_pair(contor, '~'), afn2.GetStareInitiala()));

	tranzitii.push_back(std::make_pair(std::make_pair(*(afn1.GetStariFinale().begin()), '~'), contor + 1));
	tranzitii.push_back(std::make_pair(std::make_pair(*(afn2.GetStariFinale().begin()), '~'), contor + 1));

	result.SetTranzitii(tranzitii);
	result.SetStareInitiala(contor);

	std::unordered_set<char> stariFinale;
	stariFinale.insert(contor + 1);
	result.SetStariFinale(stariFinale);

	std::unordered_set<char> stari;
	for (auto& it : afn1.GetStari()) {
		stari.insert(it);
	}
	for (auto& it : afn2.GetStari()) {
		stari.insert(it);
	}
	stari.insert(contor);
	stari.insert(contor + 1);
	result.SetStari(stari);

	std::unordered_set<char> alfabet;
	for (auto& it : afn1.GetAlfabet()) {
		alfabet.insert(it);
	}
	for (auto& it : afn2.GetAlfabet()) {
		alfabet.insert(it);
	}
	result.SetAlfabet(alfabet);
	return result;
}

AFN CreateAFNFromPolishForm(std::vector<std::string> polishForm) {
	std::stack<AFN> AFNstack;
	char contor = 'A';
	for (auto& it : polishForm) {
		if (it == ".") {
			AFN afn1 = AFNstack.top();
			AFNstack.pop();
			AFN afn2 = AFNstack.top();
			AFNstack.pop();
			AFN result = Concatenare(afn2, afn1);
			AFNstack.push(result);
		}
		else if (it == "|") {
			AFN afn1 = AFNstack.top();
			AFNstack.pop();
			AFN afn2 = AFNstack.top();
			AFNstack.pop();
			AFN result = Parallel(afn2, afn1, contor);
			AFNstack.push(result);

			contor += 2;
		}
		else if (it == "*") {
			AFN afn1 = AFNstack.top();
			AFNstack.pop();
			afn1.inchidereKleene(contor);
			AFNstack.push(afn1);

			contor += 2;
		}
		else if (it == "") {
			break;
		}
		else {
			char symbol = it[0];
			AFN result = createAFN(symbol, contor);
			AFNstack.push(result);

			contor += 2;
		}
	}
	AFN result = AFNstack.top();
	result.SetNullChar('~');
		return result;
}

