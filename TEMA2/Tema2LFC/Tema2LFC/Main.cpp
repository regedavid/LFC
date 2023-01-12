#include "formaPoloneza.h"

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
	char op_cu_paranteze[20] = { " .()^*/-+" }, prev = ' ';
	char op_fara[20] = { "^*-+" };
	std::stack<char>paranteze;
	for (char c : expresie)
	{
		if (isalnum(c) == 0 && strchr(op_cu_paranteze, c) == 0)
		{
			std::cerr << "Caractere nepermise" << std::endl;
			return 0;
		}

		if (strchr(op_fara, c) != 0 && strchr(op_fara, prev) != 0)
		{
			std::cerr << "Prea multi operatori";
			return 0;
		}
		else
			if (strchr(op_fara, c) != 0)
				prev = c;
		if (isalnum(c) != 0)
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
				std::cerr << "Parantezare gresita";
				return 0;
			}
	}
	if (paranteze.size() != 0)
	{
		std::cerr << "Parantezare gresita";
		return 0;
	}
	else
		return 1;
}