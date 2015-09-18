#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Kaytettavien funktioiden esittely
vector<string> split(const string& merkkijono, char erotinmerkki);
string tarkista_komento(string komento);


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

string tarkista_komento(string komento)
{
    const vector<string>komentolista{"pala", "tulosta", "kierra", "rinnakkain", "komennot"};
    vector<string>tarkistettava_komento;
    tarkistettava_komento = split(komento, ':');
    int tarkistus{0};

    while ( tarkistus < komentolista.size() ){

        if (tarkistettava_komento[0] == komentolista[tarkistus]){
            cout << "loytyy listasta" << endl;
            return 0;
        }
        tarkistus++;
    }
    cout << "Syottamaasi komentoa ei loydy" << endl;
}


int main()
{
    int ohjelma_kaynnissa{1};
    while (ohjelma_kaynnissa == 1) {
        string komento{""};
        cout << "komento> ";
        cin >> komento;
        tarkista_komento(komento);
    }
}

