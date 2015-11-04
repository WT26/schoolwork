#include "paivyri.hh"
#include <iostream>
#include <string>
#include <deque>
#include <map>

using namespace std;

Paivyri::Paivyri() {
}

bool Paivyri::lisaa_tapahtuma(const string& paivamaara, const string& kuvaus) {


    Paivays lisattava_paivays = Paivays(paivamaara);

    // Tutkitaanko onko kyseista paivaysta paivyrissa
    if (paivyridata_.find(lisattava_paivays) != paivyridata_.end()){
        paivyridata_[paivamaara].push_back(kuvaus);
    }

    else {
        deque<string> lisattava_jono;
        lisattava_jono.push_back(kuvaus);
        //paivyridata_[paivamaara] = deque<string>;
        paivyridata_[paivamaara].push_back(kuvaus);
    }
    //DEBUG
    cout<<paivamaara<<endl;
    cout<<kuvaus<<endl;
    const string& paivamaara2 = "23.6.2016";
    cout<<paivyridata_[paivamaara2].at(0)<<endl;

    // Lisätään «paivamaara»:lle tapahtuma «kuvaus» luokan
    // private-osassa olevaan säiliöön.

    return true;
}




// Muita Paivyri-luokan metodifunktioiden määrittelyjä puuttuu tästä.
