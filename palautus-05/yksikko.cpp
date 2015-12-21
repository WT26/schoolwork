#include "yksikko.hh"
#include "kohdeyksikko.hh"
#include "paaikkuna.hh"
#include <iostream>

// Jokaisesta tekstitiedoston kaavasta tehdaan yksikko-olio. Yksikko oliossa
// on tallessa vektorissa kaikki sen kohdeyksikot, eli ne yksikot, joiden
// kaavat ovat suoraan lukuvaiheessa yhteydessa yksikkoon. Yksikolla on
// myos useita metodeita, joita tarvitaan haku, ja muunnos algoritmeissa.

using namespace std;

Yksikko::Yksikko(string kohdeyksikon_nimi){
    nimi_ = kohdeyksikon_nimi;
}


// Yksikon nimen palauttaminen on huonoa ohjelmointityylia, varsinkin jos
// nimi kuuluu private osaan (tasta syysta se on vaihdettu publicciin).
// Nimea tarvitaan rekursiivisessa etsimis-metodeissa parametrina uudelle
// "kierrokselle", enka keksinyt talle toista tapaa. Yksikon nimea
// tarvitaan myos siina vaiheessa kun ne lisataan UI:hin. Googlaamalla loytyi
// jotain tapoja, miten kyseiset toiminnot olisi voinut tehda muissa
// luokissa kuin UI:luokassa, mutta asia olisi ollut niin paljon ylikurssia
// etten sellaista alkanut opiskelemaan.
string Yksikko::tulosta_yksikon_nimi(){
    return nimi_;
}


// Tutkii onko yksikolla tiettya kohdeyksikkoa.
bool Yksikko::loytyyko_kohdeyksikko(string yksikko_nimi){
    for(auto kohdeyksikko : kohdeyksikot_){
        if(kohdeyksikko.tulosta() == yksikko_nimi){
            return true;
        }
    }
    return false;
}


// Vertaa parametrina saatua nimea yksikon nimeen.
bool Yksikko::vertaa_yksikon_nimea(string verrattava){
    if (verrattava == nimi_){
        return true;
    }
    else{
        return false;
    }
}


// Palauttaa yksikolla olevien kohdeyksikoiden maaran.
int Yksikko::kohdeyksikkojen_maara(){
    int lukumaara;
    lukumaara = kohdeyksikot_.size();
    return lukumaara;
}


// Lisaa yksikolle kohdeyksikot_ vektroiin uuden kohdeyksikon.
void Yksikko::lisaa_kohdeyksikko(string lahtoyksikko, double suhde,
                                 double lisattava, bool suunta){
    Kohdeyksikko uusi_kohdeyksikko(lahtoyksikko, suhde, lisattava, suunta);
    kohdeyksikot_.push_back(uusi_kohdeyksikko);
}


