#include "AFD.h"

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
}

