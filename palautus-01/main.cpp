#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Pala {
    public:
        Pala(vector<string> palan_tiedot );
        void tulosta() const;
        void kaanna_pala();

    private:
        void tarkista_muoto() const;
        int ylalaita_;
        int oikea_laita_;
        int alalaita_;
        int vasen_laita_;
        string kryk_;//lyhennetty: Kuvan Rivit Yhteen Kirjoitettuna
};

//############################Funktiot############################

//Funktioiden esittelyt
vector<string> split(const string& merkkijono, char erotinmerkki);
vector<string> tarkista_komento(string komento);
bool tarkista_tiedot(vector<string> palan_tiedot);

//Funktio jakaa merkkijonon annetun erotinmerkin kohdalta.
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
            tarkistettava_komento[2] = tarkistettava_komento[2] + " " + tarkistettava_komento[2+indeksi];
            indeksi++;
            kuvaan_lisattavat--;
        }
    }
    int tarkistus{0};

    while ( tarkistus < komentolista.size() ){

        if ( tarkistettava_komento[0] == komentolista[ tarkistus ] ) {
            return tarkistettava_komento;
        }
        tarkistus++;
    }
    cout << "Virhe: Syottamaasi komentoa ei loydy" << endl;
}

//Funktio tarkistaa onko kaikki annetut palan tiedot oikein:
//onko kuvassa kaytetty oikeita merkkeja ja onko laidat positiivisia kokonaislukuja
bool tarkista_tiedot( vector<string> palan_tiedot )
{
    vector<char> sallitut_merkit{   'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z','A', 'B',
                                    'C', 'D', 'R', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
                                    '4', '5', '6', '7', '8', '9', ' ', '-', '|', '+',  '*',  '#',  '@',
                                    '/'};//merkki \ ei toimi
    vector<char>::iterator merkki_iter;
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

                if ( palan_tiedot[4].at( indeksi ) == *merkki_iter ) {
                    vaara_merkki = 1;
                    break;

                } else {

                cout << palan_tiedot[4].at(indeksi)<<endl;
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
        return true;
    }
}

//############################Funktiot valmiit############################

int main()
{
    int ohjelma_kaynnissa{1};
    set<int> palojen_numerot;
    map<int, Pala> pala_hakemisto;

    while (ohjelma_kaynnissa == 1) {
        string syotetty_komento{""};
        vector<string> komento;

        cout << "komento> ";
        getline(cin, syotetty_komento);

        if ( syotetty_komento == "" ){
            return 0;

        } else {

            komento = tarkista_komento(syotetty_komento);

            if ( komento[0] == "pala" ){
                int palan_numero;
                palan_numero = stoi(komento[1]); //Muutetaan pala komennon (palan numero) osa str->int

                if ( palojen_numerot.find( palan_numero ) == palojen_numerot.end() ){
                    palojen_numerot.insert( palan_numero );
                    vector<string> palan_tiedot = split( komento[2], ':' );
                    if ( tarkista_tiedot(palan_tiedot) == true ) {
                        pala_hakemisto.insert( { palan_numero, Pala(palan_tiedot ) } );
                        cout << "Pala "<< palan_numero << " asetettu." << endl;
                    }

                } else { //Jos pala onkin jo hakemistossa, poistetaan vanha ja korvataan uudella
                    vector<string> palan_tiedot = split( komento[2], ':' );
                    pala_hakemisto.erase( palan_numero );
                    pala_hakemisto.insert( { palan_numero, Pala( palan_tiedot ) } );
                    cout << "Pala "<< palan_numero << " asetettu." << endl;
                }


            }

            if (komento[0] == "tulosta") {
                Pala tulostettava = pala_hakemisto.at( stoi( komento[1] ) );
                tulostettava.tulosta();
            }

            if (komento[0] == "kierra") {

            }

            if (komento[0] == "rinnakkain") {

            }
        }
    }
}

//############################Metodien maarittely############################

Pala::Pala(vector<string> palan_tiedot):
    ylalaita_{ stoi( palan_tiedot[0] ) },
    oikea_laita_{ stoi( palan_tiedot[1] ) },
    alalaita_{ stoi( palan_tiedot[2] ) },
    vasen_laita_{stoi( palan_tiedot[3] ) },
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

//void Pala::tarkista_tiedot() const{

//}

//############################Metodien maarittely valmis############################

