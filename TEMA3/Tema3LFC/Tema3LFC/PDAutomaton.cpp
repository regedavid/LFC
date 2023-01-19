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
	ClearStiva();
	m_stiva.push(m_stareInitialaPD);
	char currentState = m_stareInitiala;
	return Checkwordrec(currentState, word, m_stiva);
}

bool PDAutomaton::Checkwordrec(char currentState, std::string word, std::stack<char> m_stiva)
{
	bool foundTransition = false;
	for (int j = 0; j < m_tranzitii.size(); j++) 
	{
		if (currentState == std::get<0>(m_tranzitii[j].first) && word[0] == std::get<1>(m_tranzitii[j].first) && m_stiva.top() == std::get<2>(m_tranzitii[j].first))
		{
			foundTransition = true;
			m_stiva.pop();
			if (m_tranzitii[j].second.second[0] != '~')
			{
				for (int k = m_tranzitii[j].second.second.size() - 1; k >= 0; k--)
				{
					m_stiva.push(m_tranzitii[j].second.second[k]);
				}
			}
			currentState = m_tranzitii[j].second.first;
			std::string new_word = word.substr(1, word.size() - 1);
			if (m_stiva.size() != 0)
			{
				if (Checkwordrec(currentState, new_word, m_stiva) == 0)
				{
					foundTransition = false;
					for (int k = 0; k < m_tranzitii[j].second.second.size(); k++)
						m_stiva.pop();
					m_stiva.push(std::get<2>(m_tranzitii[j].first));
					currentState = std::get<0>(m_tranzitii[j].first);
				}
				else
				{
					return 1;
				}
			}
			else 
				if (new_word.size() == 1)
			    {
				    return 0;
			    }
			else
				return 1;
		}
	}
	if (foundTransition == false)
	{
		return 0;
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

void PDAutomaton::ClearStiva()
{
	while (m_stiva.empty() == false)
		m_stiva.pop();
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
