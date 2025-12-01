#pragma once
#include "../headers/Zbor.h"
#include "../headers/Pasager.h"
#include "../headers/Bilet.h"
#include "../headers/CompanieAeriana.h"
#include <fstream>
#include <iostream>
#include <vector>

void saveData(const CompanieAeriana& companie, const std::string& nameFile) {
	std::ofstream fout(nameFile);

	if (!fout.is_open()) {
		std::cerr << "EROARE: NU s-a putut deschide fisierul '" << nameFile << "' pentru scriere!";
		return;
	}

	const std::vector<Zbor>& zboruri = companie.getZboruri();

	fout << zboruri.size() << "\n";

	for (const auto& zbor : zboruri) {
		fout << zbor.getNumarZbor() << " "
			 << zbor.getDestinatie() << " "
			 << zbor.getPoarta() << " "
			 << zbor.getCapacitateMaxima() << "\n";

		const std::vector<Pasager>& pasageri = zbor.getPasageri();

		fout << pasageri.size() << "\n";

		for (const auto& pasager : pasageri) {
			fout << pasager.getNume() << "\n";
			fout << pasager.getEmail() << "\n";

			const Bilet* bilet = pasager.getBilet();
			if (bilet != nullptr) {
				fout	<< bilet->getLoc() << " "
						<< bilet->getTipClasa() << " "
						<< bilet->getPretBaza() << " "
						<< bilet->getDiscountProcent() << "\n";
			} else {
				fout << "EROARE";
			}
		}
	}

	fout.close();
	std::cout << "\n[SUCCES] Datele au fost salavte in fisierul '" << nameFile << "'\n";
	std::cout << "[INFO] S-au salvat " << zboruri.size() << " zboruri.\n";
}
