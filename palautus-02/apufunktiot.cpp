#include "apufunktiot.hh"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

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

//Funktio tarkastaa onko syotettya komentoa olemassa
vector<string> tarkista_komento(string komento)
{
    const vector<string>komentolista{"pala", "tulosta", "kierra", "rinnakkain"};
    vector<string>tarkistettava_komento;

    tarkistettava_komento = split(komento, ' ');

   //Jos valilyonteja on palapelin kuvassa, yhdistetaan kuva takaisin yhteen
    if ( tarkistettava_komento.size() > 3 ) {
        int kuvaan_lisattavat{ tarkistettava_komento.size() - 3 };
        int indeksi{1};
        while ( kuvaan_lisattavat != 0 ){
            tarkistettava_komento[2] = tarkistettava_komento[2] + " " + tarkistettava_komento[2 + indeksi];
            indeksi++;
            kuvaan_lisattavat--;
        }
    }
    int tarkistus{0};

    while ( tarkistus < komentolista.size() ){

        if ( tarkistettava_komento[0] == komentolista[tarkistus] ) {
            return tarkistettava_komento;
        }
        tarkistus++;
    }
    cout << "Virhe: Syottamaasi komentoa ei loydy" << endl;
}


//Funktio tarkistaa onko kaikki annetut palan tiedot oikein:
//onko kuvassa kaytetty oikeita merkkeja ja onko laidat positiivisia kokonaislukuja
bool tarkista_tiedot(vector<string> palan_tiedot) {
    vector<char>::iterator merkki_iter;
    vector<char> sallitut_merkit{   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B',
                                    'C', 'D', 'R', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                                    '4', '5', '6', '7', '8', '9', ' ', '-', '|', '+',  '*',  '#',  '@',
                                    '/', '\\'   };

    merkki_iter = sallitut_merkit.begin();

    int indeksi{0};
    if ( palan_tiedot[4].length() != 9 ){
        cout << "Virhe: Palan kuvan merkkeja ei ole tasan yhdeksaa" << endl;
        return false;

    } else {

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
                return false;
            }
            ++indeksi;
            merkki_iter = sallitut_merkit.begin();

        }

        //Tama vaihe tarkistaa palan laidat, niiden on oltava positiivisia kokonaislukuja
        try {
            int numero_1 = stoi(palan_tiedot[0]);
            int numero_2 = stoi(palan_tiedot[1]);
            int numero_3 = stoi(palan_tiedot[2]);
            int numero_4 = stoi(palan_tiedot[3]);
            if ( (numero_1 > 0) && (numero_2 > 0) && (numero_3 > 0) && (numero_4 > 0) ) {
                return true;

            } else {
                cout << "Virhe: Palan laidat eivat olleet positiivisia kokonaislukuja" << endl;
                return false;
            }
        }
        catch(exception const){
            cout << "Virhe: Palan laidat eivat olleet positiivisia kokonaislukuja" <<endl;
            return false;
        }
    }
}

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
