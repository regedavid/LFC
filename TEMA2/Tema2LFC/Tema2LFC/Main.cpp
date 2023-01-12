#include "formaPoloneza.h"
#include <regex>

// calculele tre sa faca toate nebuniile cu automatonul in fct de forma poloneza
float calcul_forma_poloneza(std::vector<std::string> fp);
float calcul(float x, float y, char element);

// sa verificat si moficat expresia data sa fie calumea
int verificare_expresie(std::string expresie);

int main()
{
	std::ifstream in("date.in");
	std::string expresie;
	getline(in, expresie);
	if (verificare_expresie(expresie) == 1)
		std::cout << "ok" << std::endl;
	else
		std::cout << "nu ok" << std::endl;
	formaPoloneza f;
	std::vector<std::string>fp = f(expresie);
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