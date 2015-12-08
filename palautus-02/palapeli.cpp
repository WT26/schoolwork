#include "palapeli.hh"
#include "pala.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>

using namespace std;

Palapeli::Palapeli(deque<Pala> pala_jono):
    pala_jono_{ pala_jono },
    leveys_{},
    korkeus_{}
{
}


// Metodi tutkii palajonoa ja jarjestelee palat vastaamaan kuviota.
// Esimerkiksi pala_jono [1, 2, 3, 4, 5, 6] tulisi olla kuvion:
//
//      1 2 3
//      4 5 6
//
// nakoinen.
bool Palapeli::jarjesta() {
    deque<Pala>::iterator jarjestaja;
    jarjestaja = pala_jono_.begin();
    bool jarjestus_valmis = false;
    int kulmapaloja_valmiina{0};
    int jarjestettu_lkm{0};
    int korkeus_selvilla{0};

    while (!jarjestus_valmis){
        if (jarjestettu_lkm == 0){
            if((*jarjestaja).onko_aloituspala()){
                // Ensimmainen pala on tassa vaiheessa loydetty, kierretaan se ympari
                // oikeinpain ja sijoitetaan alkuun.
                (*jarjestaja).kierra_eka();
                iter_swap(jarjestaja, pala_jono_.begin());
                jarjestettu_lkm++;
                kulmapaloja_valmiina++;
            }
            else {
                jarjestaja++;
            }
        }

        // Etsitaan seuraavat palat, ja jarjestellaan niita perakkain kunnes tulee vastaan kulma
        // pala.
        while ((jarjestettu_lkm >= 1) && (kulmapaloja_valmiina == 1)) {

            for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){

                // Etsitaan viereen sopiva pala.
                if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){

                    // Tarkastetaan onko se kulmapala.
                    if((*jarjestaja).onko_kulmapala()){

                        // Kierretaan oikein pain.
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));

                        // Tarkistetaan viela kuuluuko kyseinen pala ylariviin
                        if((*jarjestaja).onko_ylarivi()){
                            kulmapaloja_valmiina++;
                            leveys_ = jarjestettu_lkm + 1;

                            // Vaihdetaan pala jonossa seuraavaksi.
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                        }
                        else {
                            cout<<"virhe: palojen yla reunoissa virheita"<<endl;
                            return false;
                        }

                    }
                    else{

                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));

                        if((*jarjestaja).onko_ylarivi()){
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                        }
                        else {
                            cout<<"virhe: palojen yla reunoissa virheita"<<endl;
                            return false;
                        }
                    }
                }
            }
        }
        while (kulmapaloja_valmiina == 2) {
            // korkeus_selvilla arvot:
            // 0 = Etsitaan alle sopivaa palaa
            // 1 = Etsitaan vierekkaisia paloja
            // 2 = uusi kulmapala loytynyt eli lopeta looppi.

            // korkeus ei ole viela selvilla, etsitaan allekkainsopiva pala.
            if(korkeus_selvilla == 0){

                for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){

                    // Etsitaan pala joka sopii verrattavan palan alle.
                    if(pala_jono_.at(jarjestettu_lkm - leveys_).allekkain(*jarjestaja)){

                        // Pala loytyi, katsotaan onko se kulmapala.
                        if((*jarjestaja).onko_kulmapala()){

                            kulmapaloja_valmiina++;

                            // Kierretaan oikein pain jotta se sopii verratun palan alle.
                            (*jarjestaja).kierra_allekkain(pala_jono_.at(jarjestettu_lkm - leveys_));

                            // Vaihdetaan kierretty pala oikeaan kohtaan.
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                            korkeus_selvilla = 2;
                            korkeus_ = (jarjestettu_lkm + leveys_ - 1) / leveys_;
                            break;
                        }
                        else {

                            (*jarjestaja).kierra_allekkain(pala_jono_.at(jarjestettu_lkm - leveys_));

                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            jarjestettu_lkm++;
                            korkeus_selvilla = 1;
                            break;
                        }
                    }
                }
            }

            // Korkeus ei ole viela selvilla joten asetellaan paloja vierekkain.
            if(korkeus_selvilla == 1){

                for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){

                    // Etsitaan pala joka sopii viime palan viereen.
                    if (pala_jono_.at(jarjestettu_lkm-1).vierekkain(*jarjestaja)){

                        // Kierretaan pala jotta se sopii viereen.
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm-1));

                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;

                        // Jos pala on reunapala, palataan taas vaiheeseen jossa etsitaan
                        // sille allekkaista palaa.
                        if((pala_jono_.at(jarjestettu_lkm - 1)).onko_reunapala()) {
                            korkeus_selvilla = 0;
                        }
                    }
                }
            }
        }

        while (kulmapaloja_valmiina == 3) {
            for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){

                // Etsitaan pala joka sopii viereen.
                if(pala_jono_.at(jarjestettu_lkm - 1).vierekkain(*jarjestaja)){

                    // Tarkastetaan onko loytynyt pala kulmapala.
                    if((*jarjestaja).onko_kulmapala()){

                        // Tarkistetaan sopiiko pala allekkain.
                        if(pala_jono_.at(jarjestettu_lkm - leveys_).allekkain(*jarjestaja)){

                            // Kierretaan viimeinen pala oikeinpain
                            (*jarjestaja).kierra_vika();

                            // Vaihdetaan oikeean kohtaan.
                            iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                            if((*jarjestaja).onko_alarivi()){
                                kulmapaloja_valmiina++;
                                jarjestettu_lkm++;
                                jarjestus_valmis = true;
                                break;
                            }
                            else{
                                cout<<"virhe: palojen ala reunoissa virheita"<<endl;
                                return false;
                            }
                        }
                        else {
                            cout<<"virhe: palojen reunoissa virheita"<<endl;
                        }



                    }
                    else {
                        if(pala_jono_.at(jarjestettu_lkm - leveys_).allekkain(*jarjestaja)){
                            (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));
                            if((*jarjestaja).onko_alarivi()){
                                iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                                jarjestettu_lkm++;
                            }
                            else{
                                cout<<"virhe: palojen ala reunoissa virheita"<<endl;

                                return false;
                            }
                        }
                        else {
                            cout<<"virhe: palojen reunoissa virheita"<<endl;
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}


// Metodi tulostaa valmiin palapelin korkeutta ja leveytta hyvaksikayttaen.
void Palapeli::tulosta() const{

    for (int korkeuden_laskija{0};korkeuden_laskija != korkeus_;korkeuden_laskija++){
        for (int leveyden_laskija{korkeuden_laskija * leveys_}, counter = 0;counter != leveys_;leveyden_laskija++){
            pala_jono_.at(leveyden_laskija).tulosta_1();
            counter++;
        }
        cout<<endl;
        for (int leveyden_laskija{korkeuden_laskija * leveys_}, counter = 0;counter != leveys_;leveyden_laskija++){
            pala_jono_.at(leveyden_laskija).tulosta_2();
            counter++;

        }
        cout<<endl;
        for (int leveyden_laskija{korkeuden_laskija * leveys_}, counter = 0;counter != leveys_;leveyden_laskija++){
            pala_jono_.at(leveyden_laskija).tulosta_3();
            counter++;

        }
        cout<<endl;
    }

}

