#include "AFN.h"

std::unordered_set<char> AFN::EpsilonClosure(std::unordered_set<char> states)
{
	std::unordered_set<char> closure = states;
	std::vector<char> queue(states.begin(), states.end());
	int start = 0;

	while (start < queue.size())
	{
		char state = queue[start];
		start++;

		for (auto transition : m_tranzitii)
		{
			if (transition.first.first == state && transition.first.second == m_nullcharacter)
			{
				char next = transition.second;
				if (closure.count(next) == 0)
				{
					closure.insert(next);
					queue.push_back(next);
				}
			}
		}
	}
	return closure;
}

std::unordered_set<char> AFN::GetTransition(char state, char symbol)
{
	std::unordered_set<char> nextStates;
	for (auto transition : m_tranzitii)
	{
		if (transition.first.first == state && transition.first.second == symbol)
		{
			nextStates.insert(transition.second);
		}
	}
	return nextStates;
}

bool AFN::IsFinalState(char state)
{
	return m_stariFinale.count(state) > 0;
}

void AFN::inchidereKleene(char contor)
{
	m_tranzitii.push_back(std::make_pair(std::make_pair(*m_stariFinale.begin(), '~'),m_stareInitiala));
	m_tranzitii.push_back(std::make_pair(std::make_pair(contor, '~'), m_stareInitiala));
	m_tranzitii.push_back(std::make_pair(std::make_pair(*m_stariFinale.begin(), '~'), contor+1));
	m_tranzitii.push_back(std::make_pair(std::make_pair(contor, '~'), contor + 1));
	m_stareInitiala = contor;
	m_stariFinale.clear();
	m_stariFinale.insert(contor + 1);

	m_stari.insert(contor);
	m_stari.insert(contor + 1);
}

void AFN::SetStari(const std::unordered_set<char>& stari)
{
	m_stari = stari;
}

void AFN::SetAlfabet(const std::unordered_set<char>& alfabet)
{
	m_alfabet = alfabet;
}

void AFN::SetTranzitii(const std::vector<std::pair<std::pair<char, char>, char>>& tranzitii)
{
	m_tranzitii = tranzitii;
}

void AFN::SetStareInitiala(const char& stareInitiala)
{
	m_stareInitiala = stareInitiala;
}

void AFN::SetStariFinale(const std::unordered_set<char>& stariFinale)
{
	m_stariFinale = stariFinale;
}

std::unordered_set<char> AFN::GetStari() const
{
	return m_stari;
}

std::unordered_set<char> AFN::GetAlfabet() const
{
	return m_alfabet;
}

std::vector<std::pair<std::pair<char, char>, char>> AFN::GetTranzitii() const
{
	return m_tranzitii;
}

char AFN::GetStareInitiala() const
{
	return m_stareInitiala;
}

std::unordered_set<char> AFN::GetStariFinale() const
{
	return m_stariFinale;
}

std::ostream& operator<<(std::ostream& out, const AFN& finiteAutomaton)
{
	out << '(';
	out << '{';
	for (auto& it : finiteAutomaton.m_stari) {
		out << it << ',';
	}
	out << "\b}, ";
	out << '{';
	for (auto& it : finiteAutomaton.m_alfabet) {
		out << it << ',';
	}
	out << "\b}, ";
	

	out << finiteAutomaton.m_stareInitiala;
	out << ')';
	out << std::endl;
	int index = 1;
	for (auto& it : finiteAutomaton.m_tranzitii) {
		out << "(" << index << ") ";
		out << '(' << it.first.first << ',' << it.first.second << ") -> (" << it.second;
		out << std::endl;
	}

	return out;
}
