#ifndef PAIVAYS_HH
#define PAIVAYS_HH

#include <string>

// Paivays-luokka, annettua koodia. Paivaysta on hitusen muutettu, jottei
// STL sailioita tarvitse kayttaa. Muutos tapahtui merkkijonoksi ja tulosta
// metodeissa. Muuten samanlainen.

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

    string merkkijonoksi() const;
    void tulosta() const;

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
