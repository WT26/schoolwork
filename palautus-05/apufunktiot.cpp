#include "apufunktiot.hh"
#include "kohdeyksikko.hh"
#include "yksikko.hh"
#include "stdlib.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

vector<Yksikko> lue_muunnoskaaviot(string tiedoston_nimi){
    string rivi;
    ifstream kaaviot;
    vector<Yksikko> kaikki_yksikot;
    kaaviot.open(tiedoston_nimi);

    if (kaaviot.is_open()){

        // Kaydaan lapi jokainen tiedoston rivi erikseen.
        while (getline (kaaviot, rivi)){
            string kohdeyksikko;
            string lahtoyksikko;
            double lisattava{0};
            double suhde{1.0};

            if (tarkista_rivi(rivi)){
                string valilyonniton = poista_valilyonnit(rivi);

                // Splitataan kaavio kohdasta '='.
                // Esim C<=1.0*K-273.15  muuttuu
                // C<    ja    1.0*K-273.15
                vector<string> kaavio = split(valilyonniton, '=');

                kohdeyksikko = kaavio[0];
                // Poistetaan kohdeyksikon lopusta merkki '<'.
                kohdeyksikko.pop_back();


                // Nyt splitataan kaavion jalki osa kohdasta '*'
                // Esim 1.0*K-273.15   muuttuu
                // 1.0    ja    K-273.15
                vector<string> rivin_loppuosa = split(kaavio[1], '*');

                // std::stringing funktio "stod" muutti stringing "1.123"
                // double "1" joten vaihdetaan pisteet pilkuiksi jolloin
                // doubleksi tuleekin haluttu "1.123"
                string str_suhde = piste_pilkuksi(rivin_loppuosa[0]);
                suhde = stold(str_suhde);
                lahtoyksikko = rivin_loppuosa[1];
                if (onko_lisattavaa(rivin_loppuosa[1])){
                    for(char& c : rivin_loppuosa[1]){
                        if (c == '+' || c == '-'){
                            vector<string> lahtoyksikko_ja_lisattava =
                                    split(rivin_loppuosa[1], c);

                            lahtoyksikko = lahtoyksikko_ja_lisattava[0];
                            if(c == '-'){
                                lisattava =
                                        -stod(lahtoyksikko_ja_lisattava[1]);
                            }
                            else{
                                lisattava = stod(lahtoyksikko_ja_lisattava[1]);
                            }
                        }
                    }
                    //cout<<"Kohdeyksikko: "<<kohdeyksikko<<"  Lahtoyksikko: "<<
                     //     lahtoyksikko<<"  suhde: "<<suhde<<"  lisattavaa: "<<
                      //    lisattava<<endl;
                    kaikki_yksikot = lisaa_kaava(kohdeyksikko, lahtoyksikko, suhde,
                                                 lisattava, kaikki_yksikot);
                }
            }
        }
        kaaviot.close();
    }
    else {
        cout << "Virhe: Kaavio tiedostoa ei saatu luettua." << endl;
    }
    return kaikki_yksikot;
}


// Vanha tuttu split.
vector<string> split(const string& merkkijono, char erotinmerkki) {
    vector<string> tulos;

    string::size_type tutkittava_kohta{0};
    string kentan_sisalto{""};

    while ( tutkittava_kohta < merkkijono.length() ) {

        if ( merkkijono.at(tutkittava_kohta) != erotinmerkki ) {
            kentan_sisalto.push_back( merkkijono.at(tutkittava_kohta) );

        } else {

            tulos.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }

        ++tutkittava_kohta;
    }

    tulos.push_back(kentan_sisalto);

    return tulos;
}


bool tarkista_rivin_vaihto(char c){
    if (c == '#' || c == '\n'){
        return true;
    }
    else {
        return false;
    }
}


bool onko_valilyonti(char c){
    if (c == ' '){
        return true;
    }
    else {
        return false;
    }
}


