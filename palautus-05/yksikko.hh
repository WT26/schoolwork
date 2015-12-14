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
    // void tulosta();
private:
    string nimi_;
    Kohdeyksikot kohdeyksikot_;
};

#endif // YKSIKKO_HH
