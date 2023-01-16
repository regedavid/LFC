#include "Grammar.h"

bool Grammar::verifyRule1()
{
	bool areInterposed = false;
	for (auto& it : m_neterminale) {
		if (m_terminale.find(it) != m_terminale.end()) {
			areInterposed = true;
		}
	}
	return !areInterposed;
}

bool Grammar::verifyRule2()
{
	if (m_neterminale.find(m_startSymbol) == m_neterminale.end()) {
		return false;
	}
	return true;
}

bool Grammar::verifyRule3()
{
	bool foundNeterminalInAll = true;
	for (auto& it : m_productii) {
		bool foundNeterminal = false;
		for (auto& it2 : it.first) {
			if (m_neterminale.find(it2) != m_neterminale.end()) {
				foundNeterminal = true;
			}
		}
		if (foundNeterminal == false) {
			foundNeterminalInAll = false;
		}
	}
	return foundNeterminalInAll;
}

bool Grammar::verifyRule4()
{
	bool hasStartSymb = false;
	for (auto& it : m_productii) {
		if (it.first.size() == 1 && it.first[0] == 'S') {
			hasStartSymb = true;
		}
	}
	return hasStartSymb;
}

bool Grammar::verifyRule5()
{
	bool isProductionValid = true;
	for (auto& it : m_productii) {
		bool isCharFromVnOrVt = true;
		for (auto& character : it.first) {
			bool containsVn = false;
			bool containsVt = false;
			if (m_neterminale.find(character) != m_neterminale.end()) {
				containsVn = true;
			}
			if (m_terminale.find(character) != m_terminale.end()) {
				containsVt = true;
			}
			if (!(containsVn || containsVt)) {
				return false;
			}
		}

		for (auto& character : it.second) {
			bool containsVn = false;
			bool containsVt = false;
			if (m_neterminale.find(character) != m_neterminale.end()) {
				containsVn = true;
			}
			if (m_terminale.find(character) != m_terminale.end()) {
				containsVt = true;
			}
			if (!(containsVn || containsVt)) {
				return false;
			}
		}
		if (!isCharFromVnOrVt) {
			isProductionValid = false;
		}

	}
	return true;
}

Grammar& Grammar::operator=(const Grammar& other)
{
	m_neterminale = other.m_neterminale;
	m_terminale = other.m_terminale;
	m_startSymbol = other.m_startSymbol;
	m_productii = other.m_productii;
	return *this;
}

void Grammar::readGrammar(std::ifstream& inputfile)
{
	int nrTerminale, nrNeterminale, nrProductii;
	char terminal, neterminal;
	std::string productie1;
	std::string productie2;
	inputfile >> m_startSymbol;
	inputfile >> nrNeterminale;
	for (int i = 0; i < nrNeterminale; i++) {
		inputfile >> neterminal;
		m_neterminale.insert(neterminal);
	}
	inputfile >> nrTerminale;
	for (int i = 0; i < nrTerminale; i++) {
		inputfile >> terminal;
		m_terminale.insert(terminal);
	}
	inputfile >> nrProductii;
	for (int i = 0; i < nrProductii; i++) {
		inputfile >> productie1 >> productie2;
		m_productii.push_back(std::make_pair(productie1, productie2));
	}
	m_neterminale.insert(m_startSymbol);
}

bool Grammar::verifyGrammar()
{
	if (verifyRule1() && verifyRule2() && verifyRule3() && verifyRule4() && verifyRule5()) {
		return true;
	}
	else return false;
}

std::string Grammar::generateWord()
{
	std::string word;
	//std::vector<bool> productiiPosibile(m_productii.size(),false);
	std::vector<std::pair<std::string, std::string>> productiiPosibile;
	word += m_startSymbol;
	//vector de productii care se pot face pe cuvant, care se reseteaza la fiecare productie folosita
	bool isProductionFound = true;
	while (isProductionFound) {
		isProductionFound = false;
		productiiPosibile.clear();
		for (auto& it : m_productii) {
			if (word.find(it.first) != -1) {
				isProductionFound = true;
				productiiPosibile.push_back(std::make_pair(it.first, it.second));
				//auto iterator = find(m_productii.begin(), m_productii.end(), it);
				//int pozitie = iterator - m_productii.begin();
				//productiiPosibile[pozitie] = true;
			}
		}
		if (isProductionFound) {
			std::random_device rd;
			std::mt19937 eng(rd());
			std::uniform_int_distribution<> distr(0, productiiPosibile.size() - 1);
			int indexProductieAleasa = distr(eng);
			std::string productieAleasaStang = productiiPosibile[indexProductieAleasa].first;
			std::string productieAleasaDrept = productiiPosibile[indexProductieAleasa].second;
			std::vector<size_t> pozitieProductie;
			size_t found = word.find(productieAleasaStang);
			if (found != std::string::npos) {
				pozitieProductie.push_back(found);
			}
			while (found != std::string::npos) {
				found = word.find(productieAleasaStang, found + productieAleasaStang.length());
				if (found != std::string::npos) {
					pozitieProductie.push_back(found);
				}
			}
			std::random_device rd2;
			std::mt19937 eng2(rd2());
			std::uniform_int_distribution<> distr2(0, pozitieProductie.size() - 1);
			int indexPozitieAleasa = distr2(eng2);
			//int indexPozitieAleasa = rand() % pozitieProductie.size();
			size_t PozitieAleasa = pozitieProductie[indexPozitieAleasa];
			word.replace(PozitieAleasa, productieAleasaStang.length(), productieAleasaDrept);
		}
	}
	return word;
}

