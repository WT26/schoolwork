#include "kirjasto.hh"
#include "paivays.hh"
#include "lista.hh"
#include <iostream>
#include <fstream>
#include <string>

// Kirjasto-luokka. Luokka on tehty STL:lan Mapin kaltaiseksi, siina luodaan
// structissa jokaiselle alkiolle paivays ja sita vastaava lista. Kirjasto
// toimii linkitetyn listan tavoin shared-pointtereilla. Listaa pidetaan
// ensimmaisesta ja viimeisesta osoitteesta.

Kirjasto::Kirjasto():
    ensimmaisen_osoite_{nullptr},
    viimeisen_osoite_{nullptr}
{
}


// Lisaa kirjastoon alkioita, parametreina taytyy olla paivays ja tapahtuma.
void Kirjasto::lisaa_alkio(Paivays lisattavan_paivays,const string &tapahtuma){
    Lista uusi_lista;
    shared_ptr<Kirjaston_alkio> uuden_osoite
    { new Kirjaston_alkio{lisattavan_paivays, uusi_lista, nullptr}};

    // Kun kirjasto on tyhja, lisataan haluttu paivays ja tapahtuma kirjaston
    // ensimmaiseksi alkioksi.
    if ( onko_tyhja() ){
        Lista uusi_lista;
        uusi_lista.lisaa_alkio_loppuun(tapahtuma);

        uuden_osoite->lista = uusi_lista;
        uuden_osoite->seuraavan_osoite = nullptr;

        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }

    // Lisataan uusi kirjaston alkio alkuun.
    else if ( lisattavan_paivays < ensimmaisen_osoite_->paivays ) {

        Lista uusi_lista;
        uusi_lista.lisaa_alkio_loppuun(tapahtuma);

        uuden_osoite->lista = uusi_lista;

        uuden_osoite->seuraavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = uuden_osoite;
    }

    // Lisataan tapahtuma jo olemassaolevalle paivaykselle, jos
    // paivays on sama kuin ensimmaisen alkion paivays.
    else if ( lisattavan_paivays == ensimmaisen_osoite_->paivays ){

        ensimmaisen_osoite_->lista.lisaa_alkio_loppuun(tapahtuma);
    }

    // Lisataan uusi kirjaston alkio loppuun.
    else if ( lisattavan_paivays > viimeisen_osoite_->paivays ) {

        Lista uusi_lista;
        uusi_lista.lisaa_alkio_loppuun(tapahtuma);

        uuden_osoite->lista = uusi_lista;

        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        uuden_osoite->seuraavan_osoite = nullptr;
        viimeisen_osoite_ = uuden_osoite;
    }

    // Lisataan tapahtuma jo olemassaolevalle paivaykselle, jos paivays
    // on sama kuin viimeisessa alkion paivayksessa.
    else if ( lisattavan_paivays == viimeisen_osoite_->paivays ){
        viimeisen_osoite_->lista.lisaa_alkio_loppuun(tapahtuma);
    }

    // Muissa tilanteissa uusi kirjaston alkio luodaa oikeaan valiin.
    else {
        shared_ptr<Kirjaston_alkio> edeltajan_osoite{ensimmaisen_osoite_};

        // Etsitaan oikea kohta, johon Paivays kuuluu pienempi tai yhtasuuri
        // kuin operaattorilla.
        while( edeltajan_osoite->seuraavan_osoite->
               paivays <= lisattavan_paivays ) {
            edeltajan_osoite = edeltajan_osoite->seuraavan_osoite;
        }

        // Jos paivays on jo olemassa, lisataan vain uusi tapahtuma listaan.
        if( edeltajan_osoite->paivays == edeltajan_osoite
                ->seuraavan_osoite->paivays){
            edeltajan_osoite->seuraavan_osoite
                    ->lista.lisaa_alkio_loppuun(tapahtuma);
        }

        // Muissa tapauksissa luodaan paivaykselle uusi lista.
        else {
            Lista uusi_lista;
            uusi_lista.lisaa_alkio_loppuun(tapahtuma);

            uuden_osoite->lista = uusi_lista;
            uuden_osoite->seuraavan_osoite
                    = edeltajan_osoite->seuraavan_osoite;
            edeltajan_osoite->seuraavan_osoite = uuden_osoite;
        }
    }
}


