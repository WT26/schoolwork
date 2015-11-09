#ifndef PAIVYRI_HH
#define PAIVYRI_HH

#include "paivays.hh"
#include <string>
#include <map>
#include <deque>

using namespace std;

class Paivyri {
  public:
    Paivyri();
    bool lisaa_tapahtuma(const string& paivamaara, const string& kuvaus);
    bool tulosta_paivyridata();
    bool tulosta_merkinnat(const string paivamaara);
    bool poista_tapahtuma(const string paivamaara);
    bool poista_tyhja_paivays(const string paivamaara);
    bool lue_tiedosto();
    bool talleta_tiedosto(const string paivyritiedoston_nimi);
    const string lisaa_nollat(const string paivamaara);

    // Muita metodifunktioiden esittelyitä puuttuu tästä.

  private:
    map<Paivays, deque<string>> paivyridata_;
    // Jonkinlainen STL-map -rakenne tänne, johon eri päivämäärien
    // tapahtumien kuvaukset talletetaan.  Rakenteen on oltava sellainen
    // että hakuavaimena on Paivays-tyyppinen arvo, ja hyötykuormana
    // kaikki kyseiselle päivämäärälle kirjatut tapahtumien kuvaukset
    // nekin sopivassa säiliössä.
};

#endif
