#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include <yksikko.hh>
#include <string>
#include <vector>

using namespace std;

vector<Yksikko> lue_muunnoskaaviot(string tiedoston_nimi);

bool tarkista_rivin_vaihto(char c);
bool onko_valilyonti(char c);
bool tarkista_rivi(string rivi);
bool onko_lisattavaa(string rivi);

string piste_pilkuksi(string desimaali);
string poista_valilyonnit(string rivi);

vector<string> split(const string& merkkijono, char erotinmerkki);
vector<Yksikko> lisaa_kaava(string kohdeyksikko, string lahtoyksikko, double suhde,
                 double lisattava, vector<Yksikko> kaikki_yksikot);


#endif // APUFUNKTIOT_HH
