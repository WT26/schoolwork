#ifndef PAIVAYS_HH
#define PAIVAYS_HH

#include <string>

using namespace std;

class Paivays {
  public:
    Paivays();
    Paivays(unsigned int paiva, unsigned int kuu, unsigned int vuosi);
    Paivays(const string& paivays);

    bool aseta(unsigned int paiva, unsigned int kuu, unsigned int vuosi);
    bool aseta(const string& paivays);

    void seuraava_paiva();

    bool operator<(const Paivays& oikealla) const;

    string merkkijonoksi(string formaatti = "%{PAIVA}.%{KUU}.%{VUOSI}") const;
    void tulosta(const string& formaatti = "%{PAIVA}.%{KUU}.%{VUOSI}") const;

  private:
    unsigned int paiva_;
    unsigned int kuu_;
    unsigned int vuosi_;
};


bool operator==(const Paivays& vasemmalla, const Paivays& oikealla);
bool operator!=(const Paivays& vasemmalla, const Paivays& oikealla);
bool operator>(const Paivays& vasemmalla, const Paivays& oikealla);
bool operator<=(const Paivays& vasemmalla, const Paivays& oikealla);
bool operator>=(const Paivays& vasemmalla, const Paivays& oikealla);

#endif
