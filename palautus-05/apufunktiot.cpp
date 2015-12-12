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

            // Kaydaan lapi jokainen rivilla oleva kirjain erikseen
            // ja tarkastetaan onko ne sopivia.
            for(char& c : rivi) {
                if (tarkista_rivin_vaihto(c) == false){
                    if (onko_valilyonti(c) == true){
                        break;
                    }
                    else {
                        cout << rivi << endl;
                    }
                }
                else {
                    break;
                }
            }
        }
        kaaviot.close();
    }
    else {
        cout << "Virhe: Kaavio tiedostoa ei saatu luettua." << endl;
    }
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
