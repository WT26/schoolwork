#ifndef PALAPELI_HH
#define PALAPELI_HH

#include <string>
#include <vector>
#include <deque>

using namespace std;

class Palapeli {
    public:
        Palapeli (deque<Pala> kaikki_palat) ;
        void tulosta() const;
        void kierra_pala( int palan_numero, bool rinnakkain_tulostus );
        void rinnakkain( Pala rinnakkainen );


    private:

};

#endif // PALAPELI_HH
