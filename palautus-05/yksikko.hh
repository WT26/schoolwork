#ifndef YKSIKKO_HH
#define YKSIKKO_HH

// Jokaisesta tekstitiedoston kaavasta tehdaan yksikko-olio. Yksikko oliossa
// on tallessa vektorissa kaikki sen kohdeyksikot, eli ne yksikot, joiden
// kaavat ovat suoraan lukuvaiheessa yhteydessa yksikkoon. Yksikolla on
// myos useita metodeita, joita tarvitaan haku, ja muunnos algoritmeissa.

#include "kohdeyksikko.hh"
#include <string>
#include <vector>

using namespace std;

class Yksikko
{
public:
    Yksikko(string kohdeyksikon_nimi);

    bool vertaa_yksikon_nimea(string verrattava);
    bool loytyyko_kohdeyksikko(string yksikko_nimi);


    void lisaa_kohdeyksikko(string lahtoyksikko, double suhde,
                            double lisattava, bool suunta);

    string tulosta_yksikon_nimi();
    string nimi_;


    int kohdeyksikkojen_maara();

    pair<double, int> etsi_kohteen_suhde(pair<double, int> suhde_maara,
                string ensimmainen, string lahto, string kohde,
                vector<Yksikko> kaikki_yksikot, vector<string>lapi_kaydyt);

    double etsi_kohteen_lisattava(double lisays, string lahto, string kohde,
                vector<Yksikko> kaikki_yksikot, vector<string>lapi_kaydyt);

    vector<string> kohdeyksikoiden_lisattavyys(vector<string> jo_lisatyt);
    vector<string> yksikot_stringiksi(vector<Yksikko> kaikki_yksikot);

    vector<string> keraa_kohdeyksikot(vector<string> loytyy_listasta,
                vector<Yksikko> kaikki_yksikot, vector<string> lapi_kaydyt);

private:
    vector<Kohdeyksikko> kohdeyksikot_;
};

#endif // YKSIKKO_HH
