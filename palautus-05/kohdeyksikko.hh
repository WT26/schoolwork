#ifndef KOHDEYKSIKKO_HH
#define KOHDEYKSIKKO_HH

#include <string>

using namespace std;

class Kohdeyksikko
{
public:
    Kohdeyksikko(string yksikon_nimi, double suhde, double lisattava,
                 bool suunta);

    void tulosta();
private:
    string yksikko_;
    double suhde_;
    double lisattava_;
    bool suunta_;
};

#endif // KOHDEYKSIKKO_HH
