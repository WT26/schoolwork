#ifndef KOHDEYKSIKKO_HH
#define KOHDEYKSIKKO_HH

#include <string>
#include <vector>

using namespace std;

class Kohdeyksikko
{
public:
    Kohdeyksikko(string yksikon_nimi, double suhde, double lisattava,
                 bool suunta);

    string tulosta();

    vector<string> keraa_kohdeyksikot(vector<string> loytyy_listasta);
private:
    string yksikko_;
    double suhde_;
    double lisattava_;
    bool suunta_;
};

#endif // KOHDEYKSIKKO_HH
