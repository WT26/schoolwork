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


using namespace std;

int main()
{

    int ohjelma_kaynnissa{1};

    while (ohjelma_kaynnissa == 1) {
        deque<Pala> pala_jono;
        string tiedoston_nimi{""};
        vector<int> palojen_laitojen_numerot;
        bool vaara_numerojen_lukumaara = true;



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
                            for(int i{0};i != 4;i++){
                                if(stoi(pala_vektori.at(i)) != 0){
                                    palojen_laitojen_numerot.push_back(stoi(pala_vektori.at(i)));
                                }
                            }
                            pala_jono.push_back(Pala(pala_vektori));
                        }
                    }
                    map<int, int> numerojen_lukumaara;
                    for(int i{0};i != palojen_laitojen_numerot.size();i++){

                        if(numerojen_lukumaara.count(palojen_laitojen_numerot.at(i))){
                            numerojen_lukumaara[palojen_laitojen_numerot.at(i)]++;
                            for(int a{0};a!=numerojen_lukumaara.size();a++){
                            }
                        }
                        else {
                            numerojen_lukumaara[palojen_laitojen_numerot.at(i)] = 1;
                        }
                    }
                    for(int a{1};a != numerojen_lukumaara.size() + 1;a++){
                        if((numerojen_lukumaara[a] != 2) && (numerojen_lukumaara[a] != 0)
                                && (numerojen_lukumaara[a] != 1)){
                            cout<<"virhe: joidenkin palojen laitoja enemman kuin kaksi"<<endl;
                            vaara_numerojen_lukumaara = false;
                            break;
                        }
                    }
                    bool aloituspala_loytyy = false;
                    int aloitus_paloja{0};
                    int kulma_paloja{0};
                    for(int i{0};i != pala_jono.size(); i++){
                        if (pala_jono.at(i).onko_aloituspala()){
                            aloituspala_loytyy = true;
                            aloitus_paloja++;
                        }
                        if (pala_jono.at(i).onko_kulmapala()){
                            kulma_paloja++;
                        }
                    }
                    if (aloituspala_loytyy == true){
                        if(aloitus_paloja == 1){
                            if(kulma_paloja == 4){
                                if(vaara_numerojen_lukumaara == true){
                                    Palapeli palapeli(pala_jono);
                                    if(palapeli.jarjesta() == true){
                                        palapeli.tulosta();
                                    }
                                }
                            }
                            else {
                                cout<<"virhe: kulmapaloja vaara maara"<<endl;
                            }
                        }
                        else {
                            cout<<"virhe: liian monta aloituspalaa"<<endl;
                        }

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

