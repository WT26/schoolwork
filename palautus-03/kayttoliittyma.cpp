#include "paivyri.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


namespace {

    void tulosta_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        loppurivi >> ws;

        if ( loppurivi.peek() != EOF ) {
            cout << "Virhe: tulosta-komennon perassa ylimaaraista." << endl;
            return;
        }

        if(!paiv.tulosta_paivyridata()){
            cout << "Paivyri on tyhja." << endl;
        }
    }


    void nayta_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string paivamaara;

        loppurivi >> ws >> paivamaara >> ws;

        if ( not loppurivi ) {
            cout << "Virhe: paivamaara ei saa olla tyhja." << endl;
            return;
        }

        if ( loppurivi.peek() != EOF ) {
            cout << "Virhe: nayta-komennon perassa ylimaaraista." << endl;
            return;
        }

        if(!paiv.tulosta_merkinnat(paivamaara)){
            cout << "Paivamaaralle ei ole tehty merkintoja." << endl;
        }
        // Tässä pitää tulostaa «paivamaara»:n tapahtumat «paiv»:stä.
    }


    void lisaa_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string paivamaara;
        string tapahtuma;

        loppurivi >> ws >> paivamaara >> ws;

        if ( not loppurivi ) {
            cout << "Virhe: paivamaara puuttui." << endl;
            return;
        }

        getline(loppurivi, tapahtuma);
        if ( tapahtuma == "" ) {
            cout << "Virhe: tapahtuma ei saa olla tyhja." << endl;
            return;
        }

        // Lisataan syotetty paivamaara ja silloin tapahtunut tapahtuma.
        paiv.lisaa_tapahtuma(paivamaara, tapahtuma);

    }


    void poista_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string paivamaara;

        loppurivi >> ws >> paivamaara >> ws;

        if ( not loppurivi ) {
            cout << "Virhe: paivamaara ei saa olla tyhja." << endl;
            return;
        }

        if ( loppurivi.peek() != EOF ) {
            cout << "Virhe: poista-komennon perassa ylimaaraista." << endl;
            return;
        }

        paiv.poista_tapahtuma(paivamaara);

        // Poistaa tarvittaessa tyhja paivays.
        paiv.poista_tyhja_paivays(paivamaara);


        // Tässä poistetaan «paivamaara»:ltä vanhin merkintä, eli siis
        // jäljellä olevista se, joka on ollut rakenteessa kauimmin.
    }


    void lue_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string tiedoston_nimi;

        loppurivi >> ws;
        getline(loppurivi, tiedoston_nimi);

        if ( tiedoston_nimi.empty() ) {
            cout << "Virhe: tiedoston nimi ei saa olla tyhja." << endl;
            return;
        }


        if ( not lue_paivyritiedosto(tiedoston_nimi, paiv) ) {
            cout<<"Virhe: tiedostoa ei saatu luettua."<<endl;
        }

        // Tässä luetaan tiedostosta «tiedoston_nimi» päivämäärät ja
        // tapahtumat ja lisätään ne «paiv»-rakenteeseen siellä
        // entuudestaan olevien tapahtumien lisäksi.
    }


    void talleta_toiminto(Paivyri& paiv, istringstream& loppurivi) {
        string tiedoston_nimi;

        loppurivi >> ws;
        getline(loppurivi, tiedoston_nimi);

        if ( tiedoston_nimi.empty() ) {
            cout << "Virhe: tiedoston nimi ei saa olla tyhja." << endl;
            return;
        }

        paiv.talleta_tiedosto(tiedoston_nimi);
        cout << "Testi: [" << tiedoston_nimi << "]" << endl;

        // Tässä talletetaan kaikki «paiv»-rakenteessa olevat tapahtumat
        // tiedostoon «tiedoston_nimi», jonka on oltava talletuksen
        // jälkeen sellaisessa muodossa, että se voidaan syöttää
        // ohjelmalle uudelleen käynnistysvaiheessa tai lue-komennolla.
    }

}

void kayttoliittyma(Paivyri& paivyri) {
    string syoterivi;
    while ( true ) {
        cout << "paivyrikomento> ";
        getline(cin, syoterivi);

        if ( not cin or syoterivi == "" ) {
            break;
        }

        istringstream rivivirta{syoterivi};

        string komento;
        rivivirta >> komento;

        if ( not rivivirta ) {
            cout << "Virhe: komennoksi ei saa syottaa pelkkia valeja." << endl;
            continue;
        }

        if ( komento == "tulosta" ) {
            tulosta_toiminto(paivyri, rivivirta);

        } else if ( komento == "nayta" ) {
            nayta_toiminto(paivyri, rivivirta);

        } else if ( komento == "lisaa" ) {
            lisaa_toiminto(paivyri, rivivirta);

        } else if ( komento == "poista" ) {
            poista_toiminto(paivyri, rivivirta);

        } else if ( komento == "lue" ) {
            lue_toiminto(paivyri, rivivirta);

        } else if ( komento == "talleta" ) {
            talleta_toiminto(paivyri, rivivirta);

        } else {
            cout << "Virhe: tuntematon komento." << endl;
        }
    }
}
