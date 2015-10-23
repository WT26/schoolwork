#ifndef PALA_HH
#define PALA_HH

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Pala {
    public:
        Pala (vector<string> palan_tiedot) ;
        void tulosta() const;
        void kierra_pala();
        void kierra_eka();
        void kierra_vika();
        void kierra_vierekkain( Pala verrattava );
        void kierra_allekkain( Pala verrattava );
        bool vierekkain( Pala verrattava );
        bool allekkain ( Pala verrattava );
        bool onko_aloituspala();
        bool onko_kulmapala();
        bool onko_reunapala();
        int oikea_laita_;
        int vasen_laita_;
        int ylalaita_;
        int alalaita_;
        string kryk_;



    private:


};

#endif // PALA_HH
