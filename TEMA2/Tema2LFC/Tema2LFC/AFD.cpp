#include "AFD.h"


void AFD::makeAFD(AFN& afn)
{
	std::vector<std::unordered_set<char>> stariArray; //vector de inchideri lambda
	std::queue<std::pair<char, int>> coadaStari;
	std::unordered_set<char> setStari;
	m_alfabet = afn.GetAlfabet();

	afn.getLambdaClosures(afn.GetStareInitiala(), setStari);

	stariArray.push_back(setStari);
	coadaStari.push(std::make_pair('q',0));
	m_stari.insert(std::make_pair('q', 0));
	m_stareInitiala = std::make_pair('q', 0);
	
	while (!coadaStari.empty()) {
		std::pair<char, int> stareCurenta = coadaStari.front();
		for (auto& simbol : afn.GetAlfabet()) {
			setStari.clear();
			std::unordered_set<char> stariRezultate;
			for (auto& stare : stariArray[stareCurenta.second]) {

				for (auto& tranzitie : afn.GetTranzitii()) {
					if (tranzitie.first.first == stare && tranzitie.first.second == simbol) {
						stariRezultate.insert(tranzitie.second);
					}
				}
			}
			if (!stariRezultate.empty()) {
				for (auto& rezultat : stariRezultate) {
					afn.getLambdaClosures(rezultat, setStari);
				}

				auto iterator = std::find(stariArray.begin(), stariArray.end(), setStari);
				if (iterator == stariArray.end()) {
					stariArray.push_back(setStari);
					coadaStari.push({ 'q',stariArray.size() - 1 });
					m_stari.insert({ 'q', stariArray.size() - 1 });

					m_tranzitii.push_back({ stareCurenta, simbol, {'q',stariArray.size() - 1} });
				}
				else {
					std::pair<char, int> stare = std::make_pair('q', iterator - stariArray.begin());
					m_tranzitii.push_back({ stareCurenta, simbol, stare });
				}
			}
		}
		coadaStari.pop();
	}
	char stareFinala = *(afn.GetStariFinale().begin());
	
	for (int index = 0; index < stariArray.size(); index++) {
		if (stariArray[index].find(stareFinala) != stariArray[index].end()) {
			m_stariFinale.insert({ 'q',index });
		}
	}
}

bool AFD::IsDeterministic()
{
	std::map<char, std::vector<std::pair<char, int>>> tabela = makeMap();
	for (const auto& elem : tabela)
	{
		if (elem.second.size() > 1)
			return false;
	}
	return true;
}

bool AFD::VerifyAutomaton()
{
	for (const auto& tranzitie : m_tranzitii)
	{
		std::pair<char, char> stare, rez; char simb;
		stare = std::get<0>(tranzitie);
		simb = std::get<1>(tranzitie);
		rez = std::get<2>(tranzitie);
		int count = 0, count2 = 0;
		for (const auto& listaStari : m_stari)
		{
			if (listaStari.first != stare.first && listaStari.second != stare.second)
				count++;
			if (listaStari.first != rez.first && listaStari.second != rez.second)
				count2++;
		}
		if (count == m_stari.size() || count2 == m_stari.size())
			return false;

		if (m_alfabet.find(simb) == m_alfabet.end())
			return false;
	}
	return true;
}

std::map<char, std::vector<std::pair<char, int>>> AFD::makeMap()
{
	std::map<char, std::vector<std::pair<char, int>>> tabela;
	std::pair<char, int> stare, rez;
	char simb;

	for (const auto& tranzitie : m_tranzitii)
	{
		stare = std::get<0>(tranzitie);
		simb = std::get<1>(tranzitie);
		rez = std::get<2>(tranzitie);
		tabela[stare.first + stare.second + simb].push_back(rez);
	}

	return tabela;
}

bool AFD::checkWord(std::string word)
{
	std::pair<char, int> stareCurenta = { 'q',0 };
	int stCurenta = 0;
	for (auto& character : word) {
		bool foundTransition = false;
		for (auto& tranzitie : m_tranzitii) {
			if (std::get<0>(tranzitie).second == stCurenta && std::get<1>(tranzitie) == character) {
				foundTransition = true;
				stCurenta = std::get<2>(tranzitie).second;
				break;
			}
		}
		if (!foundTransition) {
			return false;
		}
	}
	if (m_stariFinale.find({ 'q',stCurenta }) != m_stariFinale.end()) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, const AFD& finiteAutomaton)
{
	out << '(';
	out << '{';
	for (auto& it : finiteAutomaton.m_stari) {
		out << it.first<<it.second<<",";
	}
	out << "\b}, ";
	out << '{';
	for (auto& it : finiteAutomaton.m_alfabet) {
		out << it << ',';
	}
	out << "\b}, ";

	out << "Tanz, ";

	out << finiteAutomaton.m_stareInitiala.first<<finiteAutomaton.m_stareInitiala.second;
	out << ", ";
	out << "{";
	for (auto& it : finiteAutomaton.m_stariFinale) {
		out << it.first << it.second << ",";
	}
	out << "\b} ";
	out << ')';

	out << std::endl;
	out << "Tranz="<< std::endl;
	int index = 1;
	for (auto& it : finiteAutomaton.m_tranzitii) {
		out << "(" << index << ") ";
		out << '(' << std::get<0>(it).first<<std::get<0>(it).second << ',' << std::get<1>(it) << ") -> " << std::get<2>(it).first << std::get<2>(it).second;
		out << std::endl;
		index++;
	}

	return out;
}
