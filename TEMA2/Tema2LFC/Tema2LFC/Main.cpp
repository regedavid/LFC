#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> tokenizare(std::string expresie);
std::vector<std::string> forma_poloneza(std::vector<std::string> token);
int precedenta(char element);
void adaugareInmultire(std::string& expresie);

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
	adaugareInmultire(expresie);

	std::vector<std::string>token = tokenizare(expresie);

	std::vector<std::string> fp = forma_poloneza(token);
	for (auto x : fp)
		std::cout << x;

}

void adaugareInmultire(std::string& expresie)
{
	char before = { '(' };
	std::string after = { ")*" };
	std::string all = { "()|*" };
	char first = expresie[0];
	char second;
	for (int i = 1; i < expresie.size(); i++)
	{
		second = expresie[i];
		if (all.find(first) == std::string::npos && all.find(second) == std::string::npos ||
			after.find(first) != std::string::npos && all.find(second) == std::string::npos ||
			all.find(first) == std::string::npos && before == second)
		{
			expresie.insert(i, ".");
			i++;
		}
		first = second;
	}
}

std::vector<std::string> tokenizare(std::string expresie)
{
	std::vector<std::string> token;
	std::string temp = "", temp2 = "";
	std::string op = { "()*|." };
	for (char c : expresie)
	{
		if (op.find(c) == std::string::npos)
		{
			temp += c;
		}
		if (op.find(c) != std::string::npos)
		{
			temp2 = c;
			if (temp != "")
				token.push_back(temp);
			token.push_back(temp2);
			temp2 = "";	temp = "";
		}
	}
	token.push_back(temp);
	return token;
}

std::vector<std::string> forma_poloneza(std::vector<std::string> token)
{
	std::stack<std::string> op;
	std::vector<std::string> fp;
	char op_calcul[10] = { "()*|." };
	for (std::string element : token)
	{
		if (isalnum(element[0]) != 0)
			fp.push_back(element);
		else
			if (element[0] == '(')
				op.push(element);
			else
				if (element[0] == ')')
				{
					while (element != "" && op.top()[0] != '(')
					{
						fp.push_back(op.top());
						op.pop();
					}
					op.pop();
				}
				else
				{
					while (op.size() != 0 && precedenta(element[0]) <= precedenta(op.top()[0]))
					{
						fp.push_back(op.top());
						op.pop();
					}
					op.push(element);
				}


	}
	while (op.size() != 0)
	{
		fp.push_back(op.top());
		op.pop();
	}
	return fp;
}

int precedenta(char element)
{
	if (element == '(')
		return 0;
	if (element == '|')
		return 1;
	if (element == '.')
		return 2;
	if (element == '*')
		return 3;
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