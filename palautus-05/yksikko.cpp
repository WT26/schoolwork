#include "yksikko.hh"
#include "kohdeyksikko.hh"
#include <iostream>

Yksikko::Yksikko(string kohdeyksikon_nimi){

    nimi_ = kohdeyksikon_nimi;
    kohdeyksikot_;
}


string Yksikko::tulosta_yksikon_nimi(){
    return nimi_;
}


bool Yksikko::vertaa_yksikon_nimea(string verrattava){
    if (verrattava == nimi_){
        return true;
    }
    else{
        return false;
    }
}


int Yksikko::kohdeyksikkojen_maara(){
    int lukumaara;
    lukumaara = kohdeyksikot_.size();
    return lukumaara;
}


void Yksikko::lisaa_kohdeyksikko(string lahtoyksikko, double suhde,
                                 double lisattava, bool suunta){
    Kohdeyksikko uusi_kohdeyksikko(lahtoyksikko, suhde, lisattava, suunta);
    kohdeyksikot_.push_back(uusi_kohdeyksikko);
}


void Yksikko::tulosta_kohdeyksikot(){
    int indeksi{0};
    while(indeksi != kohdeyksikot_.size()){
        kohdeyksikot_[indeksi].tulosta();
        indeksi++;
    }
}
