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
        void kierra_pala( int palan_numero, bool rinnakkain_tulostus );
        void rinnakkain( Pala rinnakkainen);

    private:
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
char tarkista_char(char merkki);
void rinnakkain(Pala, Pala);

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
                                    '/', '\\'};
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
            int numero_1 = stoi( palan_tiedot[0] );
            int numero_2 = stoi( palan_tiedot[1] );
            int numero_3 = stoi( palan_tiedot[2] );
            int numero_4 = stoi( palan_tiedot[3] );
            if ( ( numero_1 > 0 ) && ( numero_2 > 0 ) && ( numero_3 > 0 ) && ( numero_4 > 0 ) ) {
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

char tarkista_char( char merkki ) {
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

                    if ( tarkista_tiedot(palan_tiedot) == true ) {
                        pala_hakemisto.erase( palan_numero );
                        pala_hakemisto.insert( { palan_numero, Pala( palan_tiedot ) } );
                        cout << "Pala "<< palan_numero << " asetettu." << endl;
                    }
                }
            }

            else if (komento[0] == "tulosta") {
                pala_hakemisto.at( stoi( komento[1] ) ).tulosta();
            }

            else if (komento[0] == "kierra") {
                pala_hakemisto.at( stoi( komento[1] ) ).kierra_pala( stoi( komento[1] ), false );
            }

            else if (komento[0] == "rinnakkain") {
                pala_hakemisto.at( stoi(komento[1]) ).rinnakkain( pala_hakemisto.at( stoi(komento[2]) ) );
            }
            else {
                cout << "Virhe: Vaaranlainen komento" << endl;
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

void Pala::kierra_pala( int palan_numero, bool rinnakkain_tulostus ) {
    int ylos_vaihtaja = ylalaita_;
    int oikea_vaihtaja = oikea_laita_;
    int alas_vaihtaja = alalaita_;
    int vasen_vaihtaja = vasen_laita_;

    string uusi_kryk{""};
    vector<int> jarjestus {6, 3, 0, 7, 4, 1, 8, 5, 2};

    //Vaihdetaan tarvittavat merkit / ja \ sekä - ja | toisikseen.
    int indeksi{0};
    while (indeksi < 9){
        uusi_kryk.push_back(tarkista_char(kryk_.at(indeksi)));
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

    //Tilanne ennen:
    // 0 1 2
    // 3 4 5
    // 6 7 8

    //Tilanne kierron jalkeen:
    // 6 3 0
    // 7 4 1
    // 8 5 2

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
            rinnakkainen.kierra_pala( 2, true );
            indeksi++;
        }
    }
}

//############################Metodien maarittely valmis############################

