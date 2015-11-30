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

bool Lista::poista_alkio_alusta(string &poistettu_string) {
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
