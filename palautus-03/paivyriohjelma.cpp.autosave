// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Harjoitustehtava 3
// 246479 joel.alanko@student.tut.fi (10h)


#include "paivyri.hh"
#include "kayttoliittyma.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Alkukommentti: Hyvin yksinkertainen ohjelma, jonka avulla voidaan
// yllapitaa yksinkertaista kalenteria/paivyria. Ohjelma voi tarvittaessa
// lukea, tallettaa, tulostaa, nayttaa ja poistaa tapahtumia tietyille
// paivamaarille.

int main() {
    string paivyritiedoston_nimi;
    cout << "Syota paivyritiedoston nimi: ";
    getline(cin, paivyritiedoston_nimi);

    Paivyri paivyri;

    if ( not lue_paivyritiedosto(paivyritiedoston_nimi, paivyri) ) {
        return 1;
    }

    // Luodaan kayttoliittyma.
    kayttoliittyma(paivyri);
}
