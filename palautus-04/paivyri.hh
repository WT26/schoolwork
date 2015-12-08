#ifndef PAIVYRI_HH
#define PAIVYRI_HH

#include "paivays.hh"
#include "kirjasto.hh"
#include <string>

// Paivyri luokka pitaa kirjaa paivyridatasta. Paivyri luokka myos tekee
// kayttajan antamat komennot datalle. Paivyridata koostuu Kirjastosta,
// jossa on Paivaysluokan tapaiset paivamaarat, ja niita vastaavat
// tapahtuma Listat.

using namespace std;

class Paivyri {
  public:
    Paivyri();

    bool lisaa_tapahtuma(const string& paivamaara, const string& kuvaus);
    bool tulosta_paivyridata();
    bool tulosta_paivamaaran_tapahtumat(const string paivamaara);
    bool poista_tapahtuma(const string paivamaara);
    bool poista_tyhja_paivays(const string paivamaara);
    bool lue_tiedosto();
    bool talleta_tiedosto(const string paivyritiedoston_nimi);

    const string lisaa_nollat(const string paivamaara);

  private:
    Kirjasto paivyridata_;
};

#endif // PAIVYRI_HH
