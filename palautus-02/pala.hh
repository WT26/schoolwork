#ifndef PALA_HH
#define PALA_HH

#include <string>
#include <vector>

using namespace std;


//kattava julkisen rajapinnan metodijako, jonka avulla palan jarjestely
//kay luontevasti
class Pala {
    public:
        Pala (vector<string> palan_tiedot) ;
        void tulosta_1() const;
        void tulosta_2() const;
        void tulosta_3() const;
        void kierra_pala();
        void kierra_eka();
        void kierra_vika();
        void kierra_vierekkain( Pala verrattava );
        void kierra_allekkain( Pala verrattava );
        bool vierekkain( Pala verrattava );
        bool allekkain ( Pala verrattava );
        bool onko_ylarivi();
        bool onko_alarivi();
        bool onko_aloituspala();
        bool onko_kulmapala();
        bool onko_reunapala();

    private:
        int oikea_laita_;
        int vasen_laita_;
        int ylalaita_;
        int alalaita_;
        string kryk_; //lyhenne Kuvan Rivit Yhteen Kirjoitettuna

};

#endif // PALA_HH
