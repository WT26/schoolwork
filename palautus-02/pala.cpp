#include "pala.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Pala::Pala(vector<string> palan_tiedot):
    ylalaita_{ stoi(palan_tiedot[0]) },
    oikea_laita_{ stoi(palan_tiedot[1]) },
    alalaita_{ stoi(palan_tiedot[2]) },
    vasen_laita_{stoi(palan_tiedot[3]) },
    kryk_{ palan_tiedot[4] }
{
}

void Pala::tulosta_1() const{
    cout << kryk_.at(0) << kryk_.at(1) << kryk_.at(2);
}

void Pala::tulosta_2() const{
    cout << kryk_.at(3) << kryk_.at(4) << kryk_.at(5);
}

void Pala::tulosta_3() const{
    cout << kryk_.at(6) << kryk_.at(7) << kryk_.at(8);
}

bool Pala::onko_ylarivi(){
    if (ylalaita_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Pala::onko_alarivi(){
    if (alalaita_ == 0) {
        return true;
    }
    else {
        return false;
    }
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
    while ((vasen_laita_ != 0) || (ylalaita_ != 0)){
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
    }
}

void Pala::kierra_pala() {
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
}

void Pala::kierra_vierekkain(Pala verrattava){
    while (vasen_laita_ != verrattava.oikea_laita_){
        kierra_pala();
    }
}

void Pala::kierra_allekkain(Pala verrattava){
    while (ylalaita_!= verrattava.alalaita_){
        kierra_pala();
    }
}

bool Pala::onko_reunapala(){
    if ( oikea_laita_ == 0 ) {
        return true;
    } else {
        return false;
    }
}

void Pala::kierra_vika(){
    while ((oikea_laita_ != 0) || (alalaita_ != 0)){
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
    }
}


bool Pala::vierekkain(Pala verrattava){
    int indeksi{0};
    if ((oikea_laita_ == verrattava.oikea_laita_) && (alalaita_ == verrattava.alalaita_)
            && (ylalaita_ == verrattava.ylalaita_) && (vasen_laita_ == verrattava.vasen_laita_)) {
        return false;
    }
    else {
        while (indeksi < 4){
            if ( (oikea_laita_ == verrattava.vasen_laita_) && (verrattava.vasen_laita_ != 0) ) {
                return true;
            }
            else {
                verrattava.kierra_pala();
                indeksi++;
            }
        }
        return false;
    }
}

bool Pala::allekkain(Pala verrattava){
    int indeksi{0};
    if ((oikea_laita_ == verrattava.oikea_laita_) && (alalaita_ == verrattava.alalaita_)
            && (ylalaita_ == verrattava.ylalaita_) && (vasen_laita_ == verrattava.vasen_laita_)) {
        return false;
    }
    else{
        while (indeksi < 4){
            if ( alalaita_ == verrattava.ylalaita_ ) {
                return true;
            }
            else {
                verrattava.kierra_pala();
                indeksi++;
            }
        }
        return false;
    }
}

