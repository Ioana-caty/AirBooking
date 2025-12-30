#include "../headers/CheckIn.h"
#include "../headers/Bilet.h"
#include "../headers/Utils.h"

CheckIn::CheckIn(const std::string& pasager, const std::string& zbor, const std::string& loc, Bilet* bilet)
    : numePasager(toUpperCase(pasager)),
      numarZbor(toUpperCase(zbor)),
      loc(toUpperCase(loc)),
	  biletPasager(bilet) {

    mesajSucces("Check-in creat pentru " + numePasager);
}

void CheckIn::adaugaBagaj(const Bagaj& bagaj) {
    bagaje.push_back(bagaj);

	if (biletPasager != nullptr) {
		const double taxaBagaj = bagaj.getTaxaBagaj() + bagaj.getTaxaExtra();
		biletPasager->addTaxaBagaj(taxaBagaj);
		mesajSucces("Bagaj adaugat: " + bagaj.getTipString());
		mesajInfo("Pret bilet actualizat: +" + Formatare::formatareMoneda(taxaBagaj));
	}

    if (bagaj.esteSupraponderal()) {
        mesajInfo("ATENTIE: Bagaj supraponderal! Taxa extra: " +
                  Formatare::formatareMoneda(bagaj.getTaxaExtra()));
    }
}

double CheckIn::getGreutateTotala() const {
    double total = 0.0;
    for (const auto& b : bagaje) {
        total += b.getGreutate();
    }
    return total;
}

double CheckIn::getTaxeTotaleBagaje() const {
    double total = 0.0;
    for (const auto& b : bagaje) {
        total += b.getTaxaBagaj() + b.getTaxaExtra();
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const CheckIn& c) {
    os << "\n";
    UI::Linie('=', 60);
    os << "CHECK-IN PASAGER: " << c.numePasager << "\n";
    UI::Linie('=', 60);
    os << "Zbor: " << c.numarZbor << " | Loc: " << c.loc << "\n";
    os << "Numar bagaje: " << c.bagaje.size() << "\n";

    if (!c.bagaje.empty()) {
        os << "\nBagaje inregistrate:\n";
        UI::Linie('-', 60);

        for (size_t i = 0; i < c.bagaje.size(); i++) {
            os << (i+1) << ". " << c.bagaje[i].getTipString()
               << " - " << c.bagaje[i].getGreutate() << " kg";

            if (c.bagaje[i].esteSupraponderal()) {
                os << " [SUPRAPONDERAL]";
            }

            os << " - " << Formatare::formatareMoneda(
                c.bagaje[i].getTaxaBagaj() + c.bagaje[i].getTaxaExtra()) << "\n";
        }

        UI::Linie('-', 60);
        os << "Greutate totala: " << c.getGreutateTotala() << " kg\n";
        os << "Taxe totale bagaje: " << Formatare::formatareMoneda(c.getTaxeTotaleBagaje()) << "\n";
    } else {
        os << "\nNiciun bagaj inregistrat.\n";
    }

	if (c.biletPasager != nullptr) {
		os << "\n>>> PRET BILET ACTUALIZAT: "
		   << Formatare::formatareMoneda(c.biletPasager->getPretFinal()) << " <<<\n";
	}

    UI::Linie('=', 60);

    return os;
}