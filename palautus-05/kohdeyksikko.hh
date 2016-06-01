#ifndef KOHDEYKSIKKO_HH
#define KOHDEYKSIKKO_HH

// Luokka, jota hyodynnetaan kaavojen sailomisessa. Kohdeyksikko on jonkun
// yksikon sellainen yksikko, jonka muunnos tiedetaan. Muunnokseen liittyvat
// yksikoiden suhde, suunta seka tarvittaessa lisattava luku. Suunta tarkoittaa
// sita etta kerrotaanko yksikko muunnosvaiheessa vai jaetaanko, eli kumpaan
// suuntaan muunnosta halutaan tehda.

#include <string>
#include <vector>

using namespace std;

class Kohdeyksikko
{
public:
    Kohdeyksikko(string yksikon_nimi, double suhde, double lisattava,
                 bool suunta);

    string tulosta();
    string yksikko_;


    vector<string> keraa_kohdeyksikot(vector<string> loytyy_listasta);
    vector<string> lisaa_kohdeyksikko_vectoriin(vector<string> lista);

    bool vertaa_nimea(string verrattava);
    bool onko_lisattavyytta();

    double palauta_suhde();
    double palauta_lisattava();

private:
    double suhde_;
    double lisattava_;
    bool suunta_;
};

#endif // KOHDEYKSIKKO_HH
