#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include <string>
#include <vector>

using namespace std;

void lue_muunnoskaaviot();

bool tarkista_rivin_vaihto(char c);
bool onko_valilyonti(char c);
bool tarkista_rivi(string rivi);

string poista_valilyonnit(string rivi);

vector<string> split(const string& merkkijono, char erotinmerkki);


#endif // APUFUNKTIOT_HH
