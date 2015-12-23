#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

// Apufunktioita, joita kaytetaan apuna ohjelman suorituksessa.


#include <yksikko.hh>
#include <string>
#include <vector>

using namespace std;

vector<Yksikko> lue_muunnoskaaviot(string tiedoston_nimi);

bool tarkista_lahto_ja_kohde(string rivi);
bool tarkista_yksikon_kirjaimet(string lahtoyksikko, string kohdeyksikko);
bool tarkista_rivin_vaihto(char c);
bool onko_valilyonti(char c);
bool tarkista_rivi(string rivi);
bool onko_lisattavaa(string rivi);
bool onko_vain_numeroita(string numero);
bool onko_yksikko_olemassa(string yksikon_nimi, vector<Yksikko> kaikki_yksikot);
bool onko_kaava_olemassa(string lahtoyksikko, string kohdeyksikko, vector<Yksikko> kaikki_yksikot);

void lopeta_ohjelma();

string piste_pilkuksi(string desimaali);
string poista_valilyonnit(string rivi);

vector<string> split(const string& merkkijono, char erotinmerkki);
vector<Yksikko> lisaa_kaava(string kohdeyksikko, string lahtoyksikko, double suhde,
                 double lisattava, vector<Yksikko> kaikki_yksikot);


#endif // APUFUNKTIOT_HH
