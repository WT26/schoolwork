#include "paivyri.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <map>

using namespace std;

// Rakentaja metodi.
Paivyri::Paivyri() {
}

// Lisataan uusi tapahtuma Paivyriin.
bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {

    // Luodaan uusi Paivays.
    Paivays lisattava_paivays;
    string lisatty = lisaa_nollat(lisattava_paivays.merkkijonoksi(paivamaara));

    lisattava_paivays = Paivays(lisatty);

    // Tutkitaanko onko kyseista paivaysta paivyrissa. Jos se on, ei
    // luoda uutta.
    if (paivyridata_.find(lisatty) != paivyridata_.end()){
        paivyridata_[lisatty].push_back(kuvaus);
    }

    else {
    // Ja tassa luodaan uusi ellei sita ole viela olemassa.
        deque<string> lisattava_jono;
        lisattava_jono.push_back(kuvaus);
        paivyridata_[lisatty].push_back(kuvaus);

    }
    return true;
}


// Metodi tulostaa paivyridatan.
bool Paivyri::tulosta_paivyridata(){

    if (paivyridata_.begin() == paivyridata_.end()){
        return false;
    }
    else {
        map<Paivays, deque<string>>::iterator map_iter;
        deque<string>::iterator deque_iter;

        map_iter = paivyridata_.begin();

        // Kaydaan lapi kaikki Paivaykset ja tulostetaan paivamaara.
        while (map_iter != paivyridata_.end()){

            cout<<  lisaa_nollat(map_iter->first.merkkijonoksi())<<endl;
            deque_iter = map_iter->second.begin();

            // Tulostetaan kaikki paivamaaralle kirjatut tapahtumat.
            while(deque_iter != map_iter->second.end()){
                cout<<"    "<<*deque_iter<<endl;
                deque_iter++;
            }

            map_iter++;
        }
    }
    return true;
}


// Tulostaa vain tietyn paivamaaran tapahtumat (komento nayta)
bool Paivyri::tulosta_merkinnat(const string paivamaara) {
    if (paivyridata_.find(paivamaara) == paivyridata_.end()){
        return false;
    }
    else {
        map<Paivays, deque<string>>::iterator map_iter;
        deque<string>::iterator deque_iter;

        map_iter = paivyridata_.find(paivamaara);
        cout<<lisaa_nollat(map_iter->first.merkkijonoksi())<<endl;
        deque_iter = map_iter->second.begin();

        while(deque_iter != map_iter->second.end()){
            cout<<"    "<<*deque_iter<<endl;
            deque_iter++;
        }
     return true;
    }
}

// Poistaa tietylta paivamaaralta ensimmaisen tapahtuman.
bool Paivyri::poista_tapahtuma(const string paivamaara) {
    if (paivyridata_.find(paivamaara) == paivyridata_.end()){
        cout<<"Paivamaarana ei ole poistettavaa merkintaa."<<endl;
        return false;
    }
    else{
        map<Paivays, deque<string>>::iterator map_iter;
        deque<string>::iterator deque_iter;

        map_iter = paivyridata_.find(paivamaara);
        deque_iter = map_iter->second.begin();
        map_iter->second.pop_front();
    }
}

// Poistaa tyhjan Paivayksen.
bool Paivyri::poista_tyhja_paivays(const string paivamaara) {
    if (paivyridata_.find(paivamaara) == paivyridata_.end()) {
        paivyridata_.erase(paivamaara);
        return true;
    }
    else {
        return false;
    }
}

// Tallettaa Paivyrin tiedot .txt tiedostoon.
bool Paivyri::talleta_tiedosto(const string paivyritiedoston_nimi){
    ofstream tiedosto_olio{paivyritiedoston_nimi};

    map<Paivays, deque<string>>::iterator map_iter;
    deque<string>::iterator deque_iter;

    map_iter = paivyridata_.begin();
    deque_iter = map_iter->second.begin();

    while (map_iter != paivyridata_.end()){

        deque_iter = map_iter->second.begin();

        // Talletetaan kaikki paivamaaralle kirjatut tapahtumat.
        while(deque_iter != map_iter->second.end()){
            tiedosto_olio<< map_iter->first.merkkijonoksi()<<":";
            tiedosto_olio<<*deque_iter<<"\n";
            deque_iter++;
        }

        map_iter++;
    }
}

// Metodi lisaa paivamaaran eteen tarvittaessa etunollat.
const string Paivyri::lisaa_nollat(const string paivamaara){

    // Vectori ppkkvvvv sisaltaa paivamaaran tiedot: paiva on vectorin ensimmainen
    // stringi, kuukausi toinen ja vuosi kolmas. Nain saadaan muuttamalla vectoria kohdassa
    // nolla muutettua paivaa(lisataan eteen tarvittaessa nolla) etc.
    vector<string> ppkkvvvv = split(paivamaara,'.');

    // Paivaan lisataan tarvittaessa nolla.
    if(ppkkvvvv.at(0).length() < 2) {
        string lisattava_pp = "0" + ppkkvvvv.at(0);
        ppkkvvvv.insert(ppkkvvvv.begin(), lisattava_pp);
        ppkkvvvv.erase(ppkkvvvv.begin() + 1);
    }

    // Kuukauteen lisataan tarvittaessa nolla.
    if(ppkkvvvv.at(1).length() < 2) {
        string lisattava_kk = "0" + ppkkvvvv.at(1);
        ppkkvvvv.insert(ppkkvvvv.begin()+ 1, lisattava_kk);
        ppkkvvvv.erase(ppkkvvvv.begin() + 2);
    }
    const string nollat_lisatty = ppkkvvvv.at(0)+ "." + ppkkvvvv.at(1) + "." + ppkkvvvv.at(2);
    return nollat_lisatty;
}


// Muita Paivyri-luokan metodifunktioiden määrittelyjä puuttuu tästä.
