#include "kohdeyksikot.hh"

#include <iostream>
#include <string>

using namespace std;

Kohdeyksikot::Kohdeyksikot():
ensimmaisen_osoite_{nullptr},
viimeisen_osoite_{nullptr}
{
}

Kohdeyksikot::~Kohdeyksikot(){
    ensimmaisen_osoite_ = nullptr;
    viimeisen_osoite_ = nullptr;
}


    // Metodi lisaa listan loppuun uuden alkion.
bool Kohdeyksikot::lisaa_alkio(string lisattava_string, double suhde,
                               double lisattava, bool suunta){
    shared_ptr<Yksikko_alkio> uuden_osoite{
        new Yksikko_alkio{lisattava_string, suhde, lisattava, suunta, nullptr}
    };
    if ( onko_tyhja() ){
        ensimmaisen_osoite_ = uuden_osoite;
        ensimmaisen_osoite_->seuraavan_osoite = nullptr;
        viimeisen_osoite_ = uuden_osoite;
    }
    else if( listan_pituus() == 1){
        ensimmaisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
        viimeisen_osoite_->seuraavan_osoite = nullptr;
    }
    else {
        viimeisen_osoite_->seuraavan_osoite = uuden_osoite;
        viimeisen_osoite_ = uuden_osoite;
    }
}


bool Kohdeyksikot::onko_tyhja() const {
    if ( ensimmaisen_osoite_ == nullptr ) {
        return true;
    }
    else{
        return false;
    }
}


// Metodi palauttaa kokonaisluvun Listan Alkioiden maarasta eli listan
// pituuden.
int Kohdeyksikot::listan_pituus(){
    if (ensimmaisen_osoite_ == nullptr){
        int pituus{0};
        return pituus;
    }
    else {
        shared_ptr<Yksikko_alkio> laskijan_osoite { ensimmaisen_osoite_ };
        int pituus{0};

        while ( laskijan_osoite != nullptr ) {
            laskijan_osoite = laskijan_osoite->seuraavan_osoite;
            pituus++;
        }
        return pituus;
    }
}


bool Kohdeyksikot::tulosta(){
    if(ensimmaisen_osoite_ == nullptr){
        return false;
    }
    else {
        shared_ptr<Yksikko_alkio> tulostettavan_osoite { ensimmaisen_osoite_ };
        while(tulostettavan_osoite != nullptr){
            cout<<"yksikko "<<tulostettavan_osoite->yksikko<<"\n";
            tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite;
        }
        return true;
    }
}
