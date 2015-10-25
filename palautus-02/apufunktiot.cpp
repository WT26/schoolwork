#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Funktio jakaa merkkijonon annetun erotinmerkin kohdalta palautettavaan vektoriin.
//Kyseinen funktio on sama kuin viikkoharjoituksessa oltiin annettu
vector<string> split(string& merkkijono, char erotinmerkki) {
    vector<string> tulos;

    string::size_type tutkittava_kohta{0};
    string kentan_sisalto{""};

    while ( tutkittava_kohta < merkkijono.length() ) {

        if ( merkkijono.at(tutkittava_kohta) != erotinmerkki ) {
            // Merkkijonon loppuun voi lisata uuden merkin (char)
            // push_back-metodilla.
            kentan_sisalto.push_back( merkkijono.at(tutkittava_kohta) );

        } else {
            // Kentan erotinmerkki tuli vastaan, talloin muuttujaan
            // «kentan_sisalto» on kertynyt edeltavan kentan teksti.

            tulos.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }

        ++tutkittava_kohta;
    }

    // Viimeisen kentan perassä ei ole erotinmerkkia, joten edeltava
    // silmulla ei lisaa kentan sisaltoa «kentan_sisalto»-vektoriin:
    // tehdaan se erikseen.
    tulos.push_back(kentan_sisalto);

    return tulos;
}


//Funktio tarkistaa onko kaikki annetut palan tiedot oikein:
//onko kuvassa kaytetty oikeita merkkeja ja onko laidat positiivisia kokonaislukuja
string tarkista_tiedot(string palan_tiedot_string) {
    vector<string> palan_tiedot = split( palan_tiedot_string, ':' );
    vector<char>::iterator merkki_iter;
    vector<char> sallitut_merkit{   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B',
                                    'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                                    '4', '5', '6', '7', '8', '9', ' ', '-', '|', '+',  '*',  '#',  '@',
                                    '/', '\\', '='  };

    bool tiedot_sallittuja_merkkien_tarkasteluun = true;

    if ( (palan_tiedot[4].length() == 10) ){
            if (palan_tiedot[4].at(9) == '='){
                tiedot_sallittuja_merkkien_tarkasteluun = true;
            }
            else {
                cout<<"virhe: palan kuviossa vaaria merkkeja"<<endl;
                return "virhe";
            }
    }
    else if (palan_tiedot[4].length() == 9){
        tiedot_sallittuja_merkkien_tarkasteluun = true;
    }
    else if (palan_tiedot[4].length() > 10) {
        cout<<"virhe: jossain palassa yli kymmenen merkkia."<<endl;
        return "virhe";
    }

    merkki_iter = sallitut_merkit.begin();
    int indeksi{0};

    if (tiedot_sallittuja_merkkien_tarkasteluun == true) {
        //Ensimmainen looppi kay lapi annetut yhdeksan merkkia,
        //toinen vertaa naita merkkeja sallittujen merkkien vectoriin.
        while ( indeksi < palan_tiedot[4].length() ) {
            int vaara_merkki{0};

            while ( merkki_iter != sallitut_merkit.end() ) {

                if ( palan_tiedot[4].at(indeksi) == *merkki_iter ) {
                    vaara_merkki = 1;
                    break;

                } else {
                ++merkki_iter;

                }
            }

            if ( vaara_merkki == 0 ){
                cout<< "Virhe: Palan tiedoissa vaaria merkkeja" << endl;
                return "virhe";
            }
            ++indeksi;
            merkki_iter = sallitut_merkit.begin();

        }

        //Tama vaihe tarkistaa palan laidat, niiden on oltava positiivisia kokonaislukuja
        //Tarkistaa myos onko nollia kaksi ja jos on, niiden on oltava vierekkaiset
        try {
            int nollat{0};
            int numero_1 = stoi(palan_tiedot[0]);
            int numero_2 = stoi(palan_tiedot[1]);
            int numero_3 = stoi(palan_tiedot[2]);
            int numero_4 = stoi(palan_tiedot[3]);
            bool nollat_vierekkain;

            if ( numero_1 == 0) {
                nollat++;
            }
            if ( numero_2 == 0) {
                nollat++;
            }
            if ( numero_3 == 0) {
                nollat++;
            }
            if ( numero_4 == 0) {
                nollat++;
            }


            if ((numero_1 == 0) && (numero_2 == 0) && (nollat == 2)){
                nollat_vierekkain = true;
            }
            else if ((numero_2 == 0) && (numero_3 == 0) && (nollat == 2)) {
                nollat_vierekkain = true;
            }
            else if ((numero_3 == 0) && (numero_4 == 0) && (nollat == 2)) {
                nollat_vierekkain = true;
            }
            else if ((numero_4 == 0) && (numero_1 == 0) && (nollat == 2)) {
                nollat_vierekkain = true;
            }
            else if (nollat < 2) {
                nollat_vierekkain = true;
            }
            else {
                nollat_vierekkain = false;
            }



            if ( (numero_1 >= 0) && (numero_2 >= 0) && (numero_3 >= 0) && (numero_4 >= 0) ) {
                if (nollat_vierekkain == true) {
                    string pala_str = palan_tiedot[0] + ":" + palan_tiedot[1] + ":" + palan_tiedot[2]
                            + ":" + palan_tiedot[3] + ":" + palan_tiedot[4];

                    if (palan_tiedot[4].length() < 9) {
                        int lisattavat = 9 - palan_tiedot[4].length();

                        while (lisattavat > 0) {
                            pala_str += " ";
                            lisattavat--;
                        }
                    }
                    return pala_str;

                }
                else {
                    cout<<"Virhe: Jossain palassa enemman kuin 2 nollaa tai nollat eivat ole vierekkaiset nollat"<<endl;
                    return "virhe";
                }

            } else {
                cout << "Virhe: Palan laidat eivat olleet positiivisia kokonaislukuja" << endl;
                return "virhe";
            }
        }
        catch(exception const){
            cout << "Virhe: Palan laidat eivat olleet positiivisia kokonaislukuja" <<endl;
            return "virhe";
        }
    }
    else {
        return "virhe";
    }
}


//Tarkistaa ja vaihtaa muutamat viivamerkit toisikseen, jos niita palassa esiintyy
char tarkista_char(char merkki) {
    if ( merkki == '\\' ) {
        merkki = '/';
        return merkki;
    }
    else if ( merkki == '/' ) {
        merkki = '\\';
        return merkki;
    }
    else if ( merkki == '-' ) {
        merkki = '|';
        return merkki;
    }
    else if ( merkki == '|' ) {
        merkki = '-';
        return merkki;
    }
    else {
        return merkki;
    }
}
