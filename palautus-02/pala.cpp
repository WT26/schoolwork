#include "pala.hh"

#include <string>
#include <vector>
#include <map>
#include <set>

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
void Pala::rinnakkain(Pala rinnakkainen){
    int indeksi{0};
    while (indeksi < 4){

        if ( oikea_laita_ == rinnakkainen.vasen_laita_ ) {
            cout << kryk_.at(0) << kryk_.at(1) << kryk_.at(2);
            cout << rinnakkainen.kryk_.at(0) << rinnakkainen.kryk_.at(1) << rinnakkainen.kryk_.at(2) << endl;
            cout << kryk_.at(3) << kryk_.at(4) << kryk_.at(5);
            cout << rinnakkainen.kryk_.at(3) << rinnakkainen.kryk_.at(4) << rinnakkainen.kryk_.at(5) << endl;
            cout << kryk_.at(6) << kryk_.at(7) << kryk_.at(8);
            cout << rinnakkainen.kryk_.at(6) << rinnakkainen.kryk_.at(7) << rinnakkainen.kryk_.at(8) << endl;
            indeksi = 4;
        }
        else {
            rinnakkainen.kierra_pala(2, true);
            indeksi++;
        }
    }
}
