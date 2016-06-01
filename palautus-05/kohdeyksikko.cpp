#include "kohdeyksikko.hh"
#include <string>
#include <iostream>
#include <vector>

// Luokka, jota hyodynnetaan kaavojen sailomisessa. Kohdeyksikko on jonkun
// yksikon sellainen yksikko, jonka muunnos tiedetaan. Muunnokseen liittyvat
// yksikoiden suhde, suunta seka tarvittaessa lisattava luku. Suunta tarkoittaa
// sita etta kerrotaanko yksikko muunnosvaiheessa vai jaetaanko, eli kumpaan
// suuntaan muunnosta halutaan tehda.

using namespace std;

Kohdeyksikko::Kohdeyksikko( string yksikon_nimi, double suhde,
                            double lisattava, bool suunta )
{
    yksikko_ = yksikon_nimi;
    suhde_ = suhde;
    lisattava_ = lisattava;
    suunta_ = suunta;
}


// Ohjelmointi tyylillisesti erittain huono ratkaisu. Tata metodia kutsutaan
// vain Yksikon etsi-metodeissa. Kiersin parhaani mukaan kaikki vaiheet
// alempana olevalla "vertaa_nimea" metodilla, mutta rekursiivinen haku
// tarvitsi tata tietoa parametrina joten se oli pakko toteuttaa nain.
// Yksi vaihtoehto mika tuli mieleen oli koko taman luokan muodostaminen
// vain structina, mutta aika ei riittanyt sen suunnitteluun. Tasta syysta
// laitoin string yksikko_:n publiciksi.
string Kohdeyksikko::tulosta(){
    return yksikko_;
}


// Keraa kohdeyksikot jotka eivat ole viela vectorissa "loytyy_listasta" ja
// palauttaa vectorin taydennettyna.
vector<string> Kohdeyksikko::keraa_kohdeyksikot(
        vector<string> loytyy_listasta ){
    bool loytyy_listalta{false};
    unsigned int indeksi{0};
    while( indeksi != loytyy_listasta.size() ){
        if ( loytyy_listasta[indeksi] == yksikko_ ){
            loytyy_listalta = true;
        }
        indeksi++;
    }
    if( loytyy_listalta == false ){
        loytyy_listasta.push_back( yksikko_ );
        return loytyy_listasta;
    }
    else{
        return loytyy_listasta;
    }
}


// Vertaa parametrina saatua nimea oman yksikon nimeen ja palauttaa
// sen mukaan boolean arvon.
bool Kohdeyksikko::vertaa_nimea( string verrattava ){
    if( verrattava == yksikko_ ){
        return true;
    }
    else{
        return false;
    }
}



// Palauttaa Yksikon ja kohdeyksikon valisen suhteen suunnan avulla.
// Jos suunta on true, suhde on yksikoiden valilla painvastainen eli
// 1 jaetaan suhteella, ja suunnan ollessa false se kerrotaan 1:llä.
double Kohdeyksikko::palauta_suhde(){
    if ( suunta_ == true ){
        double palautettava = 1 / suhde_;
        return palautettava;
    }
    else{
        double palautettava = 1 * suhde_;
        return palautettava;
    }
}


// Samalla menetelmalla kuin ylempana suhde, palautetaan yksikoiden valinen
// lisattavyys-suhde. Lisays voi olla miinusmerkkista.
double Kohdeyksikko::palauta_lisattava(){
    if ( suunta_ == true ){
        double palautettava = 0 - lisattava_;
        return palautettava;
    }
    else{
        double palautettava = 0 + lisattava_;
        return palautettava;
    }
}


// Tutkii onko yksikon ja kohdeyksikon valilla lisattavia lukumaaria.
bool Kohdeyksikko::onko_lisattavyytta(){
    if( lisattava_ == 0 ){
        return false;
    }
    else {
        return true;
    }
}


// Lisaa kohdeyksikon nimen vectoriin ja palauttaa sen.
vector<string> Kohdeyksikko::lisaa_kohdeyksikko_vectoriin(
                                                vector<string> lista ){
    lista.push_back( yksikko_ );
    return lista;
}
