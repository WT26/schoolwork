#ifndef PALA_HH
#define PALA_HH

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Pala {
    public:
        Pala (const vector<string> palan_tiedot) ;
        void tulosta() const;
        void kierra_pala( int palan_numero, bool rinnakkain_tulostus );
        void rinnakkain( Pala rinnakkainen );


    private:
        int ylalaita_;
        int oikea_laita_;
        int alalaita_;
        int vasen_laita_;
        string kryk_;
};

#endif // PALA_HH
