#ifndef PALAPELI_HH
#define PALAPELI_HH

#include "pala.hh"

#include <string>
#include <vector>
#include <deque>

using namespace std;

class Palapeli {
    public:
        Palapeli (deque<Pala> kaikki_palat);
        void tulosta() const;
        void jarjesta();

    private:
        deque<Pala> pala_jono_;
        int leveys_;
        int korkeus_;

};

#endif // PALAPELI_HH
