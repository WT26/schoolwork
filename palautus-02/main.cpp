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
#include <map>
#include <set>


using namespace std;

int main()
{
    deque<Pala> pala_jono;
    int ohjelma_kaynnissa{1};

    set<int> palojen_numerot;
    //map<int, Pala> pala_hakemisto;

    while (ohjelma_kaynnissa == 1) {
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
                    }
                    Palapeli palapeli(pala_jono);
                    palapeli.jarjesta();

                }
        }
        catch(exception const){
                return false;
        }



/*
        } elif tiedoston_ni

            if ( komento[0] == "pala" ){
                int palan_numero;
                palan_numero = stoi(komento[1]); //Muutetaan pala komennon (palan numero) osa str->int
                if ( palan_numero != 1 and palan_numero !=2 ) {
                    cout << "Virhe: Palan numero voi olla vain 1 tai 2" << endl;
                } else {
                    if ( palojen_numerot.find( palan_numero ) == palojen_numerot.end() ){
                        palojen_numerot.insert( palan_numero );
                        vector<string> palan_tiedot = split( komento[2], ':' );

                        if ( tarkista_tiedot(palan_tiedot) == true ) {
                            pala_hakemisto.insert( { palan_numero, Pala(palan_tiedot ) } );
                            cout << "Pala "<< palan_numero << " asetettu." << endl;
                        }

                     } else { //Jos pala onkin jo hakemistossa, poistetaan vanha ja korvataan uudella
                        vector<string> palan_tiedot = split( komento[2], ':' );

                            if ( tarkista_tiedot(palan_tiedot) == true ) {
                            pala_hakemisto.erase( palan_numero );
                            pala_hakemisto.insert( { palan_numero, Pala( palan_tiedot ) } );
                            cout << "Pala "<< palan_numero << " asetettu." << endl;
                            }
                        }
                    }
                }

        }
        */
    }
}