bool Grammar::isRegulated()
{
	for (auto& it : m_productii) {
		if (it.first.size() != 1) {
			return false;
		}
		if (m_neterminale.find(it.first[0]) == m_neterminale.end()) {
			return false;
		}
		if (it.second.size() > 2) {
			return false;
		}
		if (it.second.size() == 1 && m_terminale.find(it.second[0]) == m_terminale.end()) {
			return false;
		}
		if (it.second.size() == 2) {
			if (m_terminale.find(it.second[0]) == m_terminale.end()) {
				return false;
			}
			if (m_neterminale.find(it.second[1]) == m_neterminale.end()) {
				return false;
			}
		}
	}
	return true;
}

bool Grammar::isIDC() {
	for (auto& it : m_productii) {
		if (it.first.size() != 1) {
			return false;
		}
		if (m_neterminale.find(it.first[0]) == m_neterminale.end()) {
			return false;
		}
		if (m_terminale.find(it.first[0]) != m_terminale.end()) {
			return false;
		}
		for (auto& it2 : it.second) {
			if (m_neterminale.find(it2) == m_neterminale.end() && m_terminale.find(it2) == m_terminale.end()) {
				return false;
			}
		}
	}
	return true;
}

void Grammar::simplify1()
{
	std::unordered_set<char> stari;
	for (auto& it : m_productii) {
		if (it.second.size() == 1) {
			if (m_terminale.find(it.second[0]) != m_terminale.end()) {
				stari.insert(it.first[0]);
			}
		}
	}
	while (true) {
		int stariSize = stari.size();
		for (auto& it : m_productii) {
			bool fromStariOrTerminale=true;
			for (auto& character : it.second) {
				
				if (m_terminale.find(character) == m_terminale.end() && stari.find(character) == stari.end()) {
					fromStariOrTerminale = false;
				}
			}
			if (fromStariOrTerminale == true) {
				stari.insert(it.first[0]);
			}
		}
		if (stari.size() == stariSize) {
			break;
		}
	}
	std::vector<size_t> pozVector;
	for (auto it = m_productii.begin(); it != m_productii.end(); it++) {
		if (stari.find((*it).first[0]) == stari.end()) {
			//m_productii.erase(it);
			pozVector.push_back(it-m_productii.begin());
		}
		else {
			for (auto& character : (*it).second) {
				if (stari.find(character) == stari.end() && m_neterminale.find(character) != m_neterminale.end()) {
					//m_productii.erase(it);
					pozVector.push_back(it - m_productii.begin());
				}
			}
		}
	}
	size_t index = 0;
	for (auto& it : pozVector) {
		m_productii.erase(m_productii.begin()+(it));
		for (int i=index; i < pozVector.size(); i++) {
			pozVector[i]--;
		}
		index++;
	}
	m_neterminale = stari;
}

void Grammar::simplify2()
{
	std::unordered_set<char> stari;
	stari.insert(m_startSymbol);
	while (true) {
		int sizeStari = stari.size();
		for (auto& it : m_productii) {
			if (stari.find(it.first[0]) != stari.end()) {
				for (auto& character : it.second) {
					if (m_neterminale.find(character) != m_neterminale.end()) {
						stari.insert(character);
					}
				}
			}
		}
		if (sizeStari == stari.size()) {
			break;
		}
	}

	std::vector<size_t> pozVector;
	for (auto it = m_productii.begin(); it != m_productii.end(); it++) {
		if (stari.find((*it).first[0]) == stari.end()) {
			//m_productii.erase(it);
			pozVector.push_back(it - m_productii.begin());
		}
		else {
			for (auto& character : (*it).second) {
				if (stari.find(character) == stari.end() && m_neterminale.find(character) != m_neterminale.end()) {
					//m_productii.erase(it);
					pozVector.push_back(it - m_productii.begin());
				}
			}
		}
	}

	size_t index = 0;
	for (auto& it : pozVector) {
		m_productii.erase(m_productii.begin() + (it));
		for (int i = index; i < pozVector.size(); i++) {
			pozVector[i]--;
		}
		index++;
	}
	m_neterminale = stari;
}

