#include "paivyri.hh"
#include "kayttoliittyma.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;





int main() {
    string paivyritiedoston_nimi;
    cout << "Syota paivyritiedoston nimi: ";
    getline(cin, paivyritiedoston_nimi);

    Paivyri paivyri;

    if ( not lue_paivyritiedosto(paivyritiedoston_nimi, paivyri) ) {
        return 1;
    }

    kayttoliittyma(paivyri);
}
