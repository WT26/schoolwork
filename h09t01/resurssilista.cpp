#include "resurssilista.hh"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// ---- Kuluttajalista --------------------------------------------------------

Kuluttajalista::Kuluttajalista(): alkioiden_lukumaara_{0},
                                  ensimmaisen_kuluttajan_osoite_{nullptr} {
}

int
Kuluttajalista::pituus() const {
    return alkioiden_lukumaara_;
}


void
Kuluttajalista::tulosta() const {
    if ( pituus() == 0 ) {
        cout << "  [tyhja]" << endl;
        return;
    }

    shared_ptr<Kuluttajalistan_alkio>
        tulostettavan_osoite{ ensimmaisen_kuluttajan_osoite_ };

    while ( tulostettavan_osoite != nullptr ) {
        cout << "- " << tulostettavan_osoite->kuluttajan_nimi << endl;

        tulostettavan_osoite
            = tulostettavan_osoite->seuraavan_kuluttajan_osoite;
    }
}


void
Kuluttajalista::lisaa(const string& kuluttajan_nimi) {
    shared_ptr<Kuluttajalistan_alkio>
        uuden_kuluttajan_osoite{ new Kuluttajalistan_alkio };

    uuden_kuluttajan_osoite->kuluttajan_nimi = kuluttajan_nimi;

    uuden_kuluttajan_osoite->seuraavan_kuluttajan_osoite
        = ensimmaisen_kuluttajan_osoite_;
    ensimmaisen_kuluttajan_osoite_ = uuden_kuluttajan_osoite;

    ++alkioiden_lukumaara_;
}


bool
Kuluttajalista::poista(const string& kuluttajan_nimi) {
    if ( pituus() == 0 ) {
        return false;

    } else if ( ensimmaisen_kuluttajan_osoite_->kuluttajan_nimi
                    == kuluttajan_nimi ) {
        ensimmaisen_kuluttajan_osoite_
            = ensimmaisen_kuluttajan_osoite_->seuraavan_kuluttajan_osoite;

    } else {

        shared_ptr<Kuluttajalistan_alkio>
            tutkittavan_osoite{ ensimmaisen_kuluttajan_osoite_ };

        while ( true ) {
            if ( tutkittavan_osoite->seuraavan_kuluttajan_osoite == nullptr ) {
                return false;

            } else if ( tutkittavan_osoite->seuraavan_kuluttajan_osoite
                     ->kuluttajan_nimi == kuluttajan_nimi ) {
                break;

            } else {

                tutkittavan_osoite
                    = tutkittavan_osoite->seuraavan_kuluttajan_osoite;
            }
        }

        tutkittavan_osoite->seuraavan_kuluttajan_osoite
            = tutkittavan_osoite->seuraavan_kuluttajan_osoite
                  ->seuraavan_kuluttajan_osoite;
    }

    --alkioiden_lukumaara_;

    return true;
}

// ---- Resurssilista ---------------------------------------------------------

Resurssilista::Resurssilista(const vector<string>& resurssien_nimet) {

    // Lisätään resurssien_nimet-parametrin sisältämät resurssit
    // listaan, joka vastaa tehtävänannon vaakasuuntaista listaa
    // opersk1, opersk2, ...).
}


void
Resurssilista::tulosta() const {

    // Toiminnallisuus selvä(?)
}


string
Resurssilista::lisaa(const string& kuluttajan_nimi) {

    // Etsitään tällä hetkellä lyhin alilista (pystysuuntainen lista)
    // ja lisätään kuluttajan_nimi kyseiselle listalle.
}


bool
Resurssilista::poista(const string& kuluttajan_nimi,
                      const string& resurssin_nimi) {

    // Poistetaan kuluttajan_nimi resurssista resurssin_nimi.
}
