#include "pala.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

Pala::Pala(vector<string> palan_tiedot):
    ylalaita_{ stoi(palan_tiedot[0]) },
    oikea_laita_{ stoi(palan_tiedot[1]) },
    alalaita_{ stoi(palan_tiedot[2]) },
    vasen_laita_{stoi(palan_tiedot[3]) },
    kryk_{ palan_tiedot[4] }
{
}

void Pala::tulosta() const{
    cout << "ylos:" << ylalaita_ << endl;
    cout << "oikea:" << oikea_laita_ << endl;
    cout << "alas:" << alalaita_ << endl;
    cout << "vasen:" << vasen_laita_ << endl;
    cout << kryk_.at(0) << kryk_.at(1) << kryk_.at(2) << endl;
    cout << kryk_.at(3) << kryk_.at(4) << kryk_.at(5) << endl;
    cout << kryk_.at(6) << kryk_.at(7) << kryk_.at(8) << endl;
}
bool Pala::onko_aloituspala(){
    if (kryk_.size() == 10) {
        return true;
    }
    else {
        return false;
    }

}

bool Pala::onko_kulmapala(){
    int nollia{0};
    if (ylalaita_ == 0) {
        nollia++;
    }
    if (alalaita_ == 0) {
        nollia++;
    }
    if (oikea_laita_ == 0) {
        nollia++;
    }
    if (vasen_laita_ == 0) {
        nollia++;
    }
    if (nollia == 2) {
        return true;
    }
    else {
        return false;
    }
}


void Pala::kierra_eka(){
    while (vasen_laita_ != 0 && ylalaita_ != 0){
        int ylos_vaihtaja = ylalaita_;
        int oikea_vaihtaja = oikea_laita_;
        int alas_vaihtaja = alalaita_;
        int vasen_vaihtaja = vasen_laita_;

        string uusi_kryk{""};
        vector<int> jarjestus {6, 3, 0, 7, 4, 1, 8, 5, 2};

        //Vaihdetaan tarvittavat merkit / ja \ sekä - ja | toisikseen.
        int indeksi{0};
        while ( indeksi < 9 ){
            uusi_kryk.push_back( tarkista_char(kryk_.at(indeksi)) );
            indeksi++;
        }

        //Sijoitellaan "jarjestus" vektorin jarjestyksessa jokainen uudenkrykin merkki
        //kryk_:kiin
        indeksi = 0;
        while (indeksi < 9){
            kryk_.at(indeksi) = uusi_kryk.at(jarjestus[indeksi]);
            indeksi++;
        }

        ylalaita_ = vasen_vaihtaja;
        oikea_laita_ = ylos_vaihtaja;
        alalaita_ = oikea_vaihtaja;
        vasen_laita_ = alas_vaihtaja;
        cout<<vasen_laita_ + "  " + ylalaita_<< endl;

    }
}


void Pala::kierra_pala(int palan_numero, bool rinnakkain_tulostus) {
    int ylos_vaihtaja = ylalaita_;
    int oikea_vaihtaja = oikea_laita_;
    int alas_vaihtaja = alalaita_;
    int vasen_vaihtaja = vasen_laita_;

    string uusi_kryk{""};
    vector<int> jarjestus {6, 3, 0, 7, 4, 1, 8, 5, 2};

    //Vaihdetaan tarvittavat merkit / ja \ sekä - ja | toisikseen.
    int indeksi{0};
    while ( indeksi < 9 ){
        uusi_kryk.push_back( tarkista_char(kryk_.at(indeksi)) );
        indeksi++;
    }

    //Sijoitellaan "jarjestus" vektorin jarjestyksessa jokainen uudenkrykin merkki
    //kryk_:kiin
    indeksi = 0;
    while (indeksi < 9){
        kryk_.at(indeksi) = uusi_kryk.at(jarjestus[indeksi]);
        indeksi++;
    }

    ylalaita_ = vasen_vaihtaja;
    oikea_laita_ = ylos_vaihtaja;
    alalaita_ = oikea_vaihtaja;
    vasen_laita_ = alas_vaihtaja;

    //Tassa katsotaan kutsuttiinko kierra metodia rinnakkain -metodissa vai kutsuttiinko sita erikseen.
    if ( rinnakkain_tulostus == false ){
        cout << "Palaa " << palan_numero << " kierretty." << endl;
    }
}

//Metodi tulostaa palat rinnakkain jos palan oikealaita vastaa verrattavan palan vasenta laitaa.
//Jollei, niin kierretaan verrattava pala ympari ja koitetaan muita laitoja. Verrattava pala ei kuitenkaan
//jaa tahan asentoon.
bool Pala::vierekkain(Pala verrattava){
    int indeksi{0};
    while (indeksi < 4){

        if ( oikea_laita_ == verrattava.vasen_laita_ ) {
            return true;
        }
        else {
            verrattava.kierra_pala(2, true);
            indeksi++;
        }
    }
    return false;
}

bool Pala::allekkain(Pala allekkain){
    int indeksi{0};
    while (indeksi < 4){

        if ( alalaita_ == allekkain.ylalaita_ ) {
            return true;
        }
        else {
            allekkain.kierra_pala(2, true);
            indeksi++;
        }
    }
    return false;
}