// Metodi poistaa tapahtumia Kirjastosta. Jos tietylla paivayksella ei ole
// enaa tapahtumia, poistaa se myos paivayksen.
bool Kirjasto::poista_tapahtuma(Paivays paivays) {

    if ( onko_tyhja() ){
        return false;
    }

    shared_ptr<Kirjaston_alkio> poistettavan_osoite{ ensimmaisen_osoite_ };
    shared_ptr<Kirjaston_alkio> edeltavan_osoite;

    // Etsitaan poistettava osoite paivayksen avulla.
    while( poistettavan_osoite->paivays != paivays) {
        edeltavan_osoite = poistettavan_osoite;
        poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
    }

    // Poistetaan tapahtuma ja tarvittaessa myös paivays.
    if( poistettavan_osoite->paivays == paivays ) {
        if ( poistettavan_osoite->lista.poista_alkio_alusta() == true){
            return true;
        }
        else {
            if(poistettavan_osoite == ensimmaisen_osoite_){
                ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
                return false;
            }
            poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
            edeltavan_osoite->seuraavan_osoite = poistettavan_osoite;
            return false;
        }
    }
    else {
        return false;
    }
}


// Metodi tarkistaa onko Kirjasto tyhja.
bool Kirjasto::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    }
    else{
        return false;
    }
}


// Metodi tarkistaa onko kirjastossa tiettya paivaysta saamallaan
// parametrin avulla.
bool Kirjasto::onko_paivaysta(Paivays paivays){
    shared_ptr<Kirjaston_alkio>
            tutkittavan_osoite { ensimmaisen_osoite_ };
    while(tutkittavan_osoite != nullptr){

        if(tutkittavan_osoite->paivays == paivays){
            return true;
        }
        tutkittavan_osoite = tutkittavan_osoite->seuraavan_osoite;
    }
    return false;
}


// Tulostaa kaikki paivaykset ja niissa olevat tapahtumat jarjestyksessa.
bool Kirjasto::tulosta() {
    if(ensimmaisen_osoite_ == nullptr){
        return false;
    }
    else {
        shared_ptr<Kirjaston_alkio>
                tulostettavan_osoite { ensimmaisen_osoite_ };

        while (tulostettavan_osoite != nullptr) {
            tulostettavan_osoite->paivays.tulosta();
            tulostettavan_osoite->lista.tulosta();
            tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
        }
    }
}


// Tulostaa tietyn paivayksen tapahtumat.
bool Kirjasto::tulosta_tapahtumat(Paivays paivays) const {
    if(ensimmaisen_osoite_ == nullptr){
        return false;
    }
    else {
        shared_ptr<Kirjaston_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };
        while ( tulostettavan_osoite->paivays != paivays ){
            tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
        }
        tulostettavan_osoite->paivays.tulosta();
        tulostettavan_osoite->lista.tulosta();
        return true;
    }
}


// Tallettaa koko kirjaston datan jo olemassaolevaan .txt tiedostoon.
// Tiedoston nimen paivyriohjelman kayttaja voi itse syottaa.
void Kirjasto::tallenna(const string paivyritiedoston_nimi) const {
    ofstream tiedosto_olio{paivyritiedoston_nimi};
    shared_ptr<Kirjaston_alkio> tallennettavan_osoite { ensimmaisen_osoite_ };

    while (tallennettavan_osoite != nullptr){
        int laskija{0};

        // Kaydaan lapi kaikki paivaykset ja niissa olevat tapahtumat ja
        // sijoitetaan ne avattuun tiedostoon.
        while(laskija < tallennettavan_osoite->lista.listan_pituus()){
            tiedosto_olio<<tallennettavan_osoite->paivays.merkkijonoksi();
            tiedosto_olio<<":";
            tiedosto_olio<<tallennettavan_osoite->lista.kohdassa(laskija);
            tiedosto_olio<<"\n";
            laskija++;
        }
        tallennettavan_osoite = tallennettavan_osoite->seuraavan_osoite;
    }
}


// Metodi palauttaa kokonaisluvun Kirjaston Paivaysten lukumaarasta, eli
// kirjaston pituudesta.(kuten STL Map.size)
int Kirjasto::kirjaston_pituus() {
    if (ensimmaisen_osoite_ == nullptr){
        int pituus{0};
        return pituus;
    }
    else {
        shared_ptr<Kirjaston_alkio> laskijan_osoite { ensimmaisen_osoite_ };
        int pituus{0};

        while ( laskijan_osoite != nullptr ) {
            laskijan_osoite = laskijan_osoite->seuraavan_osoite;
            pituus++;
        }
        return pituus;
    }
}