bool tarkista_rivi(string rivi){
    for(char& c : rivi) {

        // Tarkistaa onko selattava kirjain valilyonti tai
        // kommentti (#) tai rivin vaihto. Jos jokin naista
        // tulee ennen kirjainta, palautetaan false. Muulloin
        // palautetaan true.
        if (onko_valilyonti(c) == false){
            if(tarkista_rivin_vaihto(c) == false){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}


string poista_valilyonnit(string rivi){
    string valilyonniton_rivi;

    for(char& c : rivi) {
        if(onko_valilyonti(c) == false){
            valilyonniton_rivi += c;
        }
    }
    return valilyonniton_rivi;
}


bool onko_lisattavaa(string rivi){
    if (rivi.find('-') || rivi.find('+')){
        return true;
    }
    else {
        return false;
    }
}


vector<Yksikko> lisaa_kaava(string kohdeyksikko, string lahtoyksikko,
                            double suhde, double lisattava,
                            vector<Yksikko> kaikki_yksikot){

    // Kaydaan lapi kaikki yksikot ja verrataan niita
    // parametreina saatuihin yksikoihin.
    bool kohdeyksikko_olemassa = false;
    bool lahtoyksikko_olemassa = false;

    for(auto indeksi : kaikki_yksikot){
        if(indeksi.vertaa_yksikon_nimea(kohdeyksikko)){
            kohdeyksikko_olemassa = true;
        }
    }

    for(auto indeksi : kaikki_yksikot){
        if(indeksi.vertaa_yksikon_nimea(lahtoyksikko)){
            lahtoyksikko_olemassa = true;
        }
    }

    bool onko_kaava_olemassa{false};

    for(auto indeksi : kaikki_yksikot){

    }

    if(onko_kaava_olemassa(lahtoyksikko, kohdeyksikko, kaikki_yksikot)){
        cout<<"Virhe: Tiedostossa on samat kaavat useasti.\n";

    }
    else{
        // Luodaan tai paivitetaan parametrin kohdeyksikon "kohdeyksikot" listaa.
        if(!kohdeyksikko_olemassa){
            // Tassa luodaan uusi lista uudelle yksikolle.
            Yksikko uusi_kohdeyksikko(kohdeyksikko);
            uusi_kohdeyksikko.lisaa_kohdeyksikko(lahtoyksikko, suhde, lisattava,
                                                 true);

            // Lisataan luotu Yksikko vectoriin.
            kaikki_yksikot.push_back(uusi_kohdeyksikko);
        }
        else{
            // Tassa paivitetaan jo olemassaolevan yksikon "kohdeyksikot"
            // listaa.
            unsigned int indeksi{0};
            while(indeksi != kaikki_yksikot.size()){
                if(kaikki_yksikot[indeksi].vertaa_yksikon_nimea(kohdeyksikko)){
                    kaikki_yksikot[indeksi].lisaa_kohdeyksikko(lahtoyksikko,
                                                    suhde, lisattava, true);
                }
                indeksi++;
            }
        }


        if(!lahtoyksikko_olemassa){
            // Tassa luodaan uusi lista uudelle yksikolle.
            Yksikko uusi_lahtoyksikko(lahtoyksikko);
            uusi_lahtoyksikko.lisaa_kohdeyksikko(kohdeyksikko, suhde, lisattava,
                                                 false);

            // Lisataan luotu Yksikko vectoriin.
            kaikki_yksikot.push_back(uusi_lahtoyksikko);
        }
        else{
            // Tassa paivitetaan jo olemassaolevan lahtoyksikon "kohdeyksikot"
            // listaa.
            unsigned int indeksi{0};
            while(indeksi != kaikki_yksikot.size()){
                if(kaikki_yksikot[indeksi].vertaa_yksikon_nimea(lahtoyksikko)){
                    kaikki_yksikot[indeksi].lisaa_kohdeyksikko(kohdeyksikko,
                                                    suhde, lisattava, false);
                }
                indeksi++;
            }
        }

        return kaikki_yksikot;
    }
}


string piste_pilkuksi(string desimaali){
    string uusi_desimaali;
    for(auto c : desimaali){
        if(c == '.'){
            uusi_desimaali += ",";
        }
        else {
            uusi_desimaali += c;
        }
    }
    return uusi_desimaali;
}


bool onko_vain_numeroita(string numero){
    vector<char> numerot_ja_piste_tai_pilkku{'0', '1', '2', '3', '4', '5',
                                             '6', '7', '8', '9', '.', ','};
    for(auto c : numero){
        if(find(numerot_ja_piste_tai_pilkku.begin(),
                    numerot_ja_piste_tai_pilkku.end(), c)
                    != numerot_ja_piste_tai_pilkku.end()){
            return false;
        }
    }
    return true;
}


bool onko_kaava_olemassa(string lahto, string kohde, vector<Yksikko> kaikki_yksikot){
    for (auto yksikko : kaikki_yksikot){
        if (yksikko.vertaa_yksikon_nimea(lahto) && yksikko.loytyyko_kohdeyksikko(kohde)){
            return true;
        }
        else if (yksikko.vertaa_yksikon_nimea(kohde) && yksikko.loytyyko_kohdeyksikko(lahto)){
            return true;
        }
    }
    return false;
}
