#include "AFD.h"

<<<<<<< Updated upstream
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
=======
void AFD::TransformToAFD(AFN& afn)
{
    // Get the epsilon closure of the initial state of the AFN
    std::unordered_set<char> epsilonClosure = afn.EpsilonClosure(afn.GetStareInitiala());

    // Set the initial state of the AFD to be the epsilon closure
    m_stareInitiala = epsilonClosure;

    // Add the initial state to the statesQueue and the set of states of the AFD
    std::unordered_set<std::unordered_set<char>> statesQueue;
    statesQueue.insert(epsilonClosure);
    m_stari.insert(epsilonClosure);

    while (!statesQueue.empty())
    {
        // Get the next set of states to be processed
        std::unordered_set<char> currentStates = *statesQueue.begin();
        statesQueue.erase(statesQueue.begin());

        // For each input symbol in the alphabet
        for (auto c : afn.GetAlfabet())
        {
            std::unordered_set<char> nextStates;
            for (auto state : currentStates)
            {
                auto transition = afn.GetTransition(state, c);
                for (auto next : transition)
                {
                    nextStates.insert(next);
                }
            }
            // get the epsilon closure for each state
            nextStates = afn.EpsilonClosure(nextStates);
            if (nextStates.size() == 0) continue;
            // add the resulting set of states to the set of states of the AFD
            m_stari.insert(nextStates);

            // add the resulting set of states to the statesQueue if it's not already in the queue
            if (statesQueue.find(nextStates) == statesQueue.end())
            {
                statesQueue.insert(nextStates);
            }
            // add a transition from the current set of states to the resulting set of states using the input symbol c
            m_tranzitii.push_back({ { currentStates, c }, nextStates });
        }
    }
    // Set the final states of the AFD to be the sets of states that contain a final state of the AFN
    for (auto set : m_stari)
    {
        for (auto s : set)
        {
            if (afn.IsFinalState(s))
            {
                m_stariFinale.insert(set);
                break;
            }
        }
    }
    m_alfabet = afn.GetAlfabet();
>>>>>>> Stashed changes
}
