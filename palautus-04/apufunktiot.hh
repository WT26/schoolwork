#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH

#include "paivyri.hh"
#include "lista.hh"
#include <string>
#include <vector>

using namespace std;

bool lue_paivyritiedosto(const string& paivyritiedoston_nimi, Paivyri& paivyri);

Lista split(const string& merkkijono, char erotinmerkki);

bool string_unsignediksi(const string& mjono, unsigned int& tulos);


#endif // APUFUNKTIOT_HH
