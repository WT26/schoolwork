#include "kirjasto.hh"
#include "paivays.hh"
#include "lista.hh"
#include <iostream>
#include <string>


Kirjasto::Kirjasto():
    ensimmaisen_osoite_{nullptr},
    viimeisen_osoite_{nullptr}
{
}



void Kirjasto::lisaa_alkio(Paivays lisattavan_paivays,const string &tapahtuma){
    shared_ptr<Kirjaston_alkio> uuden_osoite;
    uuden_osoite->paivays = lisattavan_paivays;

    if ( onko_tyhja() ){
        Lista uusi_lista;
        uusi_lista.lisaa_alkio_loppuun(tapahtuma);

        uuden_osoite->lista = uusi_lista;
        uuden_osoite->seuraavan_osoite = nullptr;

        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
//    else if ( lisattavan_paivays == ensimmaisen_osoite_->paivays ) {
//        ensimmaisen_osoite_->lista.lisaa_alkio_loppuun(tapahtuma);
//

    //listan alkuun
    else if ( lisattavan_paivays < ensimmaisen_osoite_->paivays ) {

        uuden_osoite->seuraavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = uuden_osoite;
    }




    else {
        shared_ptr<Kirjaston_alkio> edeltajan_osoite{ensimmaisen_osoite_};
        while( edeltajan_osoite->seuraavan_osoite->paivays >= lisattavan_paivays) {
            edeltajan_osoite = edeltajan_osoite->seuraavan_osoite;
        }

        uuden_osoite->seuraavan_osoite = edeltajan_osoite->seuraavan_osoite;
        edeltajan_osoite->seuraavan_osoite = uuden_osoite;
    }
}







bool Kirjasto::poista_alkio_alusta(string &poistettu_string) {
    if ( onko_tyhja() ){
        return false;
    }

    shared_ptr<Listan_alkio> poistettavan_osoite{ ensimmaisen_osoite_ };
    poistettu_string = poistettavan_osoite->alkio;

    if ( ensimmaisen_osoite_ == viimeisen_osoite_ ){
        ensimmaisen_osoite_ = nullptr;
        viimeisen_osoite_ = nullptr;
    }
    else {
        ensimmaisen_osoite_ = ensimmaisen_osoite_->seuraavan_osoite;
    }
    return true;
}

bool Kirjasto::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    }
    else{
        return false;
    }
}

void Kirjasto::tulosta() const {
    shared_ptr<Listan_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };
    int jarjestysnumero{1};

    while (tulostettavan_osoite != nullptr) {
        cout<< jarjestysnumero << ". " << tulostettavan_osoite->alkio <<endl;
    }
}
