#include "kirjasto.hh"
#include "paivays.hh"
#include "lista.hh"
#include <iostream>
#include <fstream>
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

    //listan alkuun
    else if ( lisattavan_paivays < ensimmaisen_osoite_->paivays ) {
        Lista uusi_lista;
        uusi_lista.lisaa_alkio_loppuun(tapahtuma);

        uuden_osoite->lista = uusi_lista;

        uuden_osoite->seuraavan_osoite = ensimmaisen_osoite_;
        ensimmaisen_osoite_ = uuden_osoite;
    }

    //sama paivays kuin listan alussa
    else if ( lisattavan_paivays == ensimmaisen_osoite_->paivays ){
        ensimmaisen_osoite_->lista.lisaa_alkio_loppuun(tapahtuma);
    }

    //listan loppuun
    else if ( lisattavan_paivays > viimeisen_osoite_->paivays) {
        Lista uusi_lista;
        uusi_lista.lisaa_alkio_loppuun(tapahtuma);

        uuden_osoite->lista = uusi_lista;

        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        uuden_osoite->seuraavan_osoite = nullptr;
        viimeisen_osoite_ = uuden_osoite;
    }
    //sama paivays kuin listan lopussa
    else if ( lisattavan_paivays == viimeisen_osoite_->paivays){
        viimeisen_osoite_->lista.lisaa_alkio_loppuun(tapahtuma);
    }

    else {
        shared_ptr<Kirjaston_alkio> edeltajan_osoite{ensimmaisen_osoite_};
        while( edeltajan_osoite->seuraavan_osoite->
               paivays <= lisattavan_paivays) {
            edeltajan_osoite = edeltajan_osoite->seuraavan_osoite;
        }
        if( edeltajan_osoite->paivays == edeltajan_osoite
                ->seuraavan_osoite->paivays){
            edeltajan_osoite->seuraavan_osoite
                    ->lista.lisaa_alkio_loppuun(tapahtuma);
        }
        else{
            uuden_osoite->seuraavan_osoite
                    = edeltajan_osoite->seuraavan_osoite;
            edeltajan_osoite->seuraavan_osoite = uuden_osoite;
        }
    }
}


bool Kirjasto::poista_tapahtuma(Paivays paivays) {

    if ( onko_tyhja() ){
        return false;
    }

    shared_ptr<Kirjaston_alkio> poistettavan_osoite{ ensimmaisen_osoite_ };
    shared_ptr<Kirjaston_alkio> edeltavan_osoite;

    while( poistettavan_osoite->paivays != paivays) {
        edeltavan_osoite = poistettavan_osoite;
        poistettavan_osoite = poistettavan_osoite->seuraavan_osoite;
    }

    if( poistettavan_osoite->paivays == paivays ) {
        if ( poistettavan_osoite->lista.poista_alkio_alusta() == true){
            return true;
        }
        else {
            edeltavan_osoite->seuraavan_osoite
                    = poistettavan_osoite->seuraavan_osoite;
            return false;
        }
    }
    else {
        return false;
    }
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
    shared_ptr<Kirjaston_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };

    while (tulostettavan_osoite != nullptr) {
        tulostettavan_osoite->paivays.tulosta();
        tulostettavan_osoite->lista.tulosta();
        tulostettavan_osoite->seuraavan_osoite;
    }
}

void Kirjasto::tulosta_tapahtumat(Paivays paivays) const {
    shared_ptr<Kirjaston_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };

    while ( tulostettavan_osoite->paivays != paivays ){
        tulostettavan_osoite->seuraavan_osoite;
    }
    tulostettavan_osoite->paivays.tulosta();
    tulostettavan_osoite->lista.tulosta();
}

void Kirjasto::tallenna(const string paivyritiedoston_nimi) const {
    ofstream tiedosto_olio{paivyritiedoston_nimi};
    shared_ptr<Kirjaston_alkio> tallennettavan_osoite { ensimmaisen_osoite_ };

    while (tallennettavan_osoite != nullptr){
        int laskija{0};
        tiedosto_olio<<tallennettavan_osoite->paivays.merkkijonoksi();
        while(laskija = tallennettavan_osoite->lista.listan_pituus()){
            tiedosto_olio<<tallennettavan_osoite->lista.kohdassa(laskija);

        }
    }
}

