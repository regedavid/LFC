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
