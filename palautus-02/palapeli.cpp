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

void Palapeli::jarjesta() {
    deque<Pala>::iterator jarjestaja;
    jarjestaja = pala_jono_.begin();
    bool jarjestus_valmis = false;
    int kulmapaloja_valmiina{0};
    int jarjestettu_lkm{0};
    int korkeus_selvilla{0};

    while (!jarjestus_valmis){
        if (jarjestettu_lkm == 0){
            if((*jarjestaja).onko_aloituspala()){
                //ensimmainen pala on tassa vaiheessa loydetty, kierretaan se ympari
                //oikeinpain ja sijoitetaan alkuun.
                (*jarjestaja).kierra_eka();
                iter_swap(jarjestaja, pala_jono_.begin());
                jarjestettu_lkm++;
                kulmapaloja_valmiina++;
            }
            else {
                jarjestaja++;
            }
        }
        while ((jarjestettu_lkm >= 1) && (kulmapaloja_valmiina == 1)) {
            for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){
                if (pala_jono_.at(jarjestettu_lkm - 1).vierekkain((*jarjestaja))){
                    if((*jarjestaja).onko_kulmapala()){
                        kulmapaloja_valmiina++;
                        leveys_ = jarjestettu_lkm + 1;
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;
                    }
                    else{
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;

                    }
                }
            }
        }
        while (kulmapaloja_valmiina == 2) {
            //0=etsitaan alle sopivaa palaa, 1=etsitaan vierekkaisia paloja,
                                    //2=uusi kulmapala loytynyt
            if(korkeus_selvilla == 0){

                for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){
                    if(pala_jono_.at(jarjestettu_lkm - leveys_).allekkain(*jarjestaja)){
                        if((*jarjestaja).onko_kulmapala()){
                            kulmapaloja_valmiina++;
                            (*jarjestaja).kierra_allekkain(pala_jono_.at(jarjestettu_lkm - leveys_));
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
            if(korkeus_selvilla == 1){
                for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){
                    if (pala_jono_.at(jarjestettu_lkm-1).vierekkain(*jarjestaja)){
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm-1));
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;
                        if((pala_jono_.at(jarjestettu_lkm - 1)).onko_reunapala()) {
                            korkeus_selvilla = 0;
                        }
                    }
                }
            }
        }

        while (kulmapaloja_valmiina == 3) {
            for(jarjestaja = pala_jono_.begin();jarjestaja != pala_jono_.end();jarjestaja++){
                if(pala_jono_.at(jarjestettu_lkm - 1).vierekkain(*jarjestaja)){
                    if((*jarjestaja).onko_kulmapala()){
                        kulmapaloja_valmiina++;
                        (*jarjestaja).kierra_vika();
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;
                        jarjestus_valmis = true;
                        break;
                    }
                    else {
                        (*jarjestaja).kierra_vierekkain(pala_jono_.at(jarjestettu_lkm - 1));
                        iter_swap(jarjestaja, pala_jono_.begin() + jarjestettu_lkm);
                        jarjestettu_lkm++;
                    }
                }
            }
        }
    }
}

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

