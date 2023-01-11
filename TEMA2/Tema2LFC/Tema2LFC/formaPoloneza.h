#include <iostream>
#include <stack>
#include <fstream>
#include <string>
#include <vector>

class formaPoloneza
{
public:

	std::vector<std::string> operator() (std::string input);

private:
	std::vector<std::string> tokenizare(std::string expresie);
	std::vector<std::string> forma_poloneza(std::vector<std::string> token);
	int precedenta(char element);
	void adaugareInmultire(std::string& expresie);
};