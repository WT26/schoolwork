#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Pala {
    public:
        Pala(vector<string> palan_muoto );
        void tulosta() const;
        void kaanna_pala ();

    private:
        int ylalaita_;
        int oikea_laita_;
        int alalaita_;
        int vasen_laita_;
        string kuvan_rivit_yhteen_kirjoitettuna_;
};

//Kaytettavien funktioiden esittely
vector<string> split(const string& merkkijono, char erotinmerkki);
vector<string> tarkista_komento(string komento);


vector<string> split(string& merkkijono, char erotinmerkki) {
    vector<string> tulos;

    string::size_type tutkittava_kohta{0};
    string kentan_sisalto{""};

    while ( tutkittava_kohta < merkkijono.length() ) {

        if ( merkkijono.at(tutkittava_kohta) != erotinmerkki ) {
            // Merkkijonon loppuun voi lisätä uuden merkin (char)
            // push_back-metodilla.
            kentan_sisalto.push_back( merkkijono.at(tutkittava_kohta) );

        } else {
            // Kentän erotinmerkki tuli vastaan, tällöin muuttujaan
            // «kentan_sisalto» on kertynyt edeltävän kentän teksti.

            tulos.push_back(kentan_sisalto);
            kentan_sisalto = "";
        }

        ++tutkittava_kohta;
    }

    // Viimeisen kentän perässä ei ole erotinmerkkiä, joten edeltävä
    // silmulla ei lisää kentän sisältöä «kentan_sisalto»-vektoriin:
    // tehdään se erikseen.
    tulos.push_back(kentan_sisalto);

    return tulos;
}


vector <string> tarkista_komento(string komento)
{
    const vector<string>komentolista{"pala", "tulosta", "kierra", "rinnakkain"};
    vector<string>tarkistettava_komento;
    tarkistettava_komento = split(komento, ' ');
    int tarkistus{0};

    while ( tarkistus < komentolista.size() ){

        if (tarkistettava_komento[0] == komentolista[tarkistus]){
            return tarkistettava_komento;
        }
        tarkistus++;
    }
    cout << "Virhe: Syottamaasi komentoa ei loydy" << endl;
}


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
                palan_numero = stoi(komento[1]);

                if ( palojen_numerot.find( palan_numero ) == palojen_numerot.end() ){
                    palojen_numerot.insert( palan_numero );
                    vector<string> palan_muoto = split( komento[2], ':' );
                    cout << palan_muoto[0]<<palan_muoto[1]<<palan_muoto[2]<<palan_muoto[3]<<palan_muoto[4]<< endl;
                    pala_hakemisto.insert( { palan_numero, Pala(palan_muoto ) } );

                } else { //Jos pala onkin jo hakemistossa, poistetaan vanha ja korvataan uudella
                    vector<string> palan_muoto = split( komento[2], ':' );
                    cout << palan_muoto[0]<<palan_muoto[1]<<palan_muoto[2]<<palan_muoto[3]<<palan_muoto[4]<< endl;
                    pala_hakemisto.erase( palan_numero );
                    pala_hakemisto.insert( { palan_numero, Pala(palan_muoto ) } );
                }


            }

            if (komento[0] == "tulosta") {

            }

            if (komento[0] == "kierra") {

            }

            if (komento[0] == "rinnakkain") {

            }
        }
    }
}
Pala::Pala(vector<string> palan_muoto):
    ylalaita_{ stoi( palan_muoto[0] ) },
    oikea_laita_{ stoi( palan_muoto[1] ) },
    alalaita_{ stoi( palan_muoto[2] ) },
    vasen_laita_{stoi( palan_muoto[3] ) },
    kuvan_rivit_yhteen_kirjoitettuna_{ palan_muoto[4] }
{
}


