#ifndef KIRJASTO_HH
#define KIRJASTO_HH

#include "paivays.hh"
#include "lista.hh"
#include <string>
#include <memory>

// Kirjasto-luokka. Luokka on tehty STL:lan Mapin kaltaiseksi, siina luodaan
// structissa jokaiselle alkiolle paivays ja sita vastaava lista. Kirjasto
// toimii linkitetyn listan tavoin shared-pointtereilla. Listaa pidetaan
// ensimmaisesta ja viimeisesta osoitteesta.

using namespace std;

class Kirjasto
{
public:
    Kirjasto();

    void lisaa_alkio(Paivays lisattavan_paivays,const string &tapahtuma);

    bool poista_tapahtuma(Paivays paivays);
    bool onko_tyhja() const;
    bool onko_paivaysta(Paivays paivays);

    bool tulosta();
    bool tulosta_tapahtumat(Paivays paivays) const;
    void tallenna(const string paivyritiedoston_nimi) const;

    int kirjaston_pituus();
private:
    struct Kirjaston_alkio {
        Paivays paivays;
        Lista lista;
        shared_ptr<Kirjaston_alkio> seuraavan_osoite;
    };

    shared_ptr<Kirjaston_alkio> ensimmaisen_osoite_;
    shared_ptr<Kirjaston_alkio> viimeisen_osoite_;
};
#endif // KIRJASTO_HH
