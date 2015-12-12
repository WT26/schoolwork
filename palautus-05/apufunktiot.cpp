#include "apufunktiot.hh"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void lue_muunnoskaaviot(){
    string rivi;
    ifstream kaaviot;
    kaaviot.open("saannot.txt");

    if (kaaviot.is_open()){

        // Kaydaan lapi jokainen tiedoston rivi erikseen.
        while (getline (kaaviot, rivi)){
            string kohdeyksikko;
            string lahtoyksikko;
            double lisattava{0};


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
                double suhde = stod(rivin_loppuosa[0]);

                if (onko_lisattavaa(rivin_loppuosa[1])){

                }
            }
        }
        kaaviot.close();
    }
    else {
        cout << "Virhe: Kaavio tiedostoa ei saatu luettua." << endl;
    }
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
