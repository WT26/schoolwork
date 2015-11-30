#ifndef KIRJASTO_HH
#define KIRJASTO_HH

#include "paivays.hh"
#include "lista.hh"

#include <string>
#include <memory>

using namespace std;

class Kirjasto
{
public:
    Kirjasto();

    void lisaa_alkio(Paivays lisattavan_paivays,const string &tapahtuma);

    bool poista_tapahtuma(Paivays paivays);
    bool onko_tyhja() const;

    void tulosta() const;
    void tulosta_tapahtumat(Paivays paivays) const;
    void tallenna() const;
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
