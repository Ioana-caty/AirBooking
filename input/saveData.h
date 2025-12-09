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

	// acces prin friend
	const std::vector<Zbor>& zboruri = companie.flotaZboruri;

	fout << zboruri.size() << "\n";

	for (const auto& zbor : zboruri) {
		// acces direct la membrii privati prin friend
		fout << zbor.numarZbor << " "
			 << zbor.destinatie << " "
			 << zbor.poarta << " "
			 << zbor.capacitateMaxima << "\n";

		const std::vector<Pasager>& pasageri = zbor.getPasageri();

		fout << pasageri.size() << "\n";

		for (const auto& pasager : pasageri) {
			fout << pasager.nume << "\n";
			fout << pasager.email << "\n";

			const Bilet* bilet = pasager.bilet;
			if (bilet != nullptr) {
				fout    << bilet->loc << " "
						<< bilet->getTipClasa() << " "
						<< bilet->pretBaza << " "
						<< bilet->discountProcent << "\n";
			} else {
				fout << "EROARE";
			}
		}
	}

	fout.close();
	mesajSucces("Datele au fost salvate in fisierul '" + nameFile + "'");
	mesajInfo("S-au salvat " + std::to_string(zboruri.size()) + " zboruri.");
}
