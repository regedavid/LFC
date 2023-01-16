#include "formaPoloneza.h"
#include "AFD.h"
#include <iostream>
#include <regex>

// calculele tre sa faca toate nebuniile cu automatonul in fct de forma poloneza
float calcul_forma_poloneza(std::vector<std::string> fp);
float calcul(float x, float y, char element);

// sa verificat si moficat expresia data sa fie calumea
int verificare_expresie(std::string expresie);

AFD createAFD(const char symbol, const char contor) {
	AFD result;
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

AFD Concatenare(const AFD& afd1, const AFD& afd2) {
	AFD result;
	result.SetStareInitiala(afd1.GetStareInitiala());
	result.SetStariFinale(afd2.GetStariFinale());
	char stareFinalaAFD1 = *(afd1.GetStariFinale().begin());
	std::vector<std::pair<std::pair<char, char>, char>> tranzitii2;
	std::vector<std::pair<std::pair<char, char>, char>> tranzitiiFinal;
	for (auto& it : afd2.GetTranzitii()) {
		tranzitii2.push_back(it);
	}
	for (auto& it : tranzitii2) {
		if(it.first.first==afd2.GetStareInitiala()){
			it.first.first = stareFinalaAFD1;
		}
	}
	for (auto& it : afd1.GetTranzitii()) {
		tranzitiiFinal.push_back(it);
	}
	for (auto& it : tranzitii2) {
		tranzitiiFinal.push_back(it);
	}
	result.SetTranzitii(tranzitiiFinal);
	std::unordered_set<char> stariAFD2;
	std::unordered_set<char> stariFinal;
	for (auto& it : afd2.GetStari()) {
		if(it!= afd2.GetStareInitiala())
		stariAFD2.insert(it);	
	}
	for (auto& it : afd1.GetStari()) {
		stariFinal.insert(it);
	}
	for (auto& it : stariAFD2) {
		stariFinal.insert(it);
	}
	result.SetStari(stariFinal);
	std::unordered_set<char> alfabet;
	for (auto& it : afd1.GetAlfabet()) {
		alfabet.insert(it);
	}
	for (auto& it : afd2.GetAlfabet()) {
		alfabet.insert(it);
	}
	result.SetAlfabet(alfabet);
	return result;
}

AFD Parallel(const AFD& afd1, const AFD& afd2, const char contor) {
	AFD result;
	std::vector<std::pair<std::pair<char, char>, char>> tranzitii;
	for (auto& it : afd1.GetTranzitii()) {
		tranzitii.push_back(it);
	}
	for (auto& it : afd2.GetTranzitii()) {
		tranzitii.push_back(it);
	}
	tranzitii.push_back(std::make_pair(std::make_pair(contor, '~'), afd1.GetStareInitiala()));
	tranzitii.push_back(std::make_pair(std::make_pair(contor, '~'), afd2.GetStareInitiala()));

	tranzitii.push_back(std::make_pair(std::make_pair(*(afd1.GetStariFinale().begin()), '~'), contor + 1));
	tranzitii.push_back(std::make_pair(std::make_pair(*(afd2.GetStariFinale().begin()), '~'), contor + 1));

	result.SetTranzitii(tranzitii);
	result.SetStareInitiala(contor);

	std::unordered_set<char> stariFinale;
	stariFinale.insert(contor + 1);
	result.SetStariFinale(stariFinale);

	std::unordered_set<char> stari;
	for (auto& it : afd1.GetStari()) {
		stari.insert(it);
	}
	for (auto& it : afd2.GetStari()) {
		stari.insert(it);
	}
	stari.insert(contor);
	stari.insert(contor + 1);
	result.SetStari(stari);

	std::unordered_set<char> alfabet;
	for (auto& it : afd1.GetAlfabet()) {
		alfabet.insert(it);
	}
	for (auto& it : afd2.GetAlfabet()) {
		alfabet.insert(it);
	}
	result.SetAlfabet(alfabet);
	return result;
}
AFD CreateAFDFromPolishForm(std::vector<std::string> polishForm) {
	std::stack<AFD> AFDstack;
	char contor = 'A';
	for (auto& it : polishForm) {
		if (it == ".") {
			AFD afd1 = AFDstack.top();
			AFDstack.pop();
			AFD afd2 = AFDstack.top();
			AFDstack.pop();
			AFD result = Concatenare(afd1, afd2);
			AFDstack.push(result);
		}
		else if (it == "|") {
			AFD afd1 = AFDstack.top();
			AFDstack.pop();
			AFD afd2 = AFDstack.top();
			AFDstack.pop();
			AFD result = Parallel(afd1, afd2, contor);
			AFDstack.push(result);

			contor += 2;
		}
		else if (it == "*") {
			AFD afd1 = AFDstack.top();
			AFDstack.pop();
			afd1.inchidereKleene(contor);
			AFDstack.push(afd1);

			contor += 2;
		}
		else if (it == "") {
			break;
		}
		else {
			char symbol = it[0];
			AFD result = createAFD(symbol, contor);
			AFDstack.push(result);

			contor += 2;
		}
	}
	return AFDstack.top();
}

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
		AFD result = CreateAFDFromPolishForm(fp);

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
		std::cout << "The grammar is not valid or IDC." << std::endl;
		return 0;
	}
	

}

float calcul_forma_poloneza(std::vector<std::string> fp)
{
	std::stack<float> num;
	//o sa vina un stack de automate presupun

	for (std::string element : fp)
	{
		if (isalnum(element[0]) != 0)
		{
			float val = std::stof(element);
			num.push(val);
		}
		else
		{
			float y = num.top();
			num.pop();
			float x = num.top();
			num.pop();
			float rez = calcul(x, y, element[0]);
			num.push(rez);
		}
	}
	return num.top();
}

float calcul(float x, float y, char element)
{
	if (element == '-')
		return x - y;
	if (element == '+')
		return x + y;
	if (element == '/')
		return x / y;
	if (element == '*')
		return x * y;
	if (element == '^')
		return pow(x, y);
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
