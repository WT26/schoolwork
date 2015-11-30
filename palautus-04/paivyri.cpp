#include "paivyri.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <fstream>
#include <string>
#include "lista.hh"
#include "kirjasto.hh"

using namespace std;

// Rakentaja metodi.
Paivyri::Paivyri() {
}

// Lisataan uusi tapahtuma Paivyriin.
bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {

    // Luodaan uusi Paivays.
    Paivays lisattava_paivays;
    string lisatty = lisaa_nollat(lisattava_paivays.merkkijonoksi(paivamaara));
    cout<<"moi"<<endl;

    lisattava_paivays = Paivays(lisatty);

    // Tutkitaanko onko kyseista paivaysta paivyrissa. Jos se on, ei
    // luoda uutta.
    paivyridata_.lisaa_alkio(lisattava_paivays, kuvaus);
    return true;
}


// Metodi tulostaa paivyridatan.
bool Paivyri::tulosta_paivyridata(){

    paivyridata_.tulosta();
/*
    else {
        map<Paivays, deque<string>>::iterator map_iter;
        deque<string>::iterator deque_iter;

        map_iter = paivyridata_.begin();

        // Kaydaan lapi kaikki Paivaykset ja tulostetaan paivamaara.
        while (map_iter != paivyridata_.end()){

            cout<<  lisaa_nollat(map_iter->first.merkkijonoksi())<<endl;
            deque_iter = map_iter->second.begin();

            // Tulostetaan kaikki paivamaaralle kirjatut tapahtumat.
            while(deque_iter != map_iter->second.end()){
                cout<<"    "<<*deque_iter<<endl;
                deque_iter++;
            }

            map_iter++;
        }
    }*/
    return true;
}


// Tulostaa vain tietyn paivamaaran tapahtumat (komento nayta)
bool Paivyri::tulosta_paivamaaran_tapahtumat(const string paivamaara) {

    Paivays tulostettava_paivays(paivamaara);
    paivyridata_.tulosta_tapahtumat(tulostettava_paivays);

    return true;

}

// Poistaa tietylta paivamaaralta ensimmaisen tapahtuman.
bool Paivyri::poista_tapahtuma(const string paivamaara) {

    Paivays poistettava_paivamaara(paivamaara);
    paivyridata_.poista_tapahtuma(poistettava_paivamaara);

    return true;
}

// Tallettaa Paivyrin tiedot .txt tiedostoon.
bool Paivyri::talleta_tiedosto(const string paivyritiedoston_nimi){
    ofstream tiedosto_olio{paivyritiedoston_nimi};

    map<Paivays, deque<string>>::iterator map_iter;
    deque<string>::iterator deque_iter;

    map_iter = paivyridata_.begin();
    deque_iter = map_iter->second.begin();

    while (map_iter != paivyridata_.end()){

        deque_iter = map_iter->second.begin();

        // Talletetaan kaikki paivamaaralle kirjatut tapahtumat.
        while(deque_iter != map_iter->second.end()){
            tiedosto_olio<< map_iter->first.merkkijonoksi()<<":";
            tiedosto_olio<<*deque_iter<<"\n";
            deque_iter++;
        }

        map_iter++;
    }
    return true;
}


// Metodi lisaa paivamaaran eteen tarvittaessa etunollat.
const string Paivyri::lisaa_nollat(const string paivamaara){

    // Lista ppkkvvvv sisaltaa paivamaaran tiedot: paiva on listan ensimmainen
    // stringi, kuukausi toinen ja vuosi kolmas.
    Lista ppkkvvvv = split(paivamaara,'.');

    bool jokin_vaihtui{false};
    string lisattava_pp;
    string lisattava_kk;

    // Paivaan lisataan tarvittaessa nolla.
    if(ppkkvvvv.kohdassa(0).length() < 2) {
        lisattava_pp = "0" + ppkkvvvv.kohdassa(0);
        jokin_vaihtui = true;
    }

    // Kuukauteen lisataan tarvittaessa nolla.
    if(ppkkvvvv.kohdassa(1).length() < 2) {
        lisattava_kk = "0" + ppkkvvvv.kohdassa(1);
        jokin_vaihtui = true;
    }

    if( jokin_vaihtui == true) {
        const string nollat_lisatty = lisattava_pp + "."
                + lisattava_kk + "." + ppkkvvvv.kohdassa(2);
        return nollat_lisatty;
    }
    else {
        return paivamaara;
    }
}