void Grammar::simplify3()
{
	std::vector<std::pair<std::string, std::string>> redenumiri;
	std::vector<size_t> pozVector;
	size_t index = 0;
	for (auto& it : m_productii) {
		if (it.second.size() == 1) {
			if (m_neterminale.find(it.second[0]) != m_neterminale.end()) {
				redenumiri.push_back(it);
				pozVector.push_back(index);
			}
		}
		index++;
	}

	size_t index2 = 0;
	for (auto& it : pozVector) {
		m_productii.erase(m_productii.begin() + (it));
		for (int i = index2; i < pozVector.size(); i++) {
			pozVector[i]--;
		}
		index2++;
	}

	for (int i = 0; i < redenumiri.size()-1; i++) {
		for (int j = i+1; j < redenumiri.size(); j++) {
			if (redenumiri[i].second == redenumiri[j].first) {
				redenumiri.push_back(std::make_pair(redenumiri[i].first, redenumiri[j].second));
			}
		}
	}

	std::vector<std::pair<std::string, std::string>> additions;
	for (auto& it : m_productii) {
		for (auto& it2 : redenumiri) {
			if (it2.second == it.first) {
				additions.push_back(std::make_pair(it2.first, it.second));
			}
		}
	}
	for (auto& it : additions) {
		m_productii.push_back(it);
	}
}

void Grammar::ChomskyNormalForm()
{
	char symbol = 'M';
	std::vector<std::pair<std::string, std::string>> additions;
	for (auto& terminal : m_terminale) {
		bool added = false;
		for (auto& productie : m_productii) {
			if (productie.second.size() > 1) {
				for (auto& character : productie.second) {
					if (terminal == character) {
						if (added == false) {
							std::string symbolString(1, symbol);
							std::string characterString(1, character);
							additions.push_back(std::make_pair(symbolString, characterString));
							added = true;
							m_neterminale.insert(symbol);
						}
						
						character = symbol;
					}
				}
			}
		}
		symbol++;
		while (symbol == m_startSymbol || m_neterminale.find(symbol) != m_neterminale.end() || m_terminale.find(symbol) != m_terminale.end()) {
			symbol++;
		}
	}

	for (auto& productie : m_productii) {
		if (productie.second.size() > 2) {
			std::string substr = productie.second.substr(1, productie.second.size() - 1);
			std::string symbolString(1, symbol);
			additions.push_back(std::make_pair(symbolString, substr));
			productie.second = productie.second[0];
			productie.second += symbol;
			m_neterminale.insert(symbol);

			symbol++;
			while (symbol == m_startSymbol || m_neterminale.find(symbol) != m_neterminale.end() || m_terminale.find(symbol) != m_terminale.end()) {
				symbol++;
			}
		}	
	}
	bool changed = true;
	while (changed) {
		changed = false;
		for (size_t index=0; index < additions.size(); index++) {
			
			if (additions[index].second.size() > 2) {
				std::string substr = additions[index].second.substr(1, additions[index].second.size() - 1);
				std::string symbolString(1, symbol);
				additions[index].second = additions[index].second[0];
				additions[index].second += symbol;

				additions.push_back(std::make_pair(symbolString, substr));	
				m_neterminale.insert(symbol);
				//additions.erase(additions.begin() + index);
				//index--;

				symbol++;
				while (symbol == m_startSymbol || m_neterminale.find(symbol) != m_neterminale.end() || m_terminale.find(symbol) != m_terminale.end()) {
					symbol++;
				}
				changed = true;
			}		
		}
	}
	for (auto& it : additions) {
		m_productii.push_back(it);
	}
}

