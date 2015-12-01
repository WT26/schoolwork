// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Harjoitustehtava 4
// 246479 joel.alanko@student.tut.fi (15h)


#include "paivyri.hh"
#include "kayttoliittyma.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <sstream>
#include <string>

// Alkukommentti: Hyvin yksinkertainen ohjelma, jonka avulla voidaan
// yllapitaa yksinkertaista kalenteria/paivyria. Ohjelma voi tarvittaessa
// lukea, tallettaa, tulostaa, nayttaa ja poistaa tapahtumia tietyille
// paivamaarille. Ohjelmassa ei ole kaytetty lainkaan stl sailioita, vaan
// on luotu itse tarvittavat rakenteet, Kirjasto vastaamaan map-rakennetta
// ja Lista vastaamaan vector/deque rakennetta.

using namespace std;

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
