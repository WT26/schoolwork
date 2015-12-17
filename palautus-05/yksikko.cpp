#include "yksikko.hh"
#include "kohdeyksikko.hh"
#include "paaikkuna.hh"
#include <iostream>

Yksikko::Yksikko(string kohdeyksikon_nimi){

    nimi_ = kohdeyksikon_nimi;
    kohdeyksikot_;
}


string Yksikko::tulosta_yksikon_nimi(){
    return nimi_;
}


string Yksikko::tulosta_kohdeyksikot_kohdassa(int i){
    return kohdeyksikot_[i].tulosta();
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


vector<string> Yksikko::keraa_kohdeyksikot(vector<string> loytyy_listasta, vector<Yksikko> kaikki_yksikot, vector<string> lapi_kaydyt){
    bool onko_jo_keratty{false};
    for(int etsija{0};etsija != lapi_kaydyt.size();etsija++){
        if (lapi_kaydyt[etsija] == nimi_) {
            onko_jo_keratty = true;
            break;
        }
    }
    if (onko_jo_keratty == false){
        lapi_kaydyt.push_back(nimi_);
        int indeksi{0};
        while(indeksi != kohdeyksikot_.size()){
            loytyy_listasta = kohdeyksikot_[indeksi].keraa_kohdeyksikot(loytyy_listasta);
            indeksi++;
        }
        indeksi = 0;
        while(indeksi != kaikki_yksikot.size()){
            for(int i{0};i != lapi_kaydyt.size();i++){
                for(int i2{0};i2 != loytyy_listasta.size();i2++){
                    //cout<<"lapikaydyt size:"<<lapi_kaydyt.size()<<"\nloytyylistasta size:"<<loytyy_listasta.size()<<endl;
                    //cout<<"i:"<<i<<"    i2:"<<i2<<endl;
                    if((kaikki_yksikot[indeksi].tulosta_yksikon_nimi() != lapi_kaydyt[i] )
                            && (kaikki_yksikot[indeksi].tulosta_yksikon_nimi() == loytyy_listasta[i2])){
                        loytyy_listasta = kaikki_yksikot[indeksi].keraa_kohdeyksikot(loytyy_listasta, kaikki_yksikot, lapi_kaydyt);

                        bool onko_lapi_kayty{false};
                        for(int etsija{0};etsija != lapi_kaydyt.size();etsija++){
                            if (lapi_kaydyt[etsija] == kaikki_yksikot[indeksi].tulosta_yksikon_nimi()) {
                                onko_lapi_kayty = true;
                                break;
                            }
                        }
                        if(onko_lapi_kayty == false){
                            lapi_kaydyt.push_back(kaikki_yksikot[indeksi].tulosta_yksikon_nimi());
                        }
                        break;
                    }
                }
            }
            indeksi++;
        }
        return loytyy_listasta;
    }
    else {
        return loytyy_listasta;
    }
}


double Yksikko::etsi_kohteen_suhde(double suhde_maara, string lahto, string kohde, vector<Yksikko> kaikki_yksikot, vector<string> lapi_kaydyt){
    cout<<"taalla"<<endl;
    bool onko_jo_keratty{false};
    for(int etsija{0};etsija != lapi_kaydyt.size();etsija++){
        if (lapi_kaydyt[etsija] == nimi_) {
            onko_jo_keratty = true;
            break;
        }
    }
    cout<<"myos taalla"<<endl;
    if (onko_jo_keratty == false){
        for(int indeksi{0};indeksi != kohdeyksikot_.size();indeksi++){
            if(kohdeyksikot_[indeksi].vertaa_nimea(kohde)){
                cout<<"loytyi!"<<endl;
                suhde_maara = suhde_maara * kohdeyksikot_[indeksi].palauta_suhde();
                return suhde_maara;
            }
        }

        lapi_kaydyt.push_back(lahto);
        int indeksi = 0;
        for(indeksi;indeksi != kohdeyksikot_.size();indeksi++){
            for(int i{0};i != kaikki_yksikot.size(); i++){
                for(int i2{0};i2 != lapi_kaydyt.size();i2++){

                    if((kaikki_yksikot[i].vertaa_yksikon_nimea(kohdeyksikot_[indeksi].tulosta())
                        && (!kohdeyksikot_[indeksi].vertaa_nimea(lapi_kaydyt[i2])))){
                        double sopivan_kohdeyksikon_suhde = kohdeyksikot_[indeksi].palauta_suhde();
                        suhde_maara = suhde_maara * sopivan_kohdeyksikon_suhde;
                        return kaikki_yksikot[i].etsi_kohteen_suhde(suhde_maara,
                                            kaikki_yksikot[i].tulosta_yksikon_nimi(), kohde, kaikki_yksikot, lapi_kaydyt);
                    }
                }
            }
        }
        return suhde_maara;
    }
    else{
        return suhde_maara;
    }
}
