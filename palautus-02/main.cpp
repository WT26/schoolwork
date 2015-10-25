// TIE-02200 Ohjelmoinnin peruskurssi, syksy 2015
// Harjoitustehtava 2
// 246479 joel.alanko@student.tut.fi ()

#include "apufunktiot.hh"
#include "pala.hh"
#include "palapeli.hh"
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque>


using namespace std;

int main()
{

    int ohjelma_kaynnissa{1};

    while (ohjelma_kaynnissa == 1) {
        deque<Pala> pala_jono;
        string tiedoston_nimi{""};

        cout << "Luettava tiedosto ";
        getline(cin, tiedoston_nimi);

        if ( tiedoston_nimi == "" ){
            return 0;
        }
        try {
                ifstream tiedosto_olio{tiedoston_nimi};
                if ( not tiedosto_olio ) {
                    cout<<"Virhe: tiedoston nimi vaarin"<<endl;

                } else {
                    string rivi;
                    while (getline(tiedosto_olio, rivi)) {
                        string rivi_string = rivi;
                        string tarkistettu = tarkista_tiedot(rivi_string);

                        //tarkistetaan onko tiedoston tiedot syotetty oikein.
                        if (tarkistettu != "virhe") {
                            vector<string> pala_vektori = split(tarkistettu, ':');
                            pala_jono.push_back(Pala(pala_vektori));
                        }
                        else {
                            cout<<"virhe:"<<endl;
                        }
                    }
                    bool aloituspala_loytyy = false;
                    for(int i{0};i != pala_jono.size(); i++){
                        if (pala_jono.at(i).onko_aloituspala()){
                            aloituspala_loytyy = true;
                        }
                    }
                    if (aloituspala_loytyy == true){
                        Palapeli palapeli(pala_jono);
                        palapeli.jarjesta();
                        palapeli.tulosta();
                    }
                    else {
                        cout<<"virhe: aloituspalaa ei loydy"<<endl;
                    }


                }
        }
        catch(exception const){
                return false;
        }
    }

}