// Funktio keraa vector<stringiin> kaikki ne kohdeyksikot, jotka
// pystytaan muutamaan tiedettyjen kaavojen avulla.
vector<string> Yksikko::keraa_kohdeyksikot(vector<string> loytyy_listasta,
                   vector<Yksikko> kaikki_yksikot, vector<string> lapi_kaydyt){

    // Tutkitaan onko jo kyseinen yksikko tutkittu lapikotaisin vai ei.
    // lapi_kaydyt vektorissa on kaikki ne yksikot jotka on jo tutkittu.
    bool onko_jo_keratty{false};
    for( unsigned int etsija{0}; etsija != lapi_kaydyt.size(); etsija++ ){
        if ( lapi_kaydyt[etsija] == nimi_ ) {
            onko_jo_keratty = true;
            break;
        }
    }
    if ( onko_jo_keratty == false ){
        lapi_kaydyt.push_back(nimi_);

        // Lisataan "loytyy_listasta" vektoriin sellaiset kohdeyksikot jotka
        // taytyy kayda lapi. Naissa yksikoissa voi olla sellaisia
        // suhteita uusiin yksikoihin, joihin ei muuten paasisi kasiksi.
        unsigned int indeksi{0};
        while(indeksi != kohdeyksikot_.size()){
            loytyy_listasta =
                    kohdeyksikot_[indeksi].keraa_kohdeyksikot(loytyy_listasta);
            indeksi++;
        }

        // Varsinainen haku vaihe. Etsitaan sopiva yksikko ja lisataan se
        // vektoriin.
        indeksi = 0;
        while(indeksi != kaikki_yksikot.size()){
            for(unsigned int i{0};i != lapi_kaydyt.size();i++){
                for(unsigned int i2{0};i2 != loytyy_listasta.size();i2++){

                    // Tahan if:fiin paastaan siis vain jos tutkittava yksikko
                    // EI ole jo lapikaydyissa yksikoissa (lapi_kaydyt)
                    // ja tama yksikko ON yksi halutuista (loytyy_listasta)
                    // yksikoista. Tama vaihe voi olla erittain pitka, jos
                    // saantoja on tiedostossa paljon ja saanto-jono on pitka.
                    // Esimerkkina pisin mahdollinen jono on kun muutetaan
                    // pituuksia esim um->yard. Maksimissaan tama on kestanyt
                    // jopa 30s. Nopeuttavia tekijoita en oikein keksinyt.
                    if((!kaikki_yksikot[indeksi]
                                .vertaa_yksikon_nimea(lapi_kaydyt[i]))
                                && (kaikki_yksikot[indeksi]
                                .vertaa_yksikon_nimea(loytyy_listasta[i2]))){

                        // Rekursiivisesti etsitaan taman yksikon kohdeyksikot.
                        loytyy_listasta = kaikki_yksikot[indeksi].
                                keraa_kohdeyksikot(loytyy_listasta,
                                                   kaikki_yksikot, lapi_kaydyt);

                        bool onko_lapi_kayty{false};
                        for( unsigned int etsija{0}; etsija !=
                                lapi_kaydyt.size(); etsija++ ){

                            if ( kaikki_yksikot[indeksi]
                                   .vertaa_yksikon_nimea(lapi_kaydyt[etsija])) {

                                onko_lapi_kayty = true;
                                break;
                            }
                        }
                        if(onko_lapi_kayty == false){
                            lapi_kaydyt.push_back(
                                kaikki_yksikot[indeksi].tulosta_yksikon_nimi());
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


// Tismalleen samanlainen idea kuin ylemmassa, mutta tama metodi etsiikin
// yksikoiden valisen suhteen, ja palauttaa sen(double). Metodi palauttaa
// myos arvon (int) joka kertoo onko etsitty kohde saavutettu, ja rekursiivinen
// suhteen etsinta voidaan lopettaa. int saa siis vain arvoja 0 eli ei ole
// loytynyt ja 1 eli on loytynyt. Metodi kertoo suhdetta aina etsiessaan
// oikeaa kohdeyksikkoa, ja kun se ottaa askelia taaksepain, se jakaa suhdetta
// jotta tulos olisi oikea.
pair<double, int> Yksikko::etsi_kohteen_suhde(pair<double, int> suhde_maara,
                 string ensimmainen, string lahto, string kohde,
                 vector<Yksikko> kaikki_yksikot, vector<string> lapi_kaydyt){

    // Kun askelia otetaan taaksepain, suhde osataan muuttaa jakamalla
    // edellisella. Ainoa poikkeus on kun palataankin lahtoyksikkoon.
    // Silloin suhde pitaa palauttaa manuaalisesti takaisin ykkoseksi.
    if(ensimmainen == lahto){
        suhde_maara.first = 1;
    }

    // Samallailla kuin ylemmassa metodissa, tutkitaan onko tata yksikkoa jo
    // tutkittu.
    bool onko_jo_keratty{false};
    for(unsigned int etsija{0};etsija != lapi_kaydyt.size();etsija++){
        if (lapi_kaydyt[etsija] == nimi_) {
            onko_jo_keratty = true;
            break;
        }
    }
    if (onko_jo_keratty == false){

        // Kohdeyksikko on haluttu "kohde" ja voidaan palauttaa oikea
        // suhde_maara.
        for(unsigned int indeksi{0};indeksi != kohdeyksikot_.size();indeksi++){
            if(kohdeyksikot_[indeksi].vertaa_nimea(kohde)){
                suhde_maara.first = suhde_maara.first
                        * kohdeyksikot_[indeksi].palauta_suhde();

                suhde_maara.second = 1;

                return suhde_maara;
            }
        }

        lapi_kaydyt.push_back(lahto);

        // Samalla tavalla kuin edellisessa metodissa, nyt vain etsitaan kohde-
        // Yksikkoa ja sen suhdetta. Nykyinen suhde kerrotaan sopivalla
        // seuraavalla suhteella, ja jatketaan etsimista silla yksikolla.
        for(unsigned int indeksi{0};indeksi != kohdeyksikot_.size();indeksi++){
            for(unsigned int i{0};i != kaikki_yksikot.size(); i++){
                for(unsigned int i2{0};i2 != lapi_kaydyt.size();i2++){

                    if( (kaikki_yksikot[i].vertaa_yksikon_nimea(
                            kohdeyksikot_[indeksi].tulosta())
                            && ( !kohdeyksikot_[indeksi].vertaa_nimea(
                            lapi_kaydyt[i2]))) ) {

                        double sopivan_kohdeyksikon_suhde
                                = kohdeyksikot_[indeksi].palauta_suhde();

                        suhde_maara.first = suhde_maara.first
                                * sopivan_kohdeyksikon_suhde;

                        suhde_maara = kaikki_yksikot[i]
                                .etsi_kohteen_suhde(suhde_maara, ensimmainen,
                                kaikki_yksikot[i].tulosta_yksikon_nimi(),
                                kohde, kaikki_yksikot, lapi_kaydyt);

                        if(kaikki_yksikot[i].loytyyko_kohdeyksikko(kohde)){
                            return suhde_maara;
                        }
                        else {
                            if(suhde_maara.second == 1){
                                return suhde_maara;
                            }
                            else{
                                suhde_maara.first
                                  = suhde_maara.first
                                    / sopivan_kohdeyksikon_suhde;
                            }
                        }
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


// Kuten kaksi edellista, tamakin metodi kay lapi yksikoita ja etsiin
// sopivat. Tama metodi palauttaa Yksikoiden valisen lisattavyyden.
double Yksikko::etsi_kohteen_lisattava(double lisattava, string lahto,
                                  string kohde, vector<Yksikko> kaikki_yksikot,
                                  vector<string> lapi_kaydyt){

    // Tutkii onko kyseinen Yksikko jo tutkittu.
    bool onko_jo_keratty{false};
    for(unsigned int etsija{0};etsija != lapi_kaydyt.size();etsija++){
        if (lapi_kaydyt[etsija] == nimi_) {
            onko_jo_keratty = true;
            break;
        }
    }
    if (onko_jo_keratty == false){

        // Tutkii onko kyseinen yksikko juuri se haluttu kohdeyksikko jota
        // etsitaan, jos on palautetaan sen lisattava maara.
        for(unsigned int indeksi{0};indeksi != kohdeyksikot_.size();indeksi++){
            if(kohdeyksikot_[indeksi].vertaa_nimea(kohde)){
                lisattava = lisattava + kohdeyksikot_[indeksi]
                        .palauta_lisattava();

                return lisattava;
            }
        }

        lapi_kaydyt.push_back(lahto);

        // Etsitaan niin kauvan kuin oikea kohdeyksikko loytyy, josta paastaan
        // palaamaan pois.
        for(unsigned int indeksi{0};indeksi != kohdeyksikot_.size();indeksi++){
            for(unsigned int i{0};i != kaikki_yksikot.size(); i++){
                for(unsigned int i2{0};i2 != lapi_kaydyt.size();i2++){

                    if((kaikki_yksikot[i].vertaa_yksikon_nimea(
                        kohdeyksikot_[indeksi].tulosta())
                        && (!kohdeyksikot_[indeksi]
                        .vertaa_nimea(lapi_kaydyt[i2])))){

                        double sopivan_kohdeyksikon_lisattava
                                = kohdeyksikot_[indeksi].palauta_lisattava();

                        lisattava = lisattava + sopivan_kohdeyksikon_lisattava;

                        return kaikki_yksikot[i].etsi_kohteen_lisattava
                           (lisattava, kaikki_yksikot[i].tulosta_yksikon_nimi(),
                            kohde, kaikki_yksikot, lapi_kaydyt);
                    }
                }
            }
        }
        return lisattava;
    }
    else{
        return lisattava;
    }
}


// Tutkii onko kohdeyksikoilla lainkaan lisattavyytta(lisattava != 0)
// Ja palauttaa ne yksikot vektorissa joilla sita on.
vector<string> Yksikko::kohdeyksikoiden_lisattavyys(vector<string> jo_lisatyt){

    for( auto kohdeyksikko : kohdeyksikot_ ){
        if( kohdeyksikko.onko_lisattavyytta() ){
            if( jo_lisatyt.size() == 0 ){
                jo_lisatyt = kohdeyksikko
                        .lisaa_kohdeyksikko_vectoriin(jo_lisatyt);
            }
            else{
                for(auto string : jo_lisatyt){
                    if(!kohdeyksikko.vertaa_nimea(string)){
                        jo_lisatyt = kohdeyksikko.lisaa_kohdeyksikko_vectoriin(jo_lisatyt);
                        break;
                    }
                }
            }
        }
    }
    return jo_lisatyt;
}

