#ifndef KOHDEYKSIKOT_HH
#define KOHDEYKSIKOT_HH

#include <string>
#include <memory>

using namespace std;

class Kohdeyksikot
{
public:
    Kohdeyksikot();

    bool onko_tyhja() const;
    bool lisaa_alkio(string lahtoyksikko, double suhde, double lisattava,
                     bool suunta);

    int listan_pituus();

    bool tulosta();

private:
    struct Yksikko_alkio {
        string yksikko;
        double suhde;
        double lisattava;
        bool suunta;
        shared_ptr<Yksikko_alkio> seuraavan_osoite;
    };

    shared_ptr<Yksikko_alkio> ensimmaisen_osoite_;
    shared_ptr<Yksikko_alkio> viimeisen_osoite_;
};

#endif // KOHDEYKSIKOT_HH
