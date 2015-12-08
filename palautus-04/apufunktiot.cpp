#include "apufunktiot.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "lista.hh"

// Apufunktioita, joita hyodynnetaan muissa moduuleissa.

using namespace std;


// Muuttaa stringin unsignediksi.
bool string_unsignediksi(const string& mjono, unsigned int& tulos) {
    const string NUMEROMERKIT{"0123456789"};

    if ( mjono.find_first_not_of(NUMEROMERKIT) != string::npos ) {
        return false;
    }

    tulos = stoi(mjono);

    return true;
}


// Split funktio, nyt toteutettuna kayttaen Lista-luokkaa vectorin sijaan.
// Muuten toimii tismalleen samanlailla.
Lista split(const string& merkkijono, char erotinmerkki) {
    Lista tulos;

    string::size_type tutkittava_kohta{0};
    string kentan_sisalto{""};

    while ( tutkittava_kohta < merkkijono.length() ) {

        if ( merkkijono.at(tutkittava_kohta) != erotinmerkki ) {
            kentan_sisalto.push_back( merkkijono.at(tutkittava_kohta) );

        } else {

            tulos.lisaa_alkio_loppuun(kentan_sisalto);
            kentan_sisalto = "";
        }

        ++tutkittava_kohta;
    }

    tulos.lisaa_alkio_loppuun(kentan_sisalto);

    return tulos;
}

// Luetaan parametrina annetun tiedoston nimen ja muodostaa tiedoston tietojen
// perusteella uuden Paivyrin tai lisaa vanhaan Paivyriin lisaa tietoja.
bool lue_paivyritiedosto(const string& paivyritiedoston_nimi,
                         Paivyri& paivyri) {
    ifstream tiedosto_olio{paivyritiedoston_nimi};
    if ( not tiedosto_olio ) {
        cout << "Virhe: paivyritiedostoa ei saanut avattua." << endl;
        return false;
    }

    string rivi;
    while ( getline(tiedosto_olio, rivi) ) {
        string::size_type erottimen_paikka;

        erottimen_paikka = rivi.find(':');

        if ( erottimen_paikka == string::npos ) {
            cout << "Virhe: syotetiedoston rivilta puuttui ':'." << endl;
            return false;
        }

        string paivays_str;
        string tapahtuman_kuvaus;

        paivays_str = rivi.substr(0, erottimen_paikka);
        tapahtuman_kuvaus = rivi.substr(erottimen_paikka + 1);

        if ( not paivyri.lisaa_tapahtuma(paivays_str, tapahtuman_kuvaus) ) {
            cout << "Virhe: tiedostossa virheellinen paivays." << endl;
            return false;
        }
    }

    tiedosto_olio.close();

    return true;
}

