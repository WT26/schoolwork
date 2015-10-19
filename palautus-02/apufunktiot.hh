#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

vector<string> split(string& merkkijono, char erotinmerkki);
char tarkista_char(char merkki);
bool tarkista_tiedot(vector<string> palan_tiedot);
vector<string> tarkista_komento(string komento);

#endif // APUFUNKTIOT_HH
