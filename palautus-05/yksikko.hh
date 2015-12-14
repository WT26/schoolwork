#ifndef YKSIKKO_HH
#define YKSIKKO_HH

#include <kohdeyksikot.hh>
#include <string>

using namespace std;

class Yksikko
{
public:
    Yksikko(string kohdeyksikon_nimi, Kohdeyksikot kohdeyksikko);

    bool vertaa_yksikon_nimea(string verrattava);

    void lisaa_kohdeyksikko(string lahtoyksikko, double suhde,
                            double lisattava, bool suunta);
    void tulosta_kohdeyksikot();
private:
    string nimi_;
    Kohdeyksikot kohdeyksikot_;
};

#endif // YKSIKKO_HH
