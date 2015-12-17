#include "kohdeyksikko.hh"
#include <string>
#include <iostream>
#include <vector>

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


vector<string> Kohdeyksikko::keraa_kohdeyksikot(vector<string> loytyy_listasta){
    bool loytyy_listalta{false};
    int indeksi{0};
    while(indeksi != loytyy_listasta.size()){
        if (loytyy_listasta[indeksi] == yksikko_){
            loytyy_listalta = true;
        }
        indeksi++;
    }
    if(loytyy_listalta == false){
        loytyy_listasta.push_back(yksikko_);
        return loytyy_listasta;
    }
    else{
        return loytyy_listasta;
    }
}


bool Kohdeyksikko::vertaa_nimea(string verrattava){
    if(verrattava == yksikko_){
        return true;
    }
    else{
        return false;
    }
}


double Kohdeyksikko::palauta_suhde(){
    if (suunta_ == true){
        double palautettava = 1 / suhde_;
        return palautettava;
    }
    else{
        double palautettava = 1 * suhde_;
        return palautettava;
    }
}


double Kohdeyksikko::palauta_lisattava(){
    if (suunta_ == true){
        double palautettava = 0 - lisattava_;
        return palautettava;
    }
    else{
        double palautettava = 0 + lisattava_;
        return palautettava;
    }
}


bool Kohdeyksikko::onko_lisattavyytta(){
    if(lisattava_ == 0){
        return false;
    }
    else {
        return true;
    }
}
