#include "lista.hh"
#include <iostream>

// Lista-luokka. Luokka on tehty STL vektorin/dequen kaltaiseksi.
// Lista on linkitetty lista johon voi sijoittaa vain stringeja. Public-osiossa
// on kaikki tarvittavat metodit Listan kasittelyyn ja muokkaukseen, Private-
// osiossa tallessa tarvittavat muistiosoitteet.

using namespace std;

Lista::Lista():
    ensimmaisen_osoite_{nullptr},
    viimeisen_osoite_{nullptr}
{
}


// Metodi lisaa listan loppuun uuden alkion.
void Lista::lisaa_alkio_loppuun(const string &lisattava_string){
    shared_ptr<Listan_alkio> uuden_osoite{
        new Listan_alkio{lisattava_string, nullptr}
    };
    if ( onko_tyhja() ){
        ensimmaisen_osoite_ = uuden_osoite;
        ensimmaisen_osoite_->seuraavan_osoite = nullptr;
        viimeisen_osoite_ = uuden_osoite;
    }
    if( listan_pituus() == 1){
        ensimmaisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
        viimeisen_osoite_->seuraavan_osoite = nullptr;
    }
    else {
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
}


// Metodi poistaa alusta yhden alkion.
bool Lista::poista_alkio_alusta() {
    if ( onko_tyhja() ){
        return false;
    }

    if ( ensimmaisen_osoite_ == viimeisen_osoite_ ){
        ensimmaisen_osoite_ = nullptr;
        viimeisen_osoite_ = nullptr;
    }
    else {
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
    }
    if ( onko_tyhja() ){
        return false;
    }
    else{
        return true;

    }
}


// Metodi tarkistaa onko listassa yhtaan alkioita ja palauttaa boolean arvon.
bool Lista::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    }
    else{
        return false;
    }
}


// Metodi tulostaa listan kaikki alkiot. Metodi tulostaa myos nelja valilyontia
// alkioiden eteen kuten ohjeissa oltiin maaritelty.
void Lista::tulosta() {
    shared_ptr<Listan_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };

    while (tulostettavan_osoite != nullptr) {
        cout<<"     "<<tulostettavan_osoite->alkio<<endl;
        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
    }
}


// Metodi palauttaa tietyn alkion parametrissa saadusta kohdasta.
// (Kuten .at STL-sailioista)
string Lista::kohdassa(int alkion_numero) {
    shared_ptr<Listan_alkio> palautettavan_osoite { ensimmaisen_osoite_ };
    int laskija{0};

    while ( laskija != alkion_numero ){
        palautettavan_osoite = palautettavan_osoite->seuraavan_osoite;
        laskija++;
    }

    return palautettavan_osoite->alkio;

}


// Metodi palauttaa kokonaisluvun Listan Alkioiden maarasta eli listan
// pituuden.
int Lista::listan_pituus(){
    if (ensimmaisen_osoite_ == nullptr){
        int pituus{0};
        return pituus;
    }
    else {
        shared_ptr<Listan_alkio> laskijan_osoite { ensimmaisen_osoite_ };
        int pituus{0};

        while ( laskijan_osoite != nullptr ) {
            laskijan_osoite = laskijan_osoite->seuraavan_osoite;
            pituus++;
        }
        return pituus;
    }
}
