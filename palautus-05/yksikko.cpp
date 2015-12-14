#include "yksikko.hh"
#include "kohdeyksikot.hh"
#include <iostream>

Yksikko::Yksikko(string kohdeyksikon_nimi, Kohdeyksikot kohdeyksikko){

    nimi_ = kohdeyksikon_nimi;
    kohdeyksikot_= kohdeyksikko;
}


bool Yksikko::vertaa_yksikon_nimea(string verrattava){
    if (verrattava == nimi_){
        return true;
    }
    else{
        return false;
    }
}


void Yksikko::lisaa_kohdeyksikko(string lahtoyksikko, double suhde,
                                 double lisattava, bool suunta){
    kohdeyksikot_.lisaa_alkio(lahtoyksikko, suhde, lisattava, suunta);
}


void Yksikko::tulosta_kohdeyksikot(){
    kohdeyksikot_.tulosta();
}
