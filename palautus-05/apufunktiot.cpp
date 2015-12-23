#include "apufunktiot.hh"
#include "kohdeyksikko.hh"
#include "yksikko.hh"
#include "stdlib.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

// Apufunktioita, joita kaytetaan apuna ohjelman suorituksessa.

using namespace std;

// Funktio lukee tekstitiedostosta muunnoskaavoja ja tekee niista Yksikoita
// ja Yksikoiden kohdeyksikoita, ja sijoittaa nama Yksikot vektoriin 
// "Kaikki_yksikot"
vector<Yksikko> lue_muunnoskaaviot( string tiedoston_nimi ){
    string rivi;
    ifstream kaaviot;
    vector<Yksikko> kaikki_yksikot;
    kaaviot.open( tiedoston_nimi );

    if (kaaviot.is_open()){

        // Kaydaan lapi jokainen tiedoston rivi erikseen.
        while (getline (kaaviot, rivi)){
            string kohdeyksikko;
            string lahtoyksikko;
            double lisattava{0};
            double suhde{1.0};

            if ( tarkista_rivi(rivi) ){
                if(tarkista_lahto_ja_kohde(rivi)){
                    string valilyonniton = poista_valilyonnit(rivi);

                    // Splitataan kaavio kohdasta '='.
                    // Esim C<=1.0*K-273.15  muuttuu
                    // C<    ja    1.0*K-273.15
                    vector<string> kaavio = split( valilyonniton, '=' );

                    kohdeyksikko = kaavio[0];
                    // Poistetaan kohdeyksikon lopusta merkki '<'.
                    kohdeyksikko.pop_back();


                    // Nyt splitataan kaavion jalkiosa kohdasta '*'
                    // Esim 1.0*K-273.15   muuttuu
                    // 1.0    ja    K-273.15
                    vector<string> rivin_loppuosa = split( kaavio[1], '*' );

                    // std::stringing funktio "stod" muutti stringing "1.123"
                    // double "1" joten vaihdetaan pisteet pilkuiksi jolloin
                    // doubleksi tuleekin haluttu "1.123"
                    string str_suhde = piste_pilkuksi( rivin_loppuosa[0] );
                    suhde = stod( str_suhde );
                    lahtoyksikko = rivin_loppuosa[1];

                    if (onko_lisattavaa( rivin_loppuosa[1] )){
                        for( char& c : rivin_loppuosa[1] ){
                            if ( c == '+' || c == '-' ){
                                vector<string> lahtoyksikko_ja_lisattava =
                                        split( rivin_loppuosa[1], c );

                                lahtoyksikko = lahtoyksikko_ja_lisattava[0];
                                if( c == '-' ){
                                    lisattava =
                                            -stod( lahtoyksikko_ja_lisattava[1] );
                                }
                                else{
                                    lisattava = stod(lahtoyksikko_ja_lisattava[1]);
                                }
                            }
                        }
                        kaikki_yksikot = lisaa_kaava(kohdeyksikko, lahtoyksikko,
                                                 suhde, lisattava, kaikki_yksikot);
                    }
                }
                else{
                    cout<< "Virhe: Tiedostossa lahto- tai kohdeyksikon nimessa"
                           "virheita\n";
                    lopeta_ohjelma();
                }
            }
        }
        kaaviot.close();
    }
    else {
        cout << "Virhe: Kaavio tiedostoa ei saatu luettua.\n";
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


// Palauttaa boolean arvon true, jos tarkistettava merkki on joko
// # tai \n.
bool tarkista_rivin_vaihto(char c){
    if ( c == '#' || c == '\n' ){
        return true;
    }
    else {
        return false;
    }
}


// Tarkistaa onko merkki valilyonti vai ei.
bool onko_valilyonti(char c){
    if ( c == ' ' ){
        return true;
    }
    else {
        return false;
    }
}


// Tarkistaa rivilta onko selattava kirjain valilyonti tai
// kommentti (#) tai rivin vaihto. Jos jokin naista
// tulee ennen kirjainta, palautetaan false. Muulloin
// palautetaan true.
bool tarkista_rivi(string rivi){
    for( char& c : rivi ) {
        if ( onko_valilyonti(c) == false ){

            if( tarkista_rivin_vaihto(c) == false ){
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}


// Tarkistaa onko rivi muotoa yksikko kerroin yksikko ja lisattava
bool tarkista_lahto_ja_kohde(string rivi){
    string lahtoyksikko;
    string kohdeyksikko;
    
    // Luodaan lahtoyksikko.
    for ( char& c : rivi){
        if( c == ' '){
            rivi.erase(0);
        }
        else if ( c != '<'){
            lahtoyksikko = lahtoyksikko + c;
            rivi.erase(0);
        }
        else if( c == '<' ){
            rivi.erase(0);
            rivi.erase(0);
            break;
        }
    }
    
    // Luodaan kerroin.
    for( char& c : rivi ){
        if( c == ' ' ){
            rivi.erase(0);
        }
        else if ( c != '*' ){
            rivi.erase(0);
        }
        else if( c == '*' ){
            rivi.erase(0);
            break;
        }
    }
    
    // Luodaan kohdeyksikko
    for ( char& c : rivi ){
        if( c == ' ' ){
            rivi.erase(0);
        }
        else if ( c != '+' && c != '-' && c != '\n' ){
            kohdeyksikko = kohdeyksikko + c;
            rivi.erase(0);
        }
        else if( c == '+' || c == '-' || c == '\n' ){
            rivi.erase(0);
            break;
        }
    }
    return tarkista_yksikon_kirjaimet(lahtoyksikko, kohdeyksikko);
}


// Tarkistaa onko lahto- ja kohdeyksikoissa oikeat kirjaimet
// (a-z, A-Z seka '/')
bool tarkista_yksikon_kirjaimet(string lahtoyksikko, string kohdeyksikko){
    vector<char> sopivat_kirjaimet{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                                  'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                                  'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
                                  'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
                                  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                  'W', 'X', 'Y', 'Z', '/' };
    for (char& c : lahtoyksikko){
        if ( sopivat_kirjaimet.end() == find(sopivat_kirjaimet.begin(),
                       sopivat_kirjaimet.end(), c)){
            return false;
        }
    }

    for (char& c : kohdeyksikko){
        if ( sopivat_kirjaimet.end() == find(sopivat_kirjaimet.begin(),
                                             sopivat_kirjaimet.end(), c)){
            return false;
        }
    }
    return true;
}

// Poistaa rivilta valilyonnit.
string poista_valilyonnit(string rivi){
    string valilyonniton_rivi;

    for( char& c : rivi ) {
        if( onko_valilyonti(c) == false ){
            valilyonniton_rivi += c;
        }
    }
    return valilyonniton_rivi;
}


// Tarkistaa onko rivilla "lisattavaa" eli onko siina plus tai miinus
// merkkia.
bool onko_lisattavaa(string rivi){
    if ( rivi.find('-') || rivi.find('+') ){
        return true;
    }
    else {
        return false;
    }
}

// Lisaa Yksikoiden valiset kaavat vektoriin kaikki_yksikot.
vector<Yksikko> lisaa_kaava(string kohdeyksikko, string lahtoyksikko,
                            double suhde, double lisattava,
                            vector<Yksikko> kaikki_yksikot){

    bool kohdeyksikko_olemassa{onko_yksikko_olemassa(kohdeyksikko,
                                                     kaikki_yksikot)};
    bool lahtoyksikko_olemassa{onko_yksikko_olemassa(lahtoyksikko,
                                                     kaikki_yksikot)};

    if( onko_kaava_olemassa(lahtoyksikko, kohdeyksikko, kaikki_yksikot) ){
        cout<<"Virhe: Tiedostossa on samat kaavat useasti.\n";
        lopeta_ohjelma();
    }
    else{
        // Luodaan tai paivitetaan parametrin kohdeyksikon "kohdeyksikot"
        // listaa.
        if( !kohdeyksikko_olemassa ){
            // Tassa luodaan uusi lista uudelle yksikolle.
            Yksikko uusi_kohdeyksikko(kohdeyksikko);

            // Muutetaan lisattava lukumaara oikeanlaiseksi jakamalla
            // se suhteella.
            double korjattu_lisattava = lisattava / suhde;

            uusi_kohdeyksikko.lisaa_kohdeyksikko(lahtoyksikko, suhde,
                                                 korjattu_lisattava, true);

            // Lisataan luotu Yksikko vectoriin.
            kaikki_yksikot.push_back(uusi_kohdeyksikko);
        }
        else{
            // Tassa paivitetaan jo olemassaolevan yksikon "kohdeyksikot"
            // listaa. Ensin se etsitaan while loopilla.
            unsigned int indeksi{0};
            while(indeksi != kaikki_yksikot.size()){
                if(kaikki_yksikot[indeksi].vertaa_yksikon_nimea(kohdeyksikko)){

                    // Muutetaan lisattava lukumaara oikeanlaiseksi jakamalla
                    // se suhteella.
                    double korjattu_lisattava = lisattava / suhde;

                    kaikki_yksikot[indeksi].lisaa_kohdeyksikko(lahtoyksikko,
                                              suhde, korjattu_lisattava, true);
                }
                indeksi++;
            }
        }


        if(!lahtoyksikko_olemassa){
            // Tassa luodaan uusi lista uudelle yksikolle.
            Yksikko uusi_lahtoyksikko(lahtoyksikko);
            uusi_lahtoyksikko.lisaa_kohdeyksikko(kohdeyksikko, suhde,
                                                 lisattava, false);

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
    }
    return kaikki_yksikot;
}


// Funktio vaihtaa kaikki rivin pisteet pilkuiksi.
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


// Funktio tarkistaa onko rivilla vain numeroita tai pisteita tai pilkkuja.
bool onko_vain_numeroita(string numero){
    vector<char> numerot_ja_piste_tai_pilkku{'0', '1', '2', '3', '4', '5',
                                             '6', '7', '8', '9', '.', ','};
    for(char& c : numero){
        if(find(numerot_ja_piste_tai_pilkku.begin(),
                    numerot_ja_piste_tai_pilkku.end(), c)
                    == numerot_ja_piste_tai_pilkku.end()){
            cout<<c<<endl;
            return false;
        }
    }
    return true;
}


// Funktio tarkistaa kaikista yksikoista onko kyseista yksikkoa jo olemassa.
bool onko_yksikko_olemassa(string yksikon_nimi,
                           vector<Yksikko> kaikki_yksikot){

    for (auto yksikko : kaikki_yksikot){
        if(yksikko.vertaa_yksikon_nimea(yksikon_nimi)){
            return true;
        }
    }
    return false;
}


// Funktio tarkistaa kiakista yksikoista onko kyseista kaavaa jo olemassa
// yksikoiden valilla.
bool onko_kaava_olemassa(string lahto, string kohde,
                         vector<Yksikko> kaikki_yksikot){

    for (auto yksikko : kaikki_yksikot){
        if (yksikko.vertaa_yksikon_nimea(lahto) &&
                yksikko.loytyyko_kohdeyksikko(kohde)){

            return true;
        }
        else if (yksikko.vertaa_yksikon_nimea(kohde) &&
                 yksikko.loytyyko_kohdeyksikko(lahto)){

            return true;
        }
    }
    return false;
}


// Tiettyjen virhetilanteiden sattuessa ohjelma pitaa lopettaa ja tama
// funktio siis lopettaa ohjelman.
void lopeta_ohjelma(){
    exit(0);
}
