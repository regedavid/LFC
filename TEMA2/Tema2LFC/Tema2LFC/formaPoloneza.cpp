#include "formaPoloneza.h"

std::vector<std::string> formaPoloneza::operator()(std::string expresie)
{
	adaugareInmultire(expresie);
	std::vector<std::string>token = tokenizare(expresie);
	std::vector<std::string> fp = forma_poloneza(token);
	return fp;
}

std::vector<std::string> formaPoloneza::tokenizare(std::string expresie)
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

std::vector<std::string> formaPoloneza::forma_poloneza(std::vector<std::string> token)
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

int formaPoloneza::precedenta(char element)
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

void formaPoloneza::adaugareInmultire(std::string& expresie)
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
