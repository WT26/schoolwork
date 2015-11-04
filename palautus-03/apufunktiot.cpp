#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <vector>


using namespace std;

bool string_unsignediksi(const string& mjono, unsigned int& tulos) {
    const string NUMEROMERKIT{"0123456789"};

    if ( mjono.find_first_not_of(NUMEROMERKIT) != string::npos ) {
        return false;
    }

    tulos = stoi(mjono);

    return true;
}


// Vanha tuttu split.
vector<string> split(const string& merkkijono, char erotinmerkki) {
    vector<string> tulos;

    string::size_type tutkittava_kohta{0};
    string kentan_sisalto{""};

    while ( tutkittava_kohta < merkkijono.length() ) {

        if ( merkkijono.at(tutkittava_kohta) != erotinmerkki ) {
            kentan_sisalto.push_back( merkkijono.at(tutkittava_kohta) );

        } else {

            tulos.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }

        ++tutkittava_kohta;
    }

    tulos.push_back(kentan_sisalto);

    return tulos;
}
