#include "lista.hh"
#include <iostream>

using namespace std;

Lista::Lista():
    ensimmaisen_osoite_{nullptr},
    viimeisen_osoite_{nullptr}
{
}

void Lista::lisaa_alkio_loppuun(const string &lisattava_string){
    shared_ptr<Listan_alkio> uuden_osoite{
        new Listan_alkio{lisattava_string, nullptr}
    };
    if ( onko_tyhja() ){
        ensimmaisen_osoite_ = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
    else {
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
}



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
    return true;
}

bool Lista::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    }
    else{
        return false;
    }
}

void Lista::tulosta() const {
    shared_ptr<Listan_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };
    int jarjestysnumero{1};

    while (tulostettavan_osoite != nullptr) {
        cout<< jarjestysnumero << ". " << tulostettavan_osoite->alkio <<endl;
    }
}

string Lista::kohdassa(int alkion_numero) {
    shared_ptr<Listan_alkio> palautettavan_osoite { ensimmaisen_osoite_ };
    int laskija{0};

    while ( laskija != alkion_numero ){
        palautettavan_osoite = palautettavan_osoite->seuraavan_osoite;
        laskija++;
    }

    return palautettavan_osoite->alkio;

}

int Lista::listan_pituus() {
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
        pituus++;
        return pituus;
    }
}
