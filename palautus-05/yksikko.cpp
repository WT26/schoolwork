#include "yksikko.hh"
#include "kohdeyksikot.hh"

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
