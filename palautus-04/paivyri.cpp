#include "paivyri.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <fstream>
#include <string>
#include "lista.hh"
#include "kirjasto.hh"

// Paivyri luokka pitaa kirjaa paivyridatasta. Paivyri luokka myos tekee
// kayttajan antamat komennot datalle. Paivyridata koostuu Kirjastosta,
// jossa on Paivaysluokan tapaiset paivamaarat, ja niita vastaavat
// tapahtuma Listat.

using namespace std;

// Rakentaja metodi.
Paivyri::Paivyri() {
}

// Lisataan uusi tapahtuma Paivyriin.
bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {

    // Luodaan uusi Paivays.
    Paivays lisattava_paivays;
    string lisatty = lisaa_nollat(paivamaara);
    lisattava_paivays = Paivays(lisatty);

    // Lisataan Kirjaston alkio paivyridataan.
    paivyridata_.lisaa_alkio(lisattava_paivays, kuvaus);
    return true;
}


// Metodi tulostaa paivyridatan.
bool Paivyri::tulosta_paivyridata(){
    if( paivyridata_.kirjaston_pituus() == 0 ) {
        return false;
    }
    else {
        paivyridata_.tulosta();
        return true;
    }
}


// Tulostaa vain tietyn paivamaaran tapahtumat (komento "nayta").
bool Paivyri::tulosta_paivamaaran_tapahtumat(const string paivamaara) {


    Paivays tulostettava_paivays(paivamaara);

    if( paivyridata_.onko_paivaysta(tulostettava_paivays) == true ){
        paivyridata_.tulosta_tapahtumat(tulostettava_paivays);
        return true;
    }
    else{
        return false;
    }
}

// Poistaa tietylta paivamaaralta ensimmaisen tapahtuman.
bool Paivyri::poista_tapahtuma(const string paivamaara) {
    Paivays poistettava_paivamaara(paivamaara);

    if( paivyridata_.onko_paivaysta(poistettava_paivamaara) == true ){
        paivyridata_.poista_tapahtuma(poistettava_paivamaara);
        return true;
    }
    else{
        return false;
    }

}

// Tallettaa Paivyrin tiedot .txt tiedostoon.
bool Paivyri::talleta_tiedosto(const string paivyritiedoston_nimi){

    paivyridata_.tallenna(paivyritiedoston_nimi);
    return true;
}


// Metodi lisaa paivamaaran eteen tarvittaessa etunollat.
const string Paivyri::lisaa_nollat(const string paivamaara){

    // Lista ppkkvvvv sisaltaa paivamaaran tiedot: paiva on listan ensimmainen
    // stringi, kuukausi toinen ja vuosi kolmas.
    Lista ppkkvvvv = split(paivamaara,'.');

    bool jokin_vaihtui{false};
    string lisattava_pp = ppkkvvvv.kohdassa(0);
    string lisattava_kk = ppkkvvvv.kohdassa(1);

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


