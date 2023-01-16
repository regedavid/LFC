#include "AFD.h"

void AFD::inchidereKleene(char contor)
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

void AFD::SetStari(const std::unordered_set<char>& stari)
{
	m_stari = stari;
}

void AFD::SetAlfabet(const std::unordered_set<char>& alfabet)
{
	m_alfabet = alfabet;
}

void AFD::SetTranzitii(const std::vector<std::pair<std::pair<char, char>, char>>& tranzitii)
{
	m_tranzitii = tranzitii;
}

void AFD::SetStareInitiala(const char& stareInitiala)
{
	m_stareInitiala = stareInitiala;
}

void AFD::SetStariFinale(const std::unordered_set<char>& stariFinale)
{
	m_stariFinale = stariFinale;
}

std::unordered_set<char> AFD::GetStari() const
{
	return m_stari;
}

std::unordered_set<char> AFD::GetAlfabet() const
{
	return m_alfabet;
}

std::vector<std::pair<std::pair<char, char>, char>> AFD::GetTranzitii() const
{
	return m_tranzitii;
}

char AFD::GetStareInitiala() const
{
	return m_stareInitiala;
}

std::unordered_set<char> AFD::GetStariFinale() const
{
	return m_stariFinale;
}

std::ostream& operator<<(std::ostream& out, const AFD& finiteAutomaton)
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
	out << ", ";
	out << *finiteAutomaton.GetStariFinale().begin();
	out << ')';

	out << std::endl;
	int index = 1;
	for (auto& it : finiteAutomaton.m_tranzitii) {
		out << "(" << index << ") ";
		out << '(' << it.first.first << ',' << it.first.second << ") -> " << it.second;
		out << std::endl;
		index++;
	}

	return out;
}
