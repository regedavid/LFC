#include "PDAutomaton.h"

bool PDAutomaton::isDeterministic()
{
	for (auto& it : m_tranzitii) {
		for (auto& it2 : m_tranzitii) {
			char stare1 = std::get<0>(it.first);
			char stare2 = std::get<0>(it2.first);
			char simbol1 = std::get<1>(it.first);
			char simbol2 = std::get<1>(it2.first);
			char simbstiva1 = std::get<2>(it.first);
			char simbstiva2 = std::get<2>(it2.first);
			if (stare1 == stare2 && simbol1 == simbol2 && simbstiva1 == simbstiva2) {
				return false;
			}
		}
	}
	return true;
}

bool PDAutomaton::Checkword(std::string word)
{
	char currentState = m_stareInitiala;
	m_stiva.push(m_stareInitialaPD);
	for (int i = 0; i < word.length(); i++) {
		char currentChar = word[i];
		bool foundTransition = false;
		std::vector<int> validTransitions;
		for (int j = 0; j < m_tranzitii.size(); j++) {
			if (currentState == std::get<0>(m_tranzitii[j].first) && currentChar == std::get<1>(m_tranzitii[j].first) && m_stiva.top() == std::get<2>(m_tranzitii[j].first)) {
				validTransitions.push_back(j);
				foundTransition = true;
			}
		}
		if (!foundTransition) {
			while (!m_stiva.empty())
			{
				m_stiva.pop();
			}
			return false;
		}
		int chosenTransition = validTransitions[rand() % validTransitions.size()];
		currentState = m_tranzitii[chosenTransition].second.first;
		std::string stackString = m_tranzitii[chosenTransition].second.second;
		if (stackString[0] != '~') {
			m_stiva.pop();
		}
		for (int k = stackString.length() - 1; k >= 0; k--) {
			if (stackString[k] != '~') {
				m_stiva.push(stackString[k]);
			}
		}
	}
	if (m_stariFinale.find(currentState) != m_stariFinale.end()) {
		while (!m_stiva.empty())
		{
			m_stiva.pop();
		}
		return true;
	}
	else {
		while (!m_stiva.empty())
		{
			m_stiva.pop();
		}
		return false;
	}
}

void PDAutomaton::SetStari(const std::unordered_set<char>& stari)
{
	m_stari = stari;
}

void PDAutomaton::SetAlfabet(const std::unordered_set<char>& alfabet)
{
	m_alfabet = alfabet;
}

void PDAutomaton::SetTranzitii(const std::vector<std::pair<std::tuple<char, char, char>, std::pair<char, std::string>>>& tranzitii)
{
	m_tranzitii = tranzitii;
}

void PDAutomaton::SetStareInitiala(const char& stareInitiala)
{
	m_stareInitiala = stareInitiala;
}

void PDAutomaton::SetStariStiva(const std::unordered_set<char>& stariStiva)
{
	m_stariStiva = stariStiva;
}

void PDAutomaton::SetStareInitialaStiva(const char& stareInitialaStiva)
{
	m_stareInitialaPD = stareInitialaStiva;
}

void PDAutomaton::SetNullCharacter(const char& nullChar)
{
	m_nullcharacter = nullChar;
}

std::ostream& operator<<(std::ostream& out, const PDAutomaton& PDAutomaton)
{
	out << '(';
	out << '{';
	for (auto& it : PDAutomaton.m_stari) {
		out << it << ',';
	}
	out << "\b}, ";
	out << '{';
	for (auto& it : PDAutomaton.m_alfabet) {
		out << it << ',';
	}
	out << "\b}, ";
	out << '{';
	for (auto& it : PDAutomaton.m_stariStiva) {
		out << it << ',';
	}
	out << "\b}, ";

	out << PDAutomaton.m_stareInitiala;
	out << ", ";
	out << PDAutomaton.m_stareInitialaPD;
	out << ')';
	out << std::endl;
	int index = 1;
	for (auto& it : PDAutomaton.m_tranzitii) {
		out << "(" << index << ") ";
		out << '(' << std::get<0>(it.first) << "," << std::get<1>(it.first) << "," << std::get<2>(it.first) << ") -> (" << it.second.first << "," << it.second.second << ")";
		out << std::endl;
	}

	return out;
}
