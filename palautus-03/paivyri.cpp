#include "paivyri.hh"
#include <iostream>
#include <string>
#include <deque>
#include <map>

using namespace std;

Paivyri::Paivyri() {
}

bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {

    Paivays lisattava_paivays;
    string oikeassa_formaatissa = lisattava_paivays.merkkijonoksi(paivamaara);

    //DEBUG
    cout<<paivamaara<<" paivamaara"<<endl;
    cout<<oikeassa_formaatissa<<" oikeassa formaatissa"<<endl;

    lisattava_paivays = Paivays(oikeassa_formaatissa);

    // Tutkitaanko onko kyseista paivaysta paivyrissa
    if (paivyridata_.find(lisattava_paivays) != paivyridata_.end()){
        paivyridata_[oikeassa_formaatissa].push_back(kuvaus);
    }

    else {

        deque<string> lisattava_jono;
        lisattava_jono.push_back(kuvaus);
        //paivyridata_[paivamaara] = deque<string>;
        paivyridata_[oikeassa_formaatissa].push_back(kuvaus);

    }

    return true;
}


bool Paivyri::tulosta_paivyridata(){

    map<Paivays, deque<string>>::iterator map_iter;
    deque<string>::iterator deque_iter;

    map_iter = paivyridata_.begin();

    // Kaydaan lapi kaikki Paivaykset ja tulostetaan paivamaara.
    while (map_iter != paivyridata_.end()){
        cout<< map_iter->first.merkkijonoksi()<<endl;

        deque_iter = map_iter->second.begin();

        // Tulostetaan kaikki paivamaaralle kirjatut tapahtumat.
        while(deque_iter != map_iter->second.end()){
            cout<<"    "<<*deque_iter<<endl;
            deque_iter++;
        }

        map_iter++;
    }
}





// Muita Paivyri-luokan metodifunktioiden määrittelyjä puuttuu tästä.
