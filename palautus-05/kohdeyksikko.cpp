#include "kohdeyksikko.hh"
#include <string>
#include <iostream>

Kohdeyksikko::Kohdeyksikko(string yksikon_nimi, double suhde, double lisattava,
                           bool suunta)
{
    yksikko_ = yksikon_nimi;
    suhde_ = suhde;
    lisattava_ = lisattava;
    suunta_ = suunta;
}


string Kohdeyksikko::tulosta(){
    return yksikko_;
}