void Grammar::GreibachNormalForm()
{
	char symbol = getMaxNeterminal() + 1;
	std::unordered_set<char> addedSymbols;
	std::unordered_set<char> step1Neterminale;
	for (auto& it : m_neterminale) {
		if (it != m_startSymbol)
			step1Neterminale.insert(it);
	}
	//pas 1
	for (int index = 0; index < m_productii.size(); index++) {
		if (step1Neterminale.find(m_productii[index].first[0]) != step1Neterminale.end() && m_productii[index].second.size() > 1 && (m_productii[index].first[0] >= m_productii[index].second[0] || m_productii[index].second[0] == m_startSymbol)) { //daca nu e in FNG sau e cu S la inceput si face parte din step1Neterminale

			if (m_productii[index].first[0] == m_productii[index].second[0]) { //recursivitate stanga se aplica LEMA2
				for (int index2 = index; index2 < m_productii.size(); index2++) { //pentru toate productiile cu acelasi simbol in stanga
					if (m_productii[index2].first[0] == m_productii[index2].second[0] && m_productii[index].first[0] == m_productii[index2].first[0]) {
						bool applicable = false;
						std::string terminal;
						for (auto& it : m_productii) {
							if (it.first[0] == m_productii[index2].first[0] && it.second.size() == 1) {
								applicable = true;
								terminal = it.second[0];
								break;
							}
						}
						if (applicable == true) {
							terminal += symbol;
							std::string symbolString(1, symbol);
							std::string substr = m_productii[index2].second.substr(1, m_productii[index2].second.size() - 1);
							m_productii.push_back(std::make_pair(m_productii[index2].first, terminal));
							m_productii.push_back(std::make_pair(symbolString, substr + symbol));
							m_productii.push_back(std::make_pair(symbolString, substr));


						}
					}
				}
				addedSymbols.insert(symbol);
				symbol++;
				m_productii.erase(m_productii.begin() + index);
				index--;
			}
			else {//se aplica LEMA 1
				std::string substr = m_productii[index].second.substr(1, m_productii[index].second.size() - 1);
				char changed = m_productii[index].second[0];
				std::string left(1, m_productii[index].first[0]);
				m_productii.erase(m_productii.begin() + index);
				index--;

				for (auto& it : m_productii) {
					if (it.first[0] == changed) {
						std::string right = it.second;
						right += substr;

						m_productii.push_back(std::make_pair(left, right));
					}
				}

			}

		}
	}
	//pas2
	for (int index = 0; index < m_productii.size(); index++) {
		if ((addedSymbols.find(m_productii[index].first[0]) != addedSymbols.end() || m_productii[index].first[0] == m_startSymbol) && m_terminale.find(m_productii[index].second[0]) == m_terminale.end()) {
			std::string substr = m_productii[index].second.substr(1, m_productii[index].second.size() - 1);
			char changed = m_productii[index].second[0];
			std::string left(1, m_productii[index].first[0]);
			m_productii.erase(m_productii.begin() + index);
			index--;

			for (auto& it : m_productii) {
				if (it.first[0] == changed) {
					std::string right = it.second;
					right += substr;

					m_productii.push_back(std::make_pair(left, right));
				}
			}
		}
	}
}

const std::unordered_set<char> Grammar::GetNeterminale() const
{
	return m_neterminale;
}

const char Grammar::GetStartSymbol() const
{
	return m_startSymbol;
}

const std::vector<std::pair<std::string, std::string>> Grammar::GetProductii() const
{
	return m_productii;
}

void Grammar::sortGrammar()
{
	for (int i = 0; i < m_productii.size()-1; i++) {
		for (int j = i + 1; j < m_productii.size(); j++) {
			if (m_productii[i] > m_productii[j] && m_productii[i].first[0] != m_startSymbol) {
				std::swap(m_productii[i], m_productii[j]);
			}
		}
	}
}

char Grammar::getMaxNeterminal()
{
	char max = 0;
	for (auto& it : m_neterminale) {
		if (it > max) {
			if(it!=m_startSymbol)
			max = it;
		}
	}
	return max;
}

const std::unordered_set<char> Grammar::GetTerminale() const
{
	return m_terminale;
}

bool operator<(const std::pair<std::string, std::string>& productie1, const std::pair<std::string, std::string>& productie2)
{
	return productie1.first[0] < productie2.first[0];
}

std::ostream& operator<<(std::ostream& out, const Grammar& grammar)
{
	out << '(';
	out << '{';
	std::unordered_set<char>::iterator itr;
	for (itr = grammar.m_neterminale.begin();
		itr != grammar.m_neterminale.end(); itr++)
	{
		out << *itr << ',';
	}
	out << "\b}, ";
	out << '{';
	std::unordered_set<char>::iterator itr2;
	for (itr2 = grammar.m_terminale.begin();
		itr2 != grammar.m_terminale.end(); itr2++)
	{
		out << *itr2 << ',';
	}
	out << "\b}, ";
	out << grammar.m_startSymbol << ", " << 'P';
	out << ')' << std::endl;
	int prodnumber = 1;
	for (auto& it : grammar.m_productii) {
		out << '(' << prodnumber << ") " << it.first << " -> " << it.second << std::endl;
		prodnumber++;
	}
	return out;
}