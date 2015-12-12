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
        while (getline (kaaviot, rivi)){
            cout<<rivi<<endl;
        }
        kaaviot.close();
    }
    else {
        cout << "Virhe: Kaavio tiedostoa ei saatu luettua." << endl;
    }
}

